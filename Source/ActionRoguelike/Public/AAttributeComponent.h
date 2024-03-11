// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnAttrChanged, AActor*, InstigatorActor, UAAttributeComponent*, OwningComp, float, NewValue, float, MaxValue, float, Delta);

DECLARE_DELEGATE_FiveParams(FOnUIHealthChanged, AActor*, UAAttributeComponent*, float, float, float);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), DisplayName="Attribute Component")
class ACTIONROGUELIKE_API UAAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnUIHealthChanged OnUIHealthChanged;
	
public:	
	// Sets default values for this component's properties
	UAAttributeComponent();

	static UAAttributeComponent* GetAttributes(AActor* FromActor);

	static bool IsActorAlive(AActor* Actor);

	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnAttrChanged OnHealthChange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float AttackDamage;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool Kill(AActor* instigator);

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool IsHealthFull() const;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	float GetHealthMax() const;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChanged(AActor* instigator, float delta);

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool FulfillHealth();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float MaxHealth;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Health;
	
};
