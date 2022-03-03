// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnitState.generated.h"


class AUnit;

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class STATEPATTERN_API UUnitState : public UObject
{
	GENERATED_BODY()


public:

	UUnitState();
	
	//Transitions
	virtual void OnEnter(AUnit* Unit);
	virtual void OnReturn(AUnit* Unit);
	virtual void OnLeave(AUnit* Unit);

	//Inputs
	UFUNCTION(BlueprintCallable)
	virtual bool Move(FVector Direction, float Scale);
	UFUNCTION(BlueprintCallable)
	virtual bool Attack();
	UFUNCTION(BlueprintCallable)
	virtual bool Jump();
	UFUNCTION()
	virtual void TookDamage();
	//Queries
	UFUNCTION(BlueprintPure)
	virtual bool CanMove();
	UFUNCTION(BlueprintPure)
	virtual bool CanAttack();
	UFUNCTION(BlueprintPure)
	virtual bool CanJump();
	UFUNCTION(BlueprintPure)
	bool IsCurrentState() const;
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FName StateName;


	UFUNCTION(BlueprintPure)
	bool HasQueuedRemoval() const {return bQueueRemoval;}
	

	
	
protected:

	UPROPERTY()
	AUnit* AssignedUnit;
	bool bQueueRemoval = false;
	
private:


};
