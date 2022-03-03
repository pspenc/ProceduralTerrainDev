// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Projectile.generated.h"

UCLASS()
class STATEPATTERN_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	float Speed;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USphereComponent* Collision;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* ProjMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UParticleSystemComponent* ProjectileParticles;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UParticleSystem* ImpactParticles;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
