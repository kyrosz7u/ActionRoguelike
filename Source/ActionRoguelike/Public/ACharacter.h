// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "ACharacter.generated.h"

class UCharacterAttributeUI;
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
	TSubclassOf<AActor> AProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackMontage;

	FTimerHandle AttackTimerHandle;

	UPROPERTY(BlueprintReadOnly)
	USpringArmComponent *SpringArmComp;
	UPROPERTY(BlueprintReadOnly)
	UCameraComponent *CameraComp;
	UPROPERTY(BlueprintReadOnly)
	UAItemInteractionComponent *ItemInteractionComponent;

	UPROPERTY(BlueprintReadOnly, Category="Components")
	UAAttributeComponent *AttributeComponent;

	// UI
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UCharacterAttributeUI> CharacterUIBP;
	UPROPERTY(BlueprintReadOnly, Category="UI")
	UCharacterAttributeUI* CharacterAttributeUI;
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	virtual void Jump() override;
	void PrimaryAttack();
	void Interact();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void PrimaryAttack_TimeElapsed();

private:
	FTransform RightMuzzleTrans;
};
