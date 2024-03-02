// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ABTTask_RangedAttack.h"

#include "AAttributeComponent.h"
#include "AIController.h"
#include "Abilities/AProjectileBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UABTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if(ensure(AIController))
	{
		ACharacter* AIPawn = Cast<ACharacter>(AIController->GetPawn());
		if(AIPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector MuzzleLocation = AIPawn->GetMesh()->GetSocketLocation("Muzzle_01");

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if(TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();

		// auto rot = UKismetMathLibrary::MakeRotFromX(Direction);
		// auto rawRot = AIPawn->GetActorRotation();
		// rawRot.Yaw = rot.Yaw;
		// AIPawn->SetActorRotation(rawRot);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = AIPawn;
		

		AAProjectileBase* projObj = Cast<AAProjectileBase>(GetWorld()->SpawnActor<AActor>(PrimaryAttackClass, MuzzleLocation, MuzzleRotation, SpawnParams));
		auto attrComp = AIPawn->FindComponentByClass<UAAttributeComponent>();
		if(projObj)
		{
			projObj->SetBaseDamage(attrComp->AttackDamage);
		}

		return projObj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
