// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttributeUI.h"

// void UCharacterAttributeUI::Construct()
// {
// }

void UCharacterAttributeUI::PostLoad()
{
	Super::PostLoad();
}

void UCharacterAttributeUI::ApplyHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue, float MaxValue)
{
	Health = NewValue;
	HealthPercent = NewValue/MaxValue;
}
