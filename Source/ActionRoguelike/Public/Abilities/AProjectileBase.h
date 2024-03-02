// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AProjectileBase.generated.h"

class USoundCue;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API AAProjectileBase : public AActor
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void SetBaseDamage(float NewBaseDamage) { BaseDamage = NewBaseDamage; }
	
	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                            FVector NormalImpulse, const FHitResult& Hit);

	// BlueprintNativeEvent = C++ base implementation, can be expanded in Blueprints
	// BlueprintCallable to allow child classes to trigger explosions
	// Not required for assignment, useful for expanding in Blueprint later on
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent *MovementComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *ParticleComp;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent *AttachedAudioComponent;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	float BaseDamage;

	UPROPERTY(EditAnywhere, Category="Effects|VFX")
	UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, Category = "Effects|Sound Cue")
	USoundCue *FlySound;
	
	UPROPERTY(EditAnywhere, Category = "Effects|Sound Cue")
	USoundCue *HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Camera Shake")
	TSubclassOf<UCameraShakeBase> HitShake;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Camera Shake")
	float HitShakeInnerRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Camera Shake")
	float HitShakeOuterRadius;

public:	
	// Sets default values for this actor's properties
	AAProjectileBase();
	
protected:
	virtual void PostInitializeComponents() override;
};
