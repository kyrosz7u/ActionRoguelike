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

bool UAAttributeComponent::IsActorAlive(AActor* Actor)
{
	return GetAttributes(Actor)->IsAlive();
}

bool UAAttributeComponent::ApplyHealthChanged(AActor* instigator, float delta)
{
	if(!GetOwner()->CanBeDamaged() || !IsAlive())
	{
		return false;
	}
	Health += delta;
	Health = FMath::Clamp(Health,0.0f, MaxHealth);
	
	OnHealthChange.Broadcast(instigator, this, Health, MaxHealth, delta);
	if(OnUIHealthChanged.IsBound())
	{
		OnUIHealthChanged.Execute(instigator, this, Health, MaxHealth, delta);
	}

	return true;
}

bool UAAttributeComponent::FulfillHealth()
{
	Health = MaxHealth;
	return true;
}

bool UAAttributeComponent::IsAlive() const
{
	return Health > 1e-2f;
}

bool UAAttributeComponent::Kill(AActor* instigator)
{
	return ApplyHealthChanged(instigator, -MaxHealth);
}

bool UAAttributeComponent::IsHealthFull() const
{
	return Health == MaxHealth;
}

float UAAttributeComponent::GetHealth() const
{
	return Health;
}

float UAAttributeComponent::GetHealthMax() const
{
	return MaxHealth;
}

float UAAttributeComponent::GetHealthPercent() const
{
	return Health / MaxHealth;
}


