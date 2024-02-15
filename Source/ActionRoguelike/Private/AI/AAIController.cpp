// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AAAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(PlayerPawn)
	{
		GetBlackboardComponent()->SetValueAsObject("TargetActor", PlayerPawn);
	}
}
