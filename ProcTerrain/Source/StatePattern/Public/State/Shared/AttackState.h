// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/UnitState.h"
#include "AttackState.generated.h"

/**
 * 
 */
UCLASS()
class STATEPATTERN_API UAttackState : public UUnitState
{
	GENERATED_BODY()

	public:
	UAttackState();
	virtual void OnEnter(AUnit* Unit) override;
	virtual void OnReturn(AUnit* Unit) override;
	virtual bool Move(FVector Direction, float Scale) override;
	virtual bool CanMove() override;
	virtual bool CanJump() override;
	
	UFUNCTION()
	void AttackApex();
	UFUNCTION()
	void PostAttack();

	protected:

	bool bReachedApex;
};
