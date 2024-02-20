// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ADashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AADashProjectile::AADashProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;
	// Can't AddDynamic in Construct Function
	// SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAMagicProjectile::OnComponentBeginOverlap);
	
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1500.f;
	MovementComp->MaxSpeed = 1500.f;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AADashProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this, &AADashProjectile::OnComponentHit);
	GetWorldTimerManager().SetTimer(DashDelayHandle, this, &AADashProjectile::Teleport, 0.4f, false);
}

// Called every frame
void AADashProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AADashProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation());
	if(!GetWorldTimerManager().IsTimerActive(TeleportDelayHandle))
	{
		GetWorldTimerManager().SetTimer(TeleportDelayHandle, this, &AADashProjectile::Teleport, 0.1f, false);
	}
}

void AADashProjectile::Teleport()
{
	auto instigator = this->GetInstigator();
	if (instigator)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleportEnterParticle, GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleportExitParticle, instigator->GetActorLocation());
		auto rot = UKismetMathLibrary::MakeRotFromX(GetActorForwardVector());
		auto rawRot = instigator->GetActorRotation();
		rawRot.Yaw = rot.Yaw;
		
		instigator->SetActorLocation(GetActorLocation());
		instigator->SetActorRotation(rawRot);
	}
	Destroy();
}


