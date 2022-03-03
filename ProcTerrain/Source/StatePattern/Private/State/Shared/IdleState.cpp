// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Shared/IdleState.h"

#include "State/Shared/DamagedState.h"
#include "State/Shared/JumpState.h"
#include "State/Shared/MovingState.h"
#include "Unit/Unit.h"

UIdleState::UIdleState()
{
	StateName = "Idle State";
}

bool UIdleState::Move(FVector Direction, float Scale)
{
	if(!AssignedUnit)
	{
		return false;
	}

	if(FMath::Abs(Scale) > 0)
	{
		UMovingState* MoveState = NewObject<UMovingState>(GetOuter(),UMovingState::StaticClass());
		AssignedUnit->PushState(MoveState);
		AssignedUnit->GetCurrentState()->Move(Direction,Scale);
		return true;
	}
	
	return false;
}

bool UIdleState::Jump()
{
	if(!AssignedUnit)
	{
		return false;
	}
	UJumpState* JumpState = NewObject<UJumpState>(GetOuter(),UJumpState::StaticClass());
	AssignedUnit->PushState(JumpState);
	return true;
}

bool UIdleState::Attack()
{
	if(AssignedUnit)
	{
		if(AssignedUnit->AttackStateClass)
		{
			UUnitState* AttackState = NewObject<UUnitState>(GetOuter(),AssignedUnit->AttackStateClass);
			AssignedUnit->PushState(AttackState);
			return true;
		}
	}
	return false;
}

void UIdleState::TookDamage()
{
	UDamagedState* DamagedState = NewObject<UDamagedState>(GetOuter(),UDamagedState::StaticClass());
	if(AssignedUnit)
	{
		AssignedUnit->PushState(DamagedState);
	}
	
}

bool UIdleState::CanAttack()
{
	return true;
}

bool UIdleState::CanJump()
{
	return true;
}

bool UIdleState::CanMove()
{
	return true;
}
