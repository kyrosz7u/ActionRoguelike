// Fill out your copyright notice in the Description page of Project Settings.


#include "AItemInteractionComponent.h"

#include "Actors/AGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UAItemInteractionComponent::UAItemInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAItemInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAItemInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAItemInteractionComponent::PrimaryInteract()
{
	TArray<FHitResult> hits;

	FCollisionObjectQueryParams params;
	FCollisionShape shape;
	
	FVector s;
	FRotator r;

	auto o =GetOwner();
	o->GetActorEyesViewPoint(s, r);

	FVector e = s + r.Vector() * 1000;
	
	params.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	// GetWorld()->LineTraceSingleByObjectType(hit, s, e, params);

	GetWorld()->SweepMultiByObjectType(hits, s, e, FQuat::Identity, params, shape);

	for(auto hit: hits)
	{
		auto a = hit.GetActor();

		if(a != nullptr)
		{
			if(a->Implements<UAGameplayInterface>())
			{
				IAGameplayInterface::Execute_Interact(a, Cast<APawn>(o));
				DrawDebugSphere(GetWorld(), hit.ImpactPoint, 10.0f, 32, FColor::Blue, false, 2.0f);
				break;
			}
		}
	}

	// FColor lineColor = 
	DrawDebugLine(GetWorld(), s, e, FColor::Red, false, 2.0f, 0, 1.0f);
}

