// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/AAbilityAction.h"

#include "ACharacter.h"
#include "Abilities/AProjectileBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

class AACharacter;

UAAbilityAction::UAAbilityAction()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;
}

void UAAbilityAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	if(Instigator == nullptr) return;
	auto character = Cast<ACharacter>(Instigator);

	if(character == nullptr) return;

	if(!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_AttackDelay))
	{
		auto cameraComp = Cast<UCameraComponent>(character->GetComponentByClass(UCameraComponent::StaticClass()));
		auto cameraForward = cameraComp->GetForwardVector();
		auto rot = UKismetMathLibrary::MakeRotFromX(cameraForward);
		auto rawRot = character->GetActorRotation();
		rawRot.Yaw = rot.Yaw;
		character->SetActorRotation(rawRot);
		character->PlayAnimMontage(AbilityMontage);
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", character);
		
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
	}
}

void UAAbilityAction::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	auto handLocaltion = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
	auto cameraComp = Cast<UCameraComponent>(InstigatorCharacter->GetComponentByClass(UCameraComponent::StaticClass()));
	
	auto cameraForward = cameraComp->GetForwardVector();
	auto cameraLocation = cameraComp->GetComponentLocation();
	
	FTransform SpawnTM;
	FVector hitLoc;
	if(GetCharacterAimAt(cameraForward, cameraLocation, hitLoc))
	{
		// 使用targetLoc-handLocaltion作为forward向量构造旋转
		SpawnTM = FTransform(UKismetMathLibrary::MakeRotFromX(hitLoc-handLocaltion), handLocaltion);
		// DrawDebugLine(GetWorld(), handLocaltion, hitLoc, FColor::Red, false, 2.0f, 0, 1.0f);
	}
	else
	{
		SpawnTM = FTransform(UKismetMathLibrary::MakeRotFromX(hitLoc), handLocaltion);
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = InstigatorCharacter;

	auto attrComp = InstigatorCharacter->FindComponentByClass<UAAttributeComponent>();
	float damage = attrComp? attrComp->AttackDamage: 1.0f;

	auto projObj = Cast<AAProjectileBase>(GetWorld()->SpawnActor(AbilityClass, &SpawnTM, SpawnParams));
	if(projObj)
	{
		projObj->SetBaseDamage(damage);
	}
}

bool UAAbilityAction::GetCharacterAimAt(FVector cameraForward, FVector CameraLocation, FVector &aimAtLoc)
{
	FCollisionObjectQueryParams queryParams;
	FHitResult hit;
	FVector e = CameraLocation + cameraForward * 5000;

	// 我的理解：Channel包括了Trace和Object两种类型
	queryParams.ObjectTypesToQuery = ECC_TO_BITFIELD(ECC_WorldStatic)|ECC_TO_BITFIELD(ECC_WorldDynamic)
		|ECC_TO_BITFIELD(ECC_Pawn)|ECC_TO_BITFIELD(ECC_PhysicsBody);

	if(GetWorld()->LineTraceSingleByObjectType(hit, CameraLocation, e, queryParams))
	{
		aimAtLoc = hit.ImpactPoint;
		return true;
	}
	aimAtLoc = cameraForward;
	return false;
}
