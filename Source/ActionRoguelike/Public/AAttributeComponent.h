// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnAttrChanged, AActor*, InstigatorActor, UAAttributeComponent*, OwningComp, float, NewValue, float, MaxValue, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), DisplayName="Attribute Component")
class ACTIONROGUELIKE_API UAAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAAttributeComponent();

	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnAttrChanged OnHealthChange;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float MaxHealth;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Health;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool IsAlive() const;
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplyHealthChanged(AActor* instigator, float delta);
};
