// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ABTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UABTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent *BlackboardComp = OwnerComp.GetBlackboardComponent();
	if(ensure(BlackboardComp))
	{
		AActor *TargetCharacter = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
		AActor *AIControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
		if(TargetCharacter && AIControlledPawn)
		{
			float Distance = FVector::Distance(TargetCharacter->GetActorLocation(), AIControlledPawn->GetActorLocation());
			bool bWithinAttackRange = Distance < AttackRange;
			bool bInsignt = false;
			if(bWithinAttackRange)
			{
				bInsignt = OwnerComp.GetAIOwner()->LineOfSightTo(TargetCharacter); 
			}
			
			BlackboardComp->SetValueAsBool(WithinAttackRangeKey.SelectedKeyName, bWithinAttackRange&&bInsignt);
		}
	}
}
