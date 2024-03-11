// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/GameModeBase.h"
#include "AGameModeBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogActionRoguelike, Log, All);

class AAAICharacter;
class UEnvQuery;
/**
 * 
 */

UCLASS()
class ACTIONROGUELIKE_API AAGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AAGameModeBase();

	virtual void StartPlay() override;

	UFUNCTION(Exec)
	void KillAll();

	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void OnActorKilled(AActor* VictimActor, AActor* KillerActor);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "GamePlay")
	UCurveFloat *DifficultyCurve;

	UPROPERTY(EditDefaultsOnly, Category="GamePlay")
	float PlayerRespawnTime=3.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI|Spawning Bots")
	TSubclassOf<AAAICharacter> BotPawnClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI|Spawning Bots")
	UEnvQuery* BotSpawnQuery;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI|Spawning Bots")
	float SpawnTimerInterval;

private:
	FTimerHandle TimerHandle_SpawnBots;

	UFUNCTION()
	void OnBotSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

	void SpawnBots();
};
