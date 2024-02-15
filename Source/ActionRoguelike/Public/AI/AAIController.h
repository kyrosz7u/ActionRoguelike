// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AAIController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AAAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree *BehaviorTree;

	virtual void BeginPlay() override;
};
          