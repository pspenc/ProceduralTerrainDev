// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralLandscape.h"

#include "KismetProceduralMeshLibrary.h"
#include "SimplexNoiseBPLibrary.h"

// Sets default values
AProceduralLandscape::AProceduralLandscape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProceduralLandscapeMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralLandsacpe");
	SetRootComponent(ProceduralLandscapeMesh);


	
}

bool AProceduralLandscape::GenerateLandscape()
{
	
	ProceduralLandscapeMesh->ClearMeshSection(0);
	TArray<int32> Triangles;
	TArray<FVector> Vertices;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> VertexColors;
	TArray<FVector>		Normals;
	TArray<FProcMeshTangent> Tangents;
	
	VertexColors.Init(FLinearColor(1,0,.5,1),MapSize*MapSize);
	
	UKismetProceduralMeshLibrary::CreateGridMeshWelded(MapSize,MapSize,Triangles,Vertices,UVs,GridPointSize);
	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices,Triangles,UVs,Normals,Tangents);
	
	ApplyNoise(Vertices,VertexColors);

	ProceduralLandscapeMesh->CreateMeshSection_LinearColor(0,Vertices,Triangles,Normals,UVs,TArray<FVector2D>(),TArray<FVector2D>(),
																TArray<FVector2D>(),VertexColors,Tangents,true);
	
	m_Vertices = Vertices;
	m_VertexColors = VertexColors;
	m_UVs = UVs;

	return true;
}
/*
void AProceduralLandscape::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	GenerateLandscape();
}
*/
void AProceduralLandscape::PostActorCreated()
{
	Super::PostActorCreated();
	//GenerateLandscape();
}

void AProceduralLandscape::PostLoad()
{
	Super::PostLoad();
	//GenerateLandscape();
}

// Called when the game starts or when spawned
void AProceduralLandscape::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProceduralLandscape::ApplyNoise(TArray<FVector>& Vertices,TArray<FLinearColor>& VertexColors)
{

	for(int y = 0; y < MapSize; y++)
	{
		for(int x = 0; x < MapSize; x++)
		{
			
			float nx =  (float)x/(float)MapSize - .5f;
			float ny = (float)y/(float)MapSize - .5f;
			float Elevation =		ElevationOctave1*	USimplexNoiseBPLibrary::SimplexNoise2D(nx*1.f,ny*1.f)
								+	ElevationOctave2*	USimplexNoiseBPLibrary::SimplexNoise2D(nx*2.f,ny*2.f)
								+	ElevationOctave3*	USimplexNoiseBPLibrary::SimplexNoise2D(nx*4.f,ny*4.f)
								+	ElevationOctave4*	USimplexNoiseBPLibrary::SimplexNoise2D(nx*8.f,ny*8.f);
			Elevation = Elevation / (ElevationOctave1+ElevationOctave2+ElevationOctave3+ElevationOctave4);
			//Elevation = FMath::Pow(Elevation*1.1f,ElevationRedistributionFactor);
			Vertices[y + (x*MapSize)].Z = Elevation*HeightScale;
			if(Elevation > .4f)
			{
				VertexColors[y + (x*MapSize)] = FLinearColor(1,0,1,1);
			}
			else if (Elevation > .15f)
			{
				VertexColors[y + (x*MapSize)] = FLinearColor(0,1,0,1);
			}
			else
			{
				VertexColors[y + (x*MapSize)] = FLinearColor(0,0,1,1);
			}
			
			
		}
		
	}
}

void AProceduralLandscape::DiamondSquare(TArray<FVector>, int size)
{
	int HalfSize = size / 2;
	if(HalfSize < 1){return;}

	

	
}

// Called every frame
void AProceduralLandscape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

