// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "ACharacter.generated.h"

class UAItemInteractionComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONROGUELIKE_API AACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharacter();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> AProjectileClass;
	
	USpringArmComponent *SpringArmComp;
	UCameraComponent *CameraComp;
	UAItemInteractionComponent *ItemInteractionComponent;
	
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

private:
	FTransform RightMuzzleTrans;
};
