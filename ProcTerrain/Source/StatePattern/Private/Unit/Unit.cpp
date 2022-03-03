// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/Unit.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "State/UnitState.h"
#include "State/Shared/AttackState.h"
#include "State/Shared/DeadState.h"
#include "State/Shared/IdleState.h"
#include "DrawDebugHelpers.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 100;
	Health = MaxHealth;
	AttackPower = 10;
	AttackCooldown = 1.0f;
	MoveSpeed = 600;
	AttackStateClass = UAttackState::StaticClass();
	StartingStateClass = UIdleState::StaticClass();
	MeleeHitboxRadius = 50;
	MeleeForwardOffset = 80;
	SetCanBeDamaged(true);
}


void AUnit::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	}
}

void AUnit::PopState()
{
	if(StateStack.Num() <= 0 )
	{
		return; //cant pop state from empty stack
	}
	CurrentState->OnLeave(this);
	StateStack.Pop();
	OnStateStackChanged.Broadcast();
	CurrentState = StateStack.Last();
	CurrentState->OnReturn(this);
	
}

void AUnit::PushState(UUnitState* State)
{
	if(CurrentState) //if we have a state currently
	{
		CurrentState->OnLeave(this);
		
	}
	CurrentState = State;

	StateStack.Add(State);  //add new state to the stack
	OnStateStackChanged.Broadcast();
	State->OnEnter(this);
	
}

bool AUnit::Attack()
{
	if(CurrentState)
	{
		return CurrentState->Attack();
	}
	return false;
}

bool AUnit::TryJump()
{
	if(CurrentState)
	{
		return CurrentState->Jump();
	}
	return false;
}

UUnitState* AUnit::GetCurrentState() const
{
	return CurrentState;
}

void AUnit::PlayAttackMontage()
{
	if(AttackMontages.Num() > 0)
	{
		PlayAnimMontage(AttackMontages[FMath::RandRange(0,HitMontages.Num()-1)]);
	}
}

void AUnit::PlayDeathMontage()
{
	if(DeathMontages.Num() > 0)
	{
		PlayAnimMontage(DeathMontages[FMath::RandRange(0,HitMontages.Num()-1)]);
	}
}

void AUnit::PlayHitMontage()
{
	if(HitMontages.Num() > 0)
	{
		PlayAnimMontage(HitMontages[FMath::RandRange(0,HitMontages.Num()-1)]);
	}
}

void AUnit::MeleeHitbox()
{
	TArray<AActor*> OverlappedActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	
	TArray<AActor*> ignoreActors;
	ignoreActors.Init(this, 1);
	
	FVector TraceCenter = GetActorLocation() + (GetActorForwardVector() * MeleeForwardOffset);
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(),TraceCenter,MeleeHitboxRadius,ObjectTypes,AUnit::StaticClass(),ignoreActors,OverlappedActors);
	if(bDebugMode)
	{
		DrawDebugSphere(GetWorld(),TraceCenter,MeleeHitboxRadius, 12,FColor::Red,false,1,0,2);
	}
	
	for(AActor* Actor : OverlappedActors)
	{
		if(Actor->CanBeDamaged())
		{
			
			Actor->TakeDamage(AttackPower,FDamageEvent(),GetController(),this);
		}
	}
}

void AUnit::FireRanged()
{
	FRotator AimRot = GetControlRotation();
	
}

float AUnit::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	
	float TotalDamage = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	if(!CanBeDamaged()) return 0;
	float NewHealthValue = FMath::Clamp(Health-TotalDamage,0.f,MaxHealth);
	SetHealth(NewHealthValue);
	
	if(NewHealthValue <= 0) //go to dead state
	{
		UDeadState* DeadState = NewObject<UDeadState>(this,UDeadState::StaticClass());
		PushState(DeadState);
	}
	else    //let current state know
	{
	     CurrentState->TookDamage();
	}
	return TotalDamage;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(StartingStateClass))
	{
		UUnitState* StartState = NewObject<UUnitState>(this,StartingStateClass);
		PushState(StartState);
	}
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

void AUnit::SetHealth(float NewHealth)
{
	if(NewHealth != Health)
	{
		Health = NewHealth;
		OnHealthChange.Broadcast(NewHealth);
	}
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

