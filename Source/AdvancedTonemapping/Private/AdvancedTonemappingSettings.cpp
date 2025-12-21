// Fill out your copyright notice in the Description page of Project Settings.
#include "AdvancedTonemappingSettings.h"
#include "OpenColorIOColorSpace.h"
#include "OpenColorIOConfiguration.h"
#include "AdvancedTonemappingSubsystem.h"


UAdvancedTonemappingSettings& UAdvancedTonemappingSettings::Get()
{
	UAdvancedTonemappingSettings* MutableCDO = GetMutableDefault<UAdvancedTonemappingSettings>();
	check(MutableCDO != nullptr)
		return *MutableCDO;
}

void UAdvancedTonemappingSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (GEditor)
    {
        GEditor->GetTimerManager()->SetTimerForNextTick([this]()
            {
                UOpenColorIOConfiguration* Config = ColorConversionSettings.ConfigurationSource.Get();
                if (!Config)
                {
                    return;
                }

                //For a simple Config with only one ColorSpace and one DisplayView, we can load it automatically.
                if (Config->DesiredColorSpaces.Num() == 1)
                {
                    ColorConversionSettings.SourceColorSpace = Config->DesiredColorSpaces[0];
                }

                if (Config->DesiredDisplayViews.Num() == 1)
                {
                    ColorConversionSettings.DestinationDisplayView = Config->DesiredDisplayViews[0];
                }

                if (GEngine)
                {
                    if (UAdvancedTonemappingSubsystem* Subsystem = GEngine->GetEngineSubsystem<UAdvancedTonemappingSubsystem>())
                    {
                        Subsystem->MarkDirty();
                    }
                }
            });
    }
}