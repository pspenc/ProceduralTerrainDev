// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/UnitState.h"
#include "IdleState.generated.h"

/**
 * 
 */
UCLASS()
class STATEPATTERN_API UIdleState : public UUnitState
{
	GENERATED_BODY()



public:

	UIdleState();
	
	virtual bool Move(FVector Direction, float Scale) override;
	virtual bool Jump() override;
	virtual bool Attack() override;
	virtual void TookDamage() override;
	
	virtual bool CanAttack() override;
	virtual bool CanJump() override;
	virtual bool CanMove() override;
	
protected:
	
	
};
