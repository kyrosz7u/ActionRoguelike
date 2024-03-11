// Fill out your copyright notice in the Description page of Project Settings.


#include "AItemInteractionComponent.h"

#include "Actors/AGameplayInterface.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UAItemInteractionComponent::UAItemInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAItemInteractionComponent::PrimaryInteract()
{
	TArray<FHitResult> hits;
	FCollisionShape shape;
	FVector s;

	auto o =GetOwner();
	auto CameraComp = o->FindComponentByClass<UCameraComponent>();
	if(CameraComp == nullptr)
	{
		return ;
	}

	s = CameraComp->GetComponentLocation();
	FVector e = s + CameraComp->GetForwardVector() * 1000;
	
	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	GetWorld()->SweepMultiByObjectType(hits, s, e, FQuat::Identity, params, shape);

	for(auto hit: hits)
	{
		auto a = hit.GetActor();

		if(a != nullptr)
		{
			if(a->Implements<UAGameplayInterface>())
			{
				IAGameplayInterface::Execute_Interact(a, Cast<APawn>(o));
				// DrawDebugSphere(GetWorld(), hit.ImpactPoint, 10.0f, 32, FColor::Blue, false, 2.0f);
				break;
			}
		}
	}

	// DrawDebugLine(GetWorld(), s, e, FColor::Red, false, 2.0f, 0, 1.0f);
}

