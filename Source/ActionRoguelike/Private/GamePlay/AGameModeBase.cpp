// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/AGameModeBase.h"

#include "GamePlay/AAttributeComponent.h"
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

void AAGameModeBase::KillAll()
{
	for(TActorIterator<AAAICharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		const auto AttrCmp = (*ActorItr)->FindComponentByClass<UAAttributeComponent>();
		if(ensure(AttrCmp) && AttrCmp->IsAlive())
		{
			AttrCmp->Kill(this);
		}
	}
}


void AAGameModeBase::SpawnBots()
{
	if(BotPawnClass == nullptr || BotSpawnQuery == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BotPawnClass or BotSpawn	Query is nullptr"));
	}

	const auto MaxBots = DifficultyCurve->GetFloatValue(GetWorld()->GetTimeSeconds());
	float NumBots = 0;

	for(TActorIterator<AAAICharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		const auto AttrCmp = (*ActorItr)->FindComponentByClass<UAAttributeComponent>();
		if(AttrCmp && AttrCmp->IsAlive())
		{
			NumBots++;
		}
	}
	
	if(NumBots >= MaxBots)
	{
		return;
	}

	auto QueryInstance = UEnvQueryManager::RunEQSQuery(this, BotSpawnQuery, this, EEnvQueryRunMode::RandomBest25Pct, nullptr);

	if(QueryInstance != nullptr)
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AAGameModeBase::OnBotSpawnQueryCompleted);
	}
}

void AAGameModeBase::OnActorKilled(AActor* VictimActor, AActor* KillerActor)
{
	auto PlayerCharacter = Cast<ACharacter>(VictimActor);
	if(PlayerCharacter != nullptr)
	{
		//没有必要持有Handle，且为了防止多人游戏中handle相互覆盖，这里做成局部变量
		FTimerHandle TimerHandle_RespawnDelay;
		//Delegate用于需要传参的情况，类比于C++11的Bind函数
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", PlayerCharacter->GetController());
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, PlayerRespawnTime, false);
	}
	UE_LOG(LogTemp, Log, TEXT("OnActorKilled:Victim:%s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(KillerActor));
}


void AAGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if(ensure(Controller))
	{
		//作用之一就是将pawn成员设为null
		Controller->UnPossess();
		//如果控制器拥有一个Pawn，则获取pawn的旋转作为控制器的新旋转
		//如果控制器不拥有，则选择一个出生点，新生成一个pawn
		RestartPlayer(Controller);
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
