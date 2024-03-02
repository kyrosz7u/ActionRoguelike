// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AProjectileBase.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
AAProjectileBase::AAProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(RootComponent);
	
	AttachedAudioComponent = CreateDefaultSubobject<UAudioComponent>("AttachedAudioComponent");
	AttachedAudioComponent->SetupAttachment(RootComponent);

	BaseDamage = 1.0f;
}

void AAProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttachedAudioComponent->Sound = FlySound;
	AttachedAudioComponent->bAutoActivate = true;
	AttachedAudioComponent->bAutoDestroy = true;
	AttachedAudioComponent->Play();

	SphereComp->OnComponentHit.AddDynamic(this, &AAProjectileBase::OnComponentHit);
}

void AAProjectileBase::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AAProjectileBase::Explode_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), FRotator::ZeroRotator, FVector(0.5f));
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	UGameplayStatics::PlayWorldCameraShake(this, HitShake, GetActorLocation(), HitShakeInnerRadius, HitShakeOuterRadius);
	Destroy();
}



