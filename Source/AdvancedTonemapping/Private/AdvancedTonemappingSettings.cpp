// Fill out your copyright notice in the Description page of Project Settings.
#include "AdvancedTonemappingSettings.h"
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

    if (GEngine)
    {
        if (UAdvancedTonemappingSubsystem* Subsystem = GEngine->GetEngineSubsystem<UAdvancedTonemappingSubsystem>())
        {
            Subsystem->MarkDirty();
        }
    }
}