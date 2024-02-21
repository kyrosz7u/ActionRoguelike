// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AProjectileBase.h"
#include "GameFramework/Actor.h"
#include "ABlackholeProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API AABlackholeProjectile : public AAProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABlackholeProjectile();

protected:
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent *RadialForceComp;

	virtual void PostInitializeComponents() override;
};
