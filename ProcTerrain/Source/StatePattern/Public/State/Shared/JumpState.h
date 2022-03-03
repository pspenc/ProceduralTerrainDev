// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/UnitState.h"
#include "JumpState.generated.h"

/**
 * 
 */
UCLASS()
class STATEPATTERN_API UJumpState : public UUnitState
{
	GENERATED_BODY()


public:

	UJumpState();

	virtual void TookDamage() override;
	
	virtual void OnEnter(AUnit* Unit) override;
	virtual void OnReturn(AUnit* Unit) override;
	virtual void OnLeave(AUnit* Unit) override;
	UFUNCTION()
	void OnLand(const FHitResult& Hit);


private:


	
};


