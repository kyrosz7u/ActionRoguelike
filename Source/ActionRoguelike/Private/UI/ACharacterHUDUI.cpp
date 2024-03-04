// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ACharacterHUDUI.h"
#include "ACharacter.h"

void UACharacterHUDUI::ApplyHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue, float MaxValue, float Delta)
{
    CurHealth = NewValue;
    HealthPercent = NewValue/MaxValue;
    OnUIHealthChanged();
}
