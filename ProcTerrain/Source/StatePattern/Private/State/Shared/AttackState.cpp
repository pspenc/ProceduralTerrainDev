// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Shared/AttackState.h"
#include "Unit/Unit.h"
#include "Unit/UnitAnimInstance.h"

UAttackState::UAttackState()
{
	StateName = "Attack State";
}

void UAttackState::OnEnter(AUnit* Unit)
{
	Super::OnEnter(Unit);

	if(Unit)
	{
		UUnitAnimInstance* AnimInstance = Cast<UUnitAnimInstance>(Unit->GetMesh()->GetAnimInstance());
        if(AnimInstance)
        {
        	AnimInstance->OnAttackPointReached.AddDynamic(this,&UAttackState::AttackApex);
        }
        else
        {
        	FTimerHandle Handle;
        	Unit->GetWorld()->GetTimerManager().SetTimer(Handle,this,&UAttackState::AttackApex,.5f);
        }
		bReachedApex = false;
        Unit->PlayAttackMontage();
		
	}
	
}

void UAttackState::OnReturn(AUnit* Unit)
{
	Super::OnReturn(Unit);
	if(bQueueRemoval)
	{
		if(AssignedUnit->GetCurrentState() == this)
		{
			AssignedUnit->PopState();
		}
	}
}

bool UAttackState::Move(FVector Direction, float Scale)
{
	if(CanMove())
	{
        if(FMath::Abs(Scale) > 0) //apply movement
        {
        	AssignedUnit->AddMovementInput(Direction, Scale*.5f);
        	
        	return true;
        }
		
	}
	return false;
}

bool UAttackState::CanMove()
{
	return !bReachedApex;
}

bool UAttackState::CanJump()
{
	return false;
}

void UAttackState::AttackApex()
{
	bReachedApex = true;
	if(AssignedUnit->AttackType == EAttackType::Melee)
	{
		AssignedUnit->MeleeHitbox();
	}
	else if(AssignedUnit->AttackType == EAttackType::Ranged)
	{
		AssignedUnit->FireRanged();
	}
	
	UUnitAnimInstance* AnimInstance = Cast<UUnitAnimInstance>(AssignedUnit->GetMesh()->GetAnimInstance());
	if(AnimInstance)
	{
		AnimInstance->OnAttackPointReached.RemoveDynamic(this,&UAttackState::AttackApex);
		AnimInstance->OnAttackAnimFinished.AddDynamic(this,&UAttackState::PostAttack);
	}
	else
	{
		FTimerHandle Handle;
		AssignedUnit->GetWorld()->GetTimerManager().SetTimer(Handle,this,&UAttackState::PostAttack,.5f);
	}
	
}

void UAttackState::PostAttack()
{
	UUnitAnimInstance* AnimInstance = Cast<UUnitAnimInstance>(AssignedUnit->GetMesh()->GetAnimInstance());
	if(AnimInstance)
	{
		AnimInstance->OnAttackPointReached.RemoveDynamic(this,&UAttackState::AttackApex);
		AnimInstance->OnAttackAnimFinished.RemoveDynamic(this,&UAttackState::PostAttack);
	}
	if(AssignedUnit)
	{
		if(AssignedUnit->GetCurrentState() == this)
		{
			AssignedUnit->PopState();
		}
		else
		{
			bQueueRemoval = true;
		}
		
	}
	
}
