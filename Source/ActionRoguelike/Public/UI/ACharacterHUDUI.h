// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ACharacterHUDUI.generated.h"

class AACharacter;
class UAAttributeComponent;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UACharacterHUDUI : public UUserWidget
{
	GENERATED_BODY()
    
public:
	UFUNCTION()
    void ApplyHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue, float MaxValue, float Delta);

protected:
    UPROPERTY(BlueprintReadOnly, Category="UIAttributes")
    float CurHealth;

    UPROPERTY(BlueprintReadOnly, Category="UIAttributes")
    float HealthPercent;

	UFUNCTION(BlueprintImplementableEvent ,Category="UIEvent")
	void OnUIHealthChanged();
};
