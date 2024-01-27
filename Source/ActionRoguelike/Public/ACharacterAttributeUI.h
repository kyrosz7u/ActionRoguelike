// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ACharacterAttributeUI.generated.h"

class AACharacter;
class UAAttributeComponent;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UACharacterAttributeUI : public UUserWidget
{
	GENERATED_BODY()
    
public:
	UFUNCTION()
    void ApplyHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue, float MaxValue);

protected:
    UPROPERTY(BlueprintReadOnly, Category="UIAttributes")
    FText HealthStr;

    UPROPERTY(BlueprintReadOnly, Category="UIAttributes")
    float HealthPercent;
};
