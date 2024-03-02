// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ABTTask_Wander.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UABTTask_Wander::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent *BlackboardComp = OwnerComp.GetBlackboardComponent();
	
	if(ensure(AIController))
	{
		ACharacter* AIPawn = Cast<ACharacter>(AIController->GetPawn());
		if(AIPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		auto AILocation = AIPawn->GetActorLocation();
		FNavLocation RandomLocation;
		bool bFound = NavSys->GetRandomReachablePointInRadius(AILocation, 500.0f, RandomLocation);
		if(bFound)
		{
			BlackboardComp->SetValueAsVector(WanderLocationKey.SelectedKeyName, RandomLocation.Location);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

