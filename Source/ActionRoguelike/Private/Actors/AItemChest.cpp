// Fill out your copyright notice in the Description page of Project Settings.
#include "Actors/AItemChest.h"

// Sets default values
AAItemChest::AAItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	RootComponent = BaseMesh;
	LidMesh->SetupAttachment(BaseMesh);

}

// Called when the game starts or when spawned
void AAItemChest::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(LidOpenAngle, 0.0f, 0.0f));
}

