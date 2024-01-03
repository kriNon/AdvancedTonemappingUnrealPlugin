// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdvancedTonemapping.h"

#include "FileHandler.h"
#include "USModLoader.h"

#define LOCTEXT_NAMESPACE "FAdvancedTonemappingModule"

void FAdvancedTonemappingModule::StartupModule()
{
	UnrealShaderModLoader::AddModification_InsertAfter(TEXT("PostProcessCombineLUTs.usf"), R"(#include "TonemapCommon.ush")", R"(#include "notorious6/Tonemapping.ush")");
	UnrealShaderModLoader::AddModification_Comment(TEXT("PostProcessCombineLUTs.usf"), R"(ColorAP1 = lerp( ColorAP1, mul( BlueCorrectAP1, ColorAP1 ), BlueCorrection );)");
	UnrealShaderModLoader::AddModification_Comment(TEXT("PostProcessCombineLUTs.usf"), R"(ColorAP1 = lerp( ColorAP1, mul( BlueCorrectInvAP1, ColorAP1 ), BlueCorrection );)");
	UnrealShaderModLoader::AddModification_Replace(TEXT("PostProcessCombineLUTs.usf"),R"(float3 ToneMappedColorAP1 = FilmToneMap( ColorAP1 );)", R"(float3 ToneMappedColorAP1 = display_transform_AP1( ColorAP1 );)");
	
	USMLFileHandler::CopyShaderOverridesToUnrealShaderModLoader(TEXT("AdvancedTonemapping"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAdvancedTonemappingModule, AdvancedTonemapping)