// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "OpenColorIOColorSpace.h"
#include "AdvancedTonemappingSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, DisplayName = "AdvancedTonemapping")
class ADVANCEDTONEMAPPING_API UAdvancedTonemappingSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "AdvancedTonemapping", meta = (DisplayName = "Use custom tonemapper", ToolTip = "Use OCIO to replace the engine tonemapper"))
	bool bUseCustomTonemapper = true;

	virtual FName GetContainerName() const override { return FName("Project"); };
	virtual FName GetCategoryName() const override { return FName("Plugins"); };
	virtual FName GetSectionName() const override { return FName("AdvancedTonemapping"); };

	static UAdvancedTonemappingSettings& Get();

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "AdvancedTonemapping")
	FOpenColorIOColorConversionSettings ColorConversionSettings;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
