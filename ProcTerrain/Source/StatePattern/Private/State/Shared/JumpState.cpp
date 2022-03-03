// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Shared/JumpState.h"

#include "Unit/Unit.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "State/Shared/DamagedState.h"

UJumpState::UJumpState()
{
	StateName = "Jump State";
	bQueueRemoval = false;
}

void UJumpState::TookDamage()
{
	UDamagedState* DamagedState = NewObject<UDamagedState>(GetOuter(),UDamagedState::StaticClass());
	if(AssignedUnit)
	{
		AssignedUnit->PushState(DamagedState);
	}
	bQueueRemoval = true;
}

void UJumpState::OnEnter(AUnit* Unit)
{
	Super::OnEnter(Unit);
	Unit->LandedDelegate.AddDynamic(this,&UJumpState::OnLand);
	Unit->Jump();
}

void UJumpState::OnReturn(AUnit* Unit)
{
	Super::OnReturn(Unit);
	if(bQueueRemoval)
	{
		Unit->PopState();
	}
}

void UJumpState::OnLeave(AUnit* Unit)
{
	Super::OnLeave(Unit);
	//AssignedUnit->LandedDelegate.RemoveDynamic(this,&UJumpState::OnLand);
	bQueueRemoval = false;
}

void UJumpState::OnLand(const FHitResult& Hit)
{
	AssignedUnit->LandedDelegate.RemoveDynamic(this,&UJumpState::OnLand);
	if(IsCurrentState()) //are we in this state 
	{
		AssignedUnit->PopState();
		return;
	}
	bQueueRemoval = true;
	
}
