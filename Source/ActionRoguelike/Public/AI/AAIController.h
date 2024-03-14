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
public:
	UFUNCTION(BlueprintCallable, Category="AI")
	bool RestartLogic();
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree *BehaviorTree;

	virtual void BeginPlay() override;
};
          