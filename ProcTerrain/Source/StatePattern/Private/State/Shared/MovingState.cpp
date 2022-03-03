// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Shared/MovingState.h"

#include "State/Shared/DamagedState.h"
#include "State/Shared/JumpState.h"
#include "Unit/Unit.h"



UMovingState::UMovingState()
{
	StateName = "MovingState";
}

bool UMovingState::Move(FVector Direction, float Scale)
{
	if(!AssignedUnit){return false;} //if no unit, fail
	
	if(FMath::Abs(Scale) > 0) //apply movement
	{
		AssignedUnit->AddMovementInput(Direction, Scale);
		
		return true;
	}
	if(AssignedUnit->GetLastMovementInputVector().Size() <= 0)
	{
		AssignedUnit->PopState();
	}
	
	return false;
}


bool UMovingState::Attack()
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

bool UMovingState::Jump()
{
	if(!AssignedUnit){return false;}
	UJumpState* JumpState = NewObject<UJumpState>(this,UJumpState::StaticClass());
	AssignedUnit->PushState(JumpState);
	return true;
}

void UMovingState::TookDamage()
{
	UDamagedState* DamagedState = NewObject<UDamagedState>(GetOuter(),UDamagedState::StaticClass());
	if(AssignedUnit)
	{
		AssignedUnit->PushState(DamagedState);
	}
	
}


bool UMovingState::CanAttack()
{
	return true;
}

bool UMovingState::CanJump()
{
	return true;
}

bool UMovingState::CanMove()
{
	return true;
}
