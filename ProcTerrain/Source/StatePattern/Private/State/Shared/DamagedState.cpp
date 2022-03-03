// Fill out your copyright notice in the Description page of Project Settings.


#include "State/Shared/DamagedState.h"

#include "Unit/Unit.h"
#include "Unit/UnitAnimInstance.h"

UDamagedState::UDamagedState()
{
	StateName = "Damaged State";
}

void UDamagedState::OnEnter(AUnit* Unit)
{
	Super::OnEnter(Unit);

	if(Unit)
	{
		UUnitAnimInstance* AnimInstance = Cast<UUnitAnimInstance>(Unit->GetMesh()->GetAnimInstance());
		if(AnimInstance)
		{
			AnimInstance->OnDamagedAnimComplete.AddDynamic(this,&UDamagedState::DamageAnimComplete);
		}
		else
		{
			FTimerHandle Handle;
			Unit->GetWorld()->GetTimerManager().SetTimer(Handle,this,&UDamagedState::DamageAnimComplete,.6f);
		}
		Unit->PlayHitMontage();
	}
	
}

void UDamagedState::OnReturn(AUnit* Unit)
{
	Super::OnReturn(Unit);
	
}

void UDamagedState::OnLeave(AUnit* Unit)
{
	Super::OnLeave(Unit);
	UUnitAnimInstance* AnimInstance = Cast<UUnitAnimInstance>(AssignedUnit->GetMesh()->GetAnimInstance());
	if(AnimInstance)
	{
		AnimInstance->OnDamagedAnimComplete.RemoveDynamic(this,&UDamagedState::DamageAnimComplete);
	}
}

void UDamagedState::DamageAnimComplete()
{
	UUnitAnimInstance* AnimInstance = Cast<UUnitAnimInstance>(AssignedUnit->GetMesh()->GetAnimInstance());
	if(AnimInstance)
	{
		AnimInstance->OnDamagedAnimComplete.RemoveDynamic(this,&UDamagedState::DamageAnimComplete);
	}
	if(IsCurrentState())
	{
		AssignedUnit->PopState();
		return;
	}
	
	bQueueRemoval = true;
	
}
