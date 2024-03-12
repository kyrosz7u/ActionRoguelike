// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlay/AAction.h"
#include "AAbilityAction.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UAAbilityAction : public UAAction
{
	GENERATED_BODY()

public:
	UAAbilityAction();
	
	virtual void StartAction_Implementation(AActor* Instigator) override;
	
protected:
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> AbilityClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AbilityMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	FName HandSocketName;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

private:
	FTimerHandle TimerHandle_AttackDelay;

	bool GetCharacterAimAt(FVector cameraForward, FVector CameraLocation, FVector& aimAtLoc);
};
