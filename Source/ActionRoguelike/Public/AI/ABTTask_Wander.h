// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "ABTTask_Wander.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UABTTask_Wander : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="BBKey")
	FBlackboardKeySelector WanderLocationKey; 

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
