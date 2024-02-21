// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AProjectileBase.h"
#include "GameFramework/Actor.h"
#include "ADashProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API AADashProjectile : public AAProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AADashProjectile();

protected:
	UPROPERTY(EditAnywhere)
	UParticleSystem* TeleportEnterParticle;

	UPROPERTY(EditAnywhere)
	UParticleSystem* TeleportExitParticle;

	FTimerHandle DashDelayHandle;
	FTimerHandle TeleportDelayHandle;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Explode_Implementation() override;

public:	
	void Teleport();
};
