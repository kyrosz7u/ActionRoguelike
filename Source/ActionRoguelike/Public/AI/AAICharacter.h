// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "AAICharacter.generated.h"

class UTimelineComponent;
class UAWorldAttributeBarUI;
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

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> HealthBarClass;

	UPROPERTY(EditDefaultsOnly, Category="Effect")
	UCurveFloat *DeadDissolveCurve;

	UPROPERTY(EditDefaultsOnly, Category="Effect")
	float DeadDissolveTime = 5.0f;
	
	UFUNCTION()
	void OnSeePawn(APawn* SeenPawn);

	UFUNCTION()
	void HandleDissolveProgress(float Ratio);

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue, float MaxValue, float Delta);
	
	void SetTargetActor(APawn* NewTarget);
	
	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	APawn* CachedTarget;
	UAWorldAttributeBarUI* ActiveHealthBar;
	FTimeline  DeadDissolveTimeline;
};
