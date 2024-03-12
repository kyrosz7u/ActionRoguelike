// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/AAction.h"

void UAAction::Initialize(UAActionComponent* InActionComp)
{
	OwnerComp = InActionComp;
}

UWorld* UAAction::GetWorld() const
{
	const AActor *Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}
	return nullptr;
}

void UAAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Action Started: %s"), *GetNameSafe(this));
}

void UAAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Action Stopped: %s"), *GetNameSafe(this));
}



