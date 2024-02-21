// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ADashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
AADashProjectile::AADashProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Can't AddDynamic in Construct Function
	// SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAMagicProjectile::OnComponentBeginOverlap);
	
	MovementComp->InitialSpeed = 1500.f;
	MovementComp->MaxSpeed = 1500.f;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

}

// Called when the game starts or when spawned
void AADashProjectile::BeginPlay()
{
	Super::BeginPlay();
	// SphereComp->OnComponentHit.AddDynamic(this, &AADashProjectile::OnComponentHit);
	GetWorldTimerManager().SetTimer(DashDelayHandle, this, &AADashProjectile::Teleport, 0.4f, false);
}

void AADashProjectile::Explode_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), FRotator::ZeroRotator, FVector(0.5f));
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	UGameplayStatics::PlayWorldCameraShake(this, HitShake, GetActorLocation(), HitShakeInnerRadius, HitShakeOuterRadius);
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

		auto pc = Cast<APlayerController>(instigator->GetInstigatorController());
		if(pc && pc->IsLocalController())
		{
			pc->ClientStartCameraShake(HitShake);
		}
	}
	Destroy();
}


