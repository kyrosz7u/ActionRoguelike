// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/AGameplayFunctionLibrary.h"

#include "GamePlay/AAttributeComponent.h"

bool UAGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	if(TargetActor == nullptr)
	{
		return false;
	}

	UAAttributeComponent* AttributeComp = UAAttributeComponent::GetAttributes(TargetActor);

	if(AttributeComp)
	{
		return AttributeComp->ApplyHealthChanged(DamageCauser, -DamageAmount);
	}

	return false;
}

bool UAGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount,
	const FHitResult& HitResult)
{
	bool ret = ApplyDamage(DamageCauser, TargetActor, DamageAmount);

	if(ret)
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		UE_LOG(LogTemp, Warning, TEXT("HitComp: %s Owner: %s"),*HitComp->GetName() , *HitComp->GetOwner()->GetName());
		if(HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			FVector Direction = HitResult.TraceEnd - HitResult.TraceStart;
			Direction.Normalize();
			HitComp->AddImpulseAtLocation(Direction * 100000.f, HitResult.ImpactPoint, HitResult.BoneName);
		}
	}

	return ret;
}
