// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacterAttributeUI.h"
#include "ACharacter.h"

void UACharacterAttributeUI::ApplyHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue, float MaxValue, float Delta)
{
    HealthStr = FText::AsNumber(NewValue);
    HealthPercent = NewValue/MaxValue;
    OnUIHealthChanged();
}
