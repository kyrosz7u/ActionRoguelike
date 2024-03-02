// Fill out your copyright notice in the Description page of Project Settings.


#include "AGameModeBase.h"

#include "AAttributeComponent.h"
#include "EngineUtils.h"
#include "AI/AAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

DEFINE_LOG_CATEGORY(LogActionRoguelike);

AAGameModeBase::AAGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void AAGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AAGameModeBase::SpawnBots, SpawnTimerInterval, true);
}


void AAGameModeBase::SpawnBots()
{
	if(BotPawnClass == nullptr || BotSpawnQuery == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BotPawnClass or BotSpawn	Query is nullptr"));
	}

	auto maxBots = DifficultyCurve->GetFloatValue(GetWorld()->GetTimeSeconds());
	float numBots = 0;

	for(TActorIterator<AAAICharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		auto attrCmp = (*ActorItr)->FindComponentByClass<UAAttributeComponent>();
		if(attrCmp && attrCmp->IsAlive())
		{
			numBots++;
		}
	}
	
	if(numBots >= maxBots)
	{
		return;
	}

	auto QueryInstance = UEnvQueryManager::RunEQSQuery(this, BotSpawnQuery, this, EEnvQueryRunMode::RandomBest25Pct, nullptr);

	if(QueryInstance != nullptr)
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AAGameModeBase::OnBotSpawnQueryCompleted);
	}
}

void AAGameModeBase::OnBotSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		return;
	}
	auto locations = QueryInstance->GetResultsAsLocations();
	GetWorld()->SpawnActor(BotPawnClass, &locations[0]);
}
