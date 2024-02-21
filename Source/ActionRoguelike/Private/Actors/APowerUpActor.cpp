// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/APowerUpActor.h"

#include "Components/SphereComponent.h"

// Sets default values
AAPowerUpActor::AAPowerUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("PowerUpActor");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// Disable collision, instead we use SphereComp to handle interaction queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	RespawnTime = 10.0f;
	bIsActive = true;
}
// Called when the game starts or when spawned
void AAPowerUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPowerUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAPowerUpActor::OnRep_IsActive()
{
	SetActorEnableCollision(bIsActive);
	// Set visibility on root and all children
	RootComponent->SetVisibility(bIsActive, true);
}

void AAPowerUpActor::ShowPowerup()
{
	bIsActive = true;
	OnRep_IsActive();
}

void AAPowerUpActor::HideAndCooldownPowerup()
{
	bIsActive = false;
	OnRep_IsActive();

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &AAPowerUpActor::ShowPowerup, RespawnTime);
}

