// Fill out your copyright notice in the Description page of Project Settings.


#include "AAttributeComponent.h"

// Sets default values for this component's properties
UAAttributeComponent::UAAttributeComponent()
{
	Health = 100.0f;
	MaxHealth = 100.f;
}


// Called when the game starts
void UAAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAAttributeComponent::ApplyHealthChanged(AActor* instigator, float delta)
{
	Health += delta;
	Health = FMath::Clamp(Health,0.0f, MaxHealth);
	
	OnHealthChange.Broadcast(instigator, this, Health, MaxHealth, delta);
}

bool UAAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

