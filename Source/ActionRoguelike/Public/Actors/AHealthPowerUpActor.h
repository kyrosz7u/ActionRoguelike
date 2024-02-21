// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/APowerUpActor.h"
#include "AHealthPowerUpActor.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AAHealthPowerUpActor : public AAPowerUpActor
{
	GENERATED_BODY()

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	
};
