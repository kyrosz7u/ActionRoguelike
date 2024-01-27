// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterAttributeUI.generated.h"

class UAAttributeComponent;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UCharacterAttributeUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="SourceCharacter")
	ACharacter *src;
protected:
 //    UFUNCTION()
	// void Construct();

	UPROPERTY(BlueprintReadOnly, Category="UIAttributes")
	float Health;

	UPROPERTY(BlueprintReadOnly, Category="UIAttributes")
	float HealthPercent;
	
	
	virtual void PostLoad();

	UFUNCTION()
	void ApplyHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue, float MaxValue);
};


