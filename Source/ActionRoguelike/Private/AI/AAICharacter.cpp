// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AAICharacter.h"

// Sets default values
AAAICharacter::AAAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

