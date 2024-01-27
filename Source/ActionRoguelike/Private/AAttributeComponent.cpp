// Fill out your copyright notice in the Description page of Project Settings.


#include "AAttributeComponent.h"

// Sets default values for this component's properties
UAAttributeComponent::UAAttributeComponent()
{
	Health = 100.0f;
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

void UAAttributeComponent::ApplyHealthChanged(float delta)
{
	Health += delta;
	OnHealthChange.Broadcast(nullptr, this, Health, MaxHealth);
}

