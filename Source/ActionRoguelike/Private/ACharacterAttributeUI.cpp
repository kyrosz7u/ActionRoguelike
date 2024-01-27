// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacterAttributeUI.h"
#include "ACharacter.h"
#include "GameFramework/Character.h"


void UACharacterAttributeUI::ApplyHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue, float MaxValue)
{
    Health = NewValue;
    HealthPercent = NewValue/MaxValue;
}
