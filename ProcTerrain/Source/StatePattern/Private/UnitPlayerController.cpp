// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitPlayerController.h"

#include "State/UnitState.h"
#include "Unit/Unit.h"


void AUnitPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ControlledUnit = Cast<AUnit>(InPawn);
}

void AUnitPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("Jump", IE_Pressed, this, &AUnitPlayerController::TryJump);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AUnitPlayerController::TryAttack);
	

	InputComponent->BindAxis("MoveForward", this, &AUnitPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AUnitPlayerController::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &AUnitPlayerController::AddYawInput);
	InputComponent->BindAxis("TurnRate", this, &AUnitPlayerController::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &AUnitPlayerController::AddPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AUnitPlayerController::LookUpAtRate);
}

void AUnitPlayerController::TryJump()
{
	if(ControlledUnit)
	{
		ControlledUnit->GetCurrentState()->Jump();
	}
}

void AUnitPlayerController::TryAttack()
{
	if(ControlledUnit)
	{
		ControlledUnit->Attack();
	}
}

void AUnitPlayerController::MoveForward(float Value)
{
	if(ControlledUnit)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		ControlledUnit->GetCurrentState()->Move(Direction,Value);
		
		
	}
	
}



void AUnitPlayerController::MoveRight(float Value)
{
	if(ControlledUnit)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		
		ControlledUnit->GetCurrentState()->Move(Direction,Value);
		
		
	}
}



void AUnitPlayerController::TurnAtRate(float Rate)
{
	AddYawInput(Rate * 45.f * GetWorld()->GetDeltaSeconds());
}

void AUnitPlayerController::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddPitchInput(Rate * 45.f * GetWorld()->GetDeltaSeconds());
}
