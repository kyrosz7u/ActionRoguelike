// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "APowerUpActor.generated.h"

class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API AAPowerUpActor : public AActor, public IAGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAPowerUpActor();

	virtual void Tick(float DeltaTime) override;
	void OnRep_IsActive();
	void ShowPowerup();
	void HideAndCooldownPowerup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Powerup")
	float RespawnTime;

	bool bIsActive;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

private:
	FTimerHandle TimerHandle_RespawnTimer;
};
