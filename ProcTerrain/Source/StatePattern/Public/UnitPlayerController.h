// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnitPlayerController.generated.h"


class AUnit;
class UUnitState;

/**
 * 
 */
UCLASS()
class STATEPATTERN_API AUnitPlayerController : public APlayerController
{
	GENERATED_BODY()



	public:

	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);
	
	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void TryJump();
	void TryAttack();
	
protected:

	UPROPERTY(BlueprintReadOnly)
	AUnit* ControlledUnit;

	
	
	
	
};
