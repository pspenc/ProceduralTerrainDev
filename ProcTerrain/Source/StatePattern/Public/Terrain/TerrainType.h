// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TerrainType.generated.h"


UENUM()
enum class ETerrainType : uint8
{
	Grassland,
	Mountainside,
	Snow
};

/**
 * 
 */
UCLASS()
class STATEPATTERN_API UTerrainType : public UObject
{
	GENERATED_BODY()
	
};
