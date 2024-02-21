// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/ABlackholeProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AABlackholeProjectile::AABlackholeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MovementComp->InitialSpeed = 512.f;
	MovementComp->MaxSpeed = 1024.f;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->Radius = 1024.f;
	RadialForceComp->ForceStrength = -300000.f;
	// 不忽略物体质量因素
	// RadialForceComp->bImpulseVelChange = false;
	// RadialForceComp->bIgnoreOwningActor = true;
}

void AABlackholeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SetLifeSpan(5.f);
}


