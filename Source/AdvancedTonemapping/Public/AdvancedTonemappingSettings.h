// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "OpenColorIOColorSpace.h"
#include "AdvancedTonemappingSettings.generated.h"

UENUM(BlueprintType)
enum class ETonemapper : uint8
{
	ACES,
	TonyMcMapface,
	MAX,
};

UCLASS(Config = Game, DefaultConfig, DisplayName = "AdvancedTonemapping")
class ADVANCEDTONEMAPPING_API UAdvancedTonemappingSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "AdvancedTonemapping", meta = (DisplayName = "Use custom tonemapper", ToolTip = "Use OCIO to replace the engine tonemapper"))
	bool bUseCustomTonemapper = true;

	UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category = "AdvancedTonemapping", meta = (DisplayName = "TonemappingOperator", ToolTip = "Custom tonemapping operator to use"))
	ETonemapper Tonemapper;

	virtual FName GetContainerName() const override { return FName("Project"); };
	virtual FName GetCategoryName() const override { return FName("Plugins"); };
	virtual FName GetSectionName() const override { return FName("AdvancedTonemapping"); };

	static UAdvancedTonemappingSettings& Get();

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "AdvancedTonemapping")
	FOpenColorIOColorConversionSettings ColorConversionSettings;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
