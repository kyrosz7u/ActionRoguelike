// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ABTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UABTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="AI", meta=(ClampMin="0.0", UIMin="0.0"))
	float AttackRange = 1000.0f;

	// 通过这样可以访问到blackboard中的值
	UPROPERTY(EditAnywhere, Category="BBKey")
	FBlackboardKeySelector WithinAttackRangeKey;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;	
};
