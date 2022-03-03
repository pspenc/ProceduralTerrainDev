// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/BlendSpace1D.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "Unit.generated.h"


class UUnitState;

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Melee,
	Ranged
};

USTRUCT()
struct FMyStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	USkeletalMesh* UnitMesh;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Stats")
	float Health;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Stats")
	float AttackPower;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Stats")
	float AttackCooldown;


	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Animation")
	UAnimSequence* IdleAnimation;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Animation")
	UAnimMontage* HitAnimationMontage;
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Animation")
	UBlendSpace1D* MovementBlendspace;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStateStackChanged);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChange, float, NewHealth);

UCLASS()
class STATEPATTERN_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnit();
	
	
	virtual void PostInitializeComponents() override;
	UFUNCTION(BlueprintCallable)
	void PopState();
	UFUNCTION(BlueprintCallable)
	void PushState(UUnitState* State);

	UFUNCTION(BlueprintCallable)
	bool Attack();
	UFUNCTION(BlueprintCallable)
	bool TryJump();

	UFUNCTION(BlueprintPure)
	UUnitState* GetCurrentState() const;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBlendSpace1D* MovementBlendSpace;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimSequence* IdleAnim;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FName UnitName;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
    TSubclassOf<UUnitState> AttackStateClass;

	UPROPERTY(EditAnywhere)
	EAttackType AttackType;

	UFUNCTION(BlueprintCallable)
	void PlayAttackMontage();
	UFUNCTION(BlueprintCallable)
	void PlayDeathMontage();
	UFUNCTION(BlueprintCallable)
	void PlayHitMontage();
	
	UFUNCTION()
	void MeleeHitbox();
	UFUNCTION()
	void FireRanged();

	/**
	* Apply damage to this actor.
	* @see https://www.unrealengine.com/blog/damage-in-ue4
	* @param DamageAmount		How much damage to apply
	* @param DamageEvent		Data package that fully describes the damage received.
	* @param EventInstigator	The Controller responsible for the damage.
	* @param DamageCauser		The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	* @return					The amount of damage actually applied.
	*/
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChange OnHealthChange;
	UPROPERTY(BlueprintAssignable)
	FOnStateStackChanged OnStateStackChanged;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"),Category = "Stats")
	float MaxHealth;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"),Category = "Stats")
	float Health;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"),Category = "Stats")
	float AttackPower;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"),Category = "Stats")
	float AttackCooldown;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"),Category = "Stats")
	float MoveSpeed;

	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"),Category = "Attack")
	float MeleeHitboxRadius;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"),Category = "Attack")
	float MeleeForwardOffset;

	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "State")
	TSubclassOf<UUnitState> StartingStateClass;
	UPROPERTY(BlueprintReadOnly,Category = "State")
	TArray<UUnitState*> StateStack;
	UPROPERTY(BlueprintReadOnly,Category = "State")
	UUnitState* CurrentState;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"),Category = "Montage")
	TArray<UAnimMontage*> HitMontages;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"),Category = "Montage")
	TArray<UAnimMontage*> AttackMontages;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"),Category = "Montage")
	TArray<UAnimMontage*> DeathMontages;

	void SetHealth(float NewHealth);

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bDebugMode;
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetHealth() const {return Health;}
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetAMaxHealth() const {return MaxHealth;}
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetAttackPower() const {return AttackPower;}
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetAttackCooldown() const {return AttackCooldown;}
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetMoveSpeed() const {return MoveSpeed;}
	
};

