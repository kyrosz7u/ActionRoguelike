// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AItemInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UAItemInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAItemInteractionComponent();
	
	void PrimaryInteract();
};
