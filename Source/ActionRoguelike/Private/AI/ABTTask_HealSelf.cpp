// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ABTTask_HealSelf.h"

#include "GamePlay/AAttributeComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UABTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if(ensure(AIController))
	{
		ACharacter* AIPawn = Cast<ACharacter>(AIController->GetPawn());
		if(AIPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		auto AttrComp = Cast<UAAttributeComponent>(AIPawn->GetComponentByClass(UAAttributeComponent::StaticClass()));
		if(AttrComp == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		AttrComp->FulfillHealth();
	}
	return EBTNodeResult::Succeeded;
}
