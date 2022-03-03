// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/UnitState.h"
#include "MovingState.generated.h"

/**
 * 
 */
UCLASS()
class STATEPATTERN_API UMovingState : public UUnitState
{
	GENERATED_BODY()

	public:
	UMovingState();
	
	virtual bool Move(FVector Direction, float Scale) override;
	virtual bool Attack() override;
	virtual bool Jump() override;
	virtual void TookDamage();
	virtual bool CanAttack() override;
	virtual bool CanJump() override;
	virtual bool CanMove() override;


	protected:

	int RecentZeros;
};
