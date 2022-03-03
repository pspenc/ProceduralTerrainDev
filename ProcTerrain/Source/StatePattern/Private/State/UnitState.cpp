// Fill out your copyright notice in the Description page of Project Settings.


#include "State/UnitState.h"

#include "Unit/Unit.h"

UUnitState::UUnitState()
{
	StateName = "DefaultState";
}

void UUnitState::OnEnter(AUnit* Unit)
{
	AssignedUnit = Unit;		
}

void UUnitState::OnReturn(AUnit* Unit)
{
	AssignedUnit = Unit;
}

void UUnitState::OnLeave(AUnit* Unit)
{
	
}

bool UUnitState::Move(FVector Direction, float Scale)
{
	return CanMove();
}

bool UUnitState::Attack()
{
	return CanAttack();
}

bool UUnitState::Jump()
{
	return CanJump();
}

void UUnitState::TookDamage()
{
}

bool UUnitState::CanMove()
{
	return true;
}

bool UUnitState::CanAttack()
{
	return true;
}

bool UUnitState::CanJump()
{
	return true;
}

bool UUnitState::IsCurrentState() const
{
	if(AssignedUnit)
	{
		return (this == AssignedUnit->GetCurrentState());
	}
	return false;
}
