// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/UnitState.h"
#include "DeadState.generated.h"

/**
 * 
 */
UCLASS()
class UDeadState : public UUnitState
{
	GENERATED_BODY()

public:

	UDeadState();
	virtual void OnEnter(AUnit* Unit) override;



	virtual bool CanMove() override;
	virtual bool CanAttack() override;
	virtual bool CanJump() override;
	
	UFUNCTION()
	void EndOfDeathAnim();
	
};
