// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AAICharacter.generated.h"

class UAAttributeComponent;
class UPawnSensingComponent;

UCLASS()
class ACTIONROGUELIKE_API AAAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAAICharacter();

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(BlueprintReadOnly, Category="Components")
	UAAttributeComponent *AttributeComponent;
	
	UFUNCTION()
	void OnSeePawn(APawn* SeenPawn);

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue, float MaxValue, float Delta);
	
	virtual void PostInitializeComponents() override;
	void SetTargetActor(APawn* NewTarget);

	APawn* CachedTarget;
};
