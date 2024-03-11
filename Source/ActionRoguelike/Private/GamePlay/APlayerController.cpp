// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/APlayerController.h"

#include "UI/ACharacterHUDUI.h"


void AAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(MainHUDUIBP!=nullptr && MainHUDUI == nullptr)
	{
		MainHUDUI = NewObject<UACharacterHUDUI>(this, MainHUDUIBP);
		// AttributeComponent->OnHealthChange.AddDynamic(MainHUDUI, &UACharacterHUDUI::ApplyHealthChange);
		// AttributeComponent->ApplyHealthChanged(nullptr, 0);
		OnPawnRespawnDelegate.AddDynamic(MainHUDUI, &UACharacterHUDUI::OnPawnChange);
		MainHUDUI->AddToViewport();
	}

	const auto MyPawn = GetPawn();
	if(MyPawn!=nullptr)
	{
		OnPawnRespawnDelegate.Broadcast(MyPawn);
	}
}

void AAPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if(InPawn!=nullptr)
	{
		OnPawnRespawnDelegate.Broadcast(InPawn);
	}
}




