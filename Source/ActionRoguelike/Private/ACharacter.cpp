// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacter.h"

#include "AItemInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AACharacter::AACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemInteractionComponent = CreateDefaultSubobject<UAItemInteractionComponent>("ItemInteractionComponent");

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetUsingAbsoluteRotation(true);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AACharacter::BeginPlay()
{
	Super::BeginPlay();
	RightMuzzleTrans = GetMesh()->GetSocketTransform("Muzzle_01", ERelativeTransformSpace::RTS_Actor);
}

// Called every frame
void AACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AACharacter::MoveForward(float Value)
{
	auto controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;
	
	AddMovementInput(controlRot.Vector(), Value);
}

void AACharacter::MoveRight(float Value)
{
	auto controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;
	// X Forward
	// Y Right
	// Z Up

	FVector RightVector = FRotationMatrix(controlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}

void AACharacter::Jump()
{
	Super::Jump();
	
	auto characterTrans = GetTransform();
	AddMovementInput(characterTrans.GetUnitAxis(EAxis::Z), 1.0f);
}

void AACharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackMontage);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AACharacter::PrimaryAttack_TimeElapsed, 0.2f, false);
}

void AACharacter::Interact()
{
	if(ItemInteractionComponent != nullptr)
	{
		ItemInteractionComponent->PrimaryInteract();
	}
}

// Called to bind functionality to input
void AACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AACharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AACharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AACharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AACharacter::Jump);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AACharacter::Interact);
}

void AACharacter::PrimaryAttack_TimeElapsed()
{
	auto handLocaltion = GetMesh()->GetSocketLocation("Muzzle_01");
	const auto SpawnTM = FTransform(GetControlRotation(), handLocaltion);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor(AProjectileClass, &SpawnTM, SpawnParams);
}

