// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AAIController.h"

#include "BehaviorTree/BehaviorTree.h"

bool AAAIController::RestartLogic()
{
	if (BehaviorTree)
	{
		BrainComponent->StopLogic("RestartLogic");
		RunBehaviorTree(BehaviorTree);
		return true;
	}
	return false;
}

void AAAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("BehaviorTree is nullptr! Please assign a BehaviorTree in the AIController.")))
	{
		RunBehaviorTree(BehaviorTree);
	}

	// APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	// if(PlayerController)
	// {
	// 	ACharacter* ControlledCharacter = Cast<ACharacter>(PlayerController->GetPawn());
	// 	GetBlackboardComponent()->SetValueAsObject("TargetActor", ControlledCharacter);
	// }
}
