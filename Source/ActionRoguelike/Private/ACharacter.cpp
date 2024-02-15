// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacter.h"

#include "AItemInteractionComponent.h"
#include "AAttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "ACharacterAttributeUI.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


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

	AttributeComponent = CreateDefaultSubobject<UAAttributeComponent>("AttributeComp");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	// CharacterUIBP 是在子类蓝图中设置的，父类先于子类构造，
	// 所以在这里子类还没完成构造，CharacterUIBP没有被蓝图初始化！！！
	// if(CharacterUIBP!=nullptr)
	// {
	// 	CharacterAttributeUI = NewObject<UACharacterAttributeUI>(this, CharacterUIBP);
	// 	CharacterAttributeUI->AddToViewport();
	// }
}

// Called when the game starts or when spawned
void AACharacter::BeginPlay()
{
	Super::BeginPlay();

	if(CharacterUIBP!=nullptr && CharacterAttributeUI == nullptr)
	{
		CharacterAttributeUI = NewObject<UACharacterAttributeUI>(this, CharacterUIBP);
		AttributeComponent->OnHealthChange.AddDynamic(CharacterAttributeUI, &UACharacterAttributeUI::ApplyHealthChange);
		AttributeComponent->ApplyHealthChanged(nullptr, 0);
		CharacterAttributeUI->AddToViewport();
	}
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
	if(!GetWorldTimerManager().IsTimerActive(AttackTimerHandle))
	{
		auto cameraForward = CameraComp->GetForwardVector();
		auto rot = UKismetMathLibrary::MakeRotFromX(cameraForward);
		auto rawRot = GetActorRotation();
		rawRot.Yaw = rot.Yaw;
		SetActorRotation(rawRot);
		PlayAnimMontage(PrimaryAttackMontage);
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AACharacter::PrimaryAttack_TimeElapsed, 0.2f, false);
	}
}

void AACharacter::BlackholeAbility()
{
	if(!GetWorldTimerManager().IsTimerActive(AttackTimerHandle))
	{
		auto cameraForward = CameraComp->GetForwardVector();
		auto rot = UKismetMathLibrary::MakeRotFromX(cameraForward);
		auto rawRot = GetActorRotation();
		rawRot.Yaw = rot.Yaw;
		SetActorRotation(rawRot);
		PlayAnimMontage(BlackholeAbilityMontage);
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AACharacter::BlackHoleAbility_TimeElapsed, 0.2f, false);
	}
}

void AACharacter::DashAbility()
{
	if(!GetWorldTimerManager().IsTimerActive(AttackTimerHandle))
	{
		auto cameraForward = CameraComp->GetForwardVector();
		auto rot = UKismetMathLibrary::MakeRotFromX(cameraForward);
		auto rawRot = GetActorRotation();
		rawRot.Yaw = rot.Yaw;
		SetActorRotation(rawRot);
		PlayAnimMontage(DashAbilityMontage);
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AACharacter::DashAbility_TimeElapsed, 0.2f, false);
	}
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AACharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AACharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Ability2", IE_Pressed, this, &AACharacter::BlackholeAbility);
	PlayerInputComponent->BindAction("Ability3", IE_Pressed, this, &AACharacter::DashAbility);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AACharacter::Interact);
}

void AACharacter::PrimaryAttack_TimeElapsed()
{
	auto handLocaltion = GetMesh()->GetSocketLocation("Muzzle_01");
	
	FTransform SpawnTM;
	FVector hitLoc;
	if(GetAimAt(hitLoc))
	{
		// 使用targetLoc-handLocaltion作为forward向量构造旋转
		SpawnTM = FTransform(UKismetMathLibrary::MakeRotFromX(hitLoc-handLocaltion), handLocaltion);
		DrawDebugLine(GetWorld(), handLocaltion, hitLoc, FColor::Red, false, 2.0f, 0, 1.0f);
	}
	else
	{
		SpawnTM = FTransform(UKismetMathLibrary::MakeRotFromX(hitLoc), handLocaltion);
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor(PrimaryAttackClass, &SpawnTM, SpawnParams);
}

void AACharacter::BlackHoleAbility_TimeElapsed()
{
	auto handLocaltion = GetMesh()->GetSocketLocation("Muzzle_02");
	
	FTransform SpawnTM;
	FVector hitLoc;

	if(GetAimAt(hitLoc))
	{
		// 使用targetLoc-handLocaltion作为forward向量构造旋转
		SpawnTM = FTransform(UKismetMathLibrary::MakeRotFromX(hitLoc-handLocaltion), handLocaltion);
		DrawDebugLine(GetWorld(), handLocaltion, hitLoc, FColor::Red, false, 2.0f, 0, 1.0f);
	}
	else
	{
		SpawnTM = FTransform(UKismetMathLibrary::MakeRotFromX(hitLoc), handLocaltion);
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	
	GetWorld()->SpawnActor(BlackholeAbilityClass, &SpawnTM, SpawnParams);
}

void AACharacter::DashAbility_TimeElapsed()
{
	auto handLocaltion = GetMesh()->GetSocketLocation("Muzzle_01");
	
	FTransform SpawnTM;
	FVector hitLoc;
	if(GetAimAt(hitLoc))
	{
		// 使用targetLoc-handLocaltion作为forward向量构造旋转
		SpawnTM = FTransform(UKismetMathLibrary::MakeRotFromX(hitLoc-handLocaltion), handLocaltion);
		DrawDebugLine(GetWorld(), handLocaltion, hitLoc, FColor::Red, false, 2.0f, 0, 1.0f);
	}
	else
	{
		SpawnTM = FTransform(UKismetMathLibrary::MakeRotFromX(hitLoc), handLocaltion);
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor(DashAbilityClass, &SpawnTM, SpawnParams);
}

// true: aimAtLoc = hitLoc; false: aimAtLoc = cameraLookAt
bool AACharacter::GetAimAt(FVector &aimAtLoc)
{
	auto cameraForward = CameraComp->GetForwardVector();
	
	FCollisionObjectQueryParams queryParams;
	FHitResult hit;
	FVector s = CameraComp->GetComponentLocation();
	FVector e = s + cameraForward * 5000;

	// 我的理解：Channel包括了Trace和Object两种类型
	queryParams.ObjectTypesToQuery = ECC_TO_BITFIELD(ECC_WorldStatic)|ECC_TO_BITFIELD(ECC_WorldDynamic)
		|ECC_TO_BITFIELD(ECC_Pawn)|ECC_TO_BITFIELD(ECC_PhysicsBody);

	if(GetWorld()->LineTraceSingleByObjectType(hit, s, e, queryParams))
	{
		aimAtLoc = hit.ImpactPoint;
		return true;
	}
	aimAtLoc = cameraForward;
	return false;
}


