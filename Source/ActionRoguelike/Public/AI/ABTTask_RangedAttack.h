// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ABTTask_RangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UABTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="AI")
	TSubclassOf<AActor> PrimaryAttackClass;

	UPROPERTY(EditAnywhere, Category="AI")
	float FlySpeed = 1000.0f;

	UPROPERTY(EditAnywhere, Category="AI")
	float MaxBulletSpread = 3.0f;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
