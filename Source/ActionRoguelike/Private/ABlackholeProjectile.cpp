// Fill out your copyright notice in the Description page of Project Settings.

#include "ABlackholeProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AABlackholeProjectile::AABlackholeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");

	RootComponent = SphereComp;
	ParticleComp->SetupAttachment(RootComponent);
	RadialForceComp->SetupAttachment(RootComponent);

	MovementComp->InitialSpeed = 500.f;
	MovementComp->MaxSpeed = 500.f;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	RadialForceComp->Radius = 256.f;
	RadialForceComp->ForceStrength = -1000.f;
	// 不忽略物体质量因素
	RadialForceComp->bImpulseVelChange = false;
	RadialForceComp->bIgnoreOwningActor = true;
}

void AABlackholeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AABlackholeProjectile::OnComponentBeginOverlap);
}

void AABlackholeProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

// Called when the game starts or when spawned
void AABlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

