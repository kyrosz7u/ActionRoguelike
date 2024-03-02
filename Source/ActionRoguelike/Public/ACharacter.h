// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAttributeComponent.h"

#include "GameFramework/Character.h"
#include "ACharacter.generated.h"

class UACharacterAttributeUI;
class UAItemInteractionComponent;
class USpringArmComponent;
class UCameraComponent;
class UAAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API AACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharacter();

protected:
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> PrimaryAttackClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* PrimaryAttackMontage;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> BlackholeAbilityClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* BlackholeAbilityMontage;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> DashAbilityClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* DashAbilityMontage;

	FTimerHandle AttackTimerHandle;

	UPROPERTY(EditAnywhere)
	USpringArmComponent *SpringArmComp;
	UPROPERTY(EditAnywhere)
	UCameraComponent *CameraComp;
	UPROPERTY(BlueprintReadOnly)
	UAItemInteractionComponent *ItemInteractionComponent;

	UPROPERTY(BlueprintReadOnly, Category="Components")
	UAAttributeComponent *AttributeComponent;

	// UI
	UPROPERTY(EditAnywhere, Category="AttributeUI")
	TSubclassOf<UACharacterAttributeUI> CharacterUIBP;
	UPROPERTY(BlueprintReadOnly, Category="AttributeUI")
	UACharacterAttributeUI* CharacterAttributeUI; 

	// Animation
	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue, float MaxValue, float Delta);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	virtual void Jump() override;
	void PrimaryAttack();
	void BlackholeAbility();
	void DashAbility();
	void Interact();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void PrimaryAttack_TimeElapsed();
	void BlackHoleAbility_TimeElapsed();
	void DashAbility_TimeElapsed();
	bool GetAimAt(FVector& aimAtLoc);
};
