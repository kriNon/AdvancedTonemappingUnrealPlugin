// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "OpenColorIODisplayExtensionWrapper.h"
#include "AdvancedTonemappingSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDTONEMAPPING_API UAdvancedTonemappingSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:
	void MarkDirty();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void CreateDisplayExtension();
	void RemoveDisplayExtension();
	virtual void Deinitialize() override;

private:
	UPROPERTY(Transient)
	TObjectPtr<UOpenColorIODisplayExtensionWrapper> DisplayExtensionWrapper;
};
