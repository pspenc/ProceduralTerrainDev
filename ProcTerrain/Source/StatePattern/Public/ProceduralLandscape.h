// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralLandscape.generated.h"

UCLASS(Blueprintable,BlueprintType)
class STATEPATTERN_API AProceduralLandscape : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralLandscape();


	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UProceduralMeshComponent* ProceduralLandscapeMesh;

	UFUNCTION(BlueprintCallable)
	bool GenerateLandscape();

	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void PostActorCreated() override;
	void PostLoad() override;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MapSize = 10;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float GridPointSize = 16;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float HeightScale = 1;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ElevationOctave1 = .5;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ElevationOctave2 = .25;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ElevationOctave3 = .13;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ElevationOctave4 = .06;
	//UPROPERTY(EditAnywhere,BlueprintReadWrite)
	//float ElevationRedistributionFactor = 1.71;


	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> m_Vertices;
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector2D> m_UVs;
	UPROPERTY(BlueprintReadWrite)
	TArray<FLinearColor> m_VertexColors;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ApplyNoise(TArray<FVector>& Vertices,TArray<FLinearColor>& VertexColors);
	void DiamondSquare(TArray<FVector>, int size);

	
	
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
