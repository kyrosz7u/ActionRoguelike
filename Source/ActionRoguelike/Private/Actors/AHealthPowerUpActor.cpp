// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AHealthPowerUpActor.h"
#include "AAttributeComponent.h"

void AAHealthPowerUpActor::Interact_Implementation(APawn* InstigatorPawn)
{
	if(!ensure(InstigatorPawn))
	{
		return ;
	}

	auto AttributeComp = InstigatorPawn->FindComponentByClass<UAAttributeComponent>();
	
	if(ensure(AttributeComp) && !AttributeComp->IsHealthFull())
    {
        auto ret = AttributeComp->ApplyHealthChanged(this, AttributeComp->GetHealthMax());
		if(ret)
		{
			HideAndCooldownPowerup();
		}
    }
}
