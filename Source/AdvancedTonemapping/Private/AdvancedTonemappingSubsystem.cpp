// Fill out your copyright notice in the Description page of Project Settings.
#include "AdvancedTonemappingSubsystem.h"
#include "AdvancedTonemappingSettings.h"
#include "OpenColorIOColorSpace.h"
#include "Misc/Optional.h"
#include "OpenColorIO/Private/OpenColorIOModule.h"
#include "OpenColorIODisplayManager.h"
#include "Editor.h"

void UAdvancedTonemappingSubsystem::MarkDirty()
{
    // Remove existing extension
    RemoveDisplayExtension();

    // Recreate with current settings
    CreateDisplayExtension();
}

void UAdvancedTonemappingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    CreateDisplayExtension();
}

void UAdvancedTonemappingSubsystem::CreateDisplayExtension()
{
    const UAdvancedTonemappingSettings* Settings = GetDefault<UAdvancedTonemappingSettings>();
    if (!Settings)
    {
        return;
    }

    // If aces is selected, or settings is disabled, we skip the display extension
    if (!Settings->bUseCustomTonemapper || Settings->Tonemapper == ETonemapper::ACES) {
        return;
    }

    const FOpenColorIOColorConversionSettings& ConversionSettings = Settings->ColorConversionSettings;

    // Validate you actually have an OCIO config asset set
    if (!ConversionSettings.ConfigurationSource)
    {
        UE_LOG(LogTemp, Warning, TEXT("OCIO ConfigurationSource is null."));
        return;
    }

    // Build a real display configuration variable
    FOpenColorIODisplayConfiguration DisplayConfig;
    DisplayConfig.bIsEnabled = true;
    DisplayConfig.ColorConfiguration = ConversionSettings;

    // Create a functor that applies to ALL viewports
    FSceneViewExtensionIsActiveFunctor IsActiveFunctor;
    IsActiveFunctor.IsActiveFunction = [](const ISceneViewExtension* SceneViewExtension,
        const FSceneViewExtensionContext& Context)
        {
            check(SceneViewExtension);

            const FOpenColorIODisplayExtension* SVE =
                static_cast<const FOpenColorIODisplayExtension*>(SceneViewExtension);
            const bool bIsEnabled = SVE->GetDisplayConfiguration().bIsEnabled;

            // Apply to any valid viewport
            if (Context.Viewport)
            {
                return TOptional<bool>(bIsEnabled);
            }

            // No viewport context - no opinion
            return TOptional<bool>();
        };

    // Create the display extension with our "all viewports" functor
    DisplayExtensionWrapper = UOpenColorIODisplayExtensionWrapper::CreateOpenColorIODisplayExtension(
        DisplayConfig,
        IsActiveFunctor
    );

    // Prevent garbage collection
    if (DisplayExtensionWrapper)
    {
        DisplayExtensionWrapper->AddToRoot();
    }
}

void UAdvancedTonemappingSubsystem::RemoveDisplayExtension()
{
    if (DisplayExtensionWrapper)
    {
        DisplayExtensionWrapper->RemoveFromRoot();
        DisplayExtensionWrapper->RemoveSceneExtension();
        DisplayExtensionWrapper = nullptr;
    }
}

void UAdvancedTonemappingSubsystem::Deinitialize()
{
    RemoveDisplayExtension();
    Super::Deinitialize();
}