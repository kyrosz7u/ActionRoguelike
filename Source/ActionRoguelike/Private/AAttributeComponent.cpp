// Fill out your copyright notice in the Description page of Project Settings.


#include "AAttributeComponent.h"

// Sets default values for this component's properties
UAAttributeComponent::UAAttributeComponent()
{
	AttackDamage = 20;
	Health = 100.0f;
	MaxHealth = 100.f;
}

UAAttributeComponent* UAAttributeComponent::GetAttributes(AActor* FromActor)
{
	return FromActor->FindComponentByClass<UAAttributeComponent>();
}

bool UAAttributeComponent::isActorAlive(AActor* Actor)
{
	return GetAttributes(Actor)->IsAlive();
}

bool UAAttributeComponent::ApplyHealthChanged(AActor* instigator, float delta)
{
	Health += delta;
	Health = FMath::Clamp(Health,0.0f, MaxHealth);
	
	OnHealthChange.Broadcast(instigator, this, Health, MaxHealth, delta);

	return true;
}

bool UAAttributeComponent::IsAlive() const
{
	return Health > 1.0f;
}

bool UAAttributeComponent::IsHealthFull() const
{
	return Health == MaxHealth;
}

float UAAttributeComponent::GetHealthMax() const
{
	return MaxHealth;
}


