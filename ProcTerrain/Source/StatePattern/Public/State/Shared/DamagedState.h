// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/UnitState.h"
#include "DamagedState.generated.h"

/**
 * 
 */
UCLASS()
class STATEPATTERN_API UDamagedState : public UUnitState
{
	GENERATED_BODY()

public:
	
	UDamagedState();
	
	virtual void OnEnter(AUnit* Unit) override;
	virtual void OnReturn(AUnit* Unit) override;
	virtual void OnLeave(AUnit* Unit) override;
	
	UFUNCTION()
	void DamageAnimComplete();
};
