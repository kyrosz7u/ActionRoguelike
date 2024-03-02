// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AMagicProjectile.h"
#include "AAttributeComponent.h"
#include "ACharacter.h"
#include "Components/AudioComponent.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
AAMagicProjectile::AAMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Can't AddDynamic in Construct Function
	// SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAMagicProjectile::OnComponentBeginOverlap);
	MovementComp->InitialSpeed = 2000.f;
	MovementComp->MaxSpeed = 2000.f;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

void AAMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAMagicProjectile::OnComponentBeginOverlap);
}

// UPrimitiveComponent, OnComponentBeginOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult
void AAMagicProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		UAAttributeComponent* Comp = Cast<UAAttributeComponent>(OtherActor->GetComponentByClass(UAAttributeComponent::StaticClass()));

		if(Comp != nullptr)
		{
			Comp->ApplyHealthChanged(this, -1.0f);
		}
	}
}

// UPrimitiveComponent, OnComponentHit, UPrimitiveComponent*, HitComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, FVector, NormalImpulse, const FHitResult&, Hit 
void AAMagicProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		UAAttributeComponent* Comp = Cast<UAAttributeComponent>(OtherActor->GetComponentByClass(UAAttributeComponent::StaticClass()));
		if(Comp != nullptr)
		{
			Comp->ApplyHealthChanged(GetInstigator(), -1.0f*BaseDamage);
		}
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation(), FRotator::ZeroRotator, FVector(0.5f));
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

	const auto PlayerCharacter = Cast<ACharacter>(OtherActor);
	if(PlayerCharacter)
	{
		auto pc = Cast<APlayerController>(PlayerCharacter->GetController());
		if(pc && pc->IsLocalController())
		{
			pc->ClientStartCameraShake(HitShake);
		}
	}
	
	Destroy();
}

