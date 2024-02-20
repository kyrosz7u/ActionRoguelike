// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMagicProjectile.generated.h"

class USoundCue;
class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API AAMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMagicProjectile();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent *MovementComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *ParticleComp;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent *AttachedAudioComponent;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, Category = "Sound Cue")
	USoundCue *FlySound;
	
	UPROPERTY(EditAnywhere, Category = "Sound Cue")
	USoundCue *HitSound;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
										UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
