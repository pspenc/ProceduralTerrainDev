// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Shared/DeadState.h"

#include "Unit/Unit.h"
#include "Unit/UnitAnimInstance.h"

UDeadState::UDeadState()
{
	StateName = "DeadState";
}

void UDeadState::OnEnter(AUnit* Unit)
{
	Super::OnEnter(Unit);
	if(Unit)
	{
		Unit->SetCanBeDamaged(false);
		UUnitAnimInstance* AnimInstance = Cast<UUnitAnimInstance>(Unit->GetMesh()->GetAnimInstance());
		if(AnimInstance)
		{
			AnimInstance->OnDeathAnimComplete.AddDynamic(this,&UDeadState::EndOfDeathAnim);
		}
		else
		{
			FTimerHandle Handle;
			Unit->GetWorld()->GetTimerManager().SetTimer(Handle,this,&UDeadState::EndOfDeathAnim,.6f);
		}
		Unit->PlayDeathMontage();
	}
	
}

bool UDeadState::CanMove()
{
	return false;
}

bool UDeadState::CanAttack()
{
	return false;
}

bool UDeadState::CanJump()
{
	return false;
}

void UDeadState::EndOfDeathAnim()
{
	if(AssignedUnit)
	{
		AssignedUnit->Destroy();
	}
}
