// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Projectile.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	SetRootComponent(Collision);

	ProjMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjMesh");
	ProjMesh->SetupAttachment(Collision);
	ProjectileParticles = CreateDefaultSubobject<UParticleSystemComponent>("ProjectileParticles");
	ProjectileParticles->SetupAttachment(Collision);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->MaxSpeed = Speed;
}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(ProjectileMovementComponent)
	{
		ProjectileMovementComponent->InitialSpeed = Speed;
		
	}
}



// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

