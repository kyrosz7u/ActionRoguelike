// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/AActionComponent.h"

#include "GamePlay/AAction.h"

UAActionComponent::UAActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// PlayerCharacterBP构造函数未完成的时候，DefaultActions不会加载Editor里的默认设置，所以不能在这里访问
	// for (auto Action : DefaultActions)
	// {
	// 	AddAction(GetOwner(), Action);
	// }
}

void UAActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// 在这里添加默认Action
	for (auto Action : DefaultActions)
	{
		AddAction(GetOwner(), Action);
	}
}

void UAActionComponent::AddAction(AActor* Instigator, const TSubclassOf<UAAction> ActionClass)
{
	if(ActionClass)
	{
		auto NewAction = NewObject<UAAction>(GetOwner(), ActionClass);
		NewAction->Initialize(this);
		Actions.Add(NewAction);
	}
}

void UAActionComponent::RemoveAction(UAAction* ActionToRemove)
{
	if(!ensure(ActionToRemove)) return;
	Actions.Remove(ActionToRemove);
}

UAAction* UAActionComponent::GetAction(const TSubclassOf<UAAction> ActionClass) const
{
	for (UAAction* Action : Actions)
	{
		if (Action && Action->IsA(ActionClass))
		{
			return Action;
		}
	}

	return nullptr;
}

bool UAActionComponent::StartActionByName(AActor* Instigator, const FName ActionName)
{
	for(UAAction* Action : Actions)
	{
		if(Action && Action->ActionName == ActionName)
		{
			Action->StartAction(Instigator);
			return true;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("StartActionByName. Action not found: %s"), *ActionName.ToString());
	return false;
}

bool UAActionComponent::StopActionByName(AActor* Instigator, const FName ActionName)
{
	for(UAAction* Action : Actions)
	{
		if(Action && Action->ActionName == ActionName)
		{
			Action->StopAction(Instigator);
			return true;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("StopActionByName. Action not found: %s"), *ActionName.ToString());
	return false;
}








