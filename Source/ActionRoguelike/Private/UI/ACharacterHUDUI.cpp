// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ACharacterHUDUI.h"
#include "ACharacter.h"

void UACharacterHUDUI::ApplyHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue, float MaxValue, float Delta)
{
    CurHealth = NewValue;
    HealthPercent = NewValue/MaxValue;
    OnUIHealthChanged();
}


void UACharacterHUDUI::OnPawnChange(APawn* NewPawn)
{
    auto NewPlayerCharacter = Cast<AACharacter>(NewPawn);

    if(NewPlayerCharacter!=nullptr)
    {
        auto AttributeComponent = NewPlayerCharacter->GetComponentByClass(UAAttributeComponent::StaticClass());
        if(AttributeComponent!=nullptr)
        {
            auto AAttributeComponent = Cast<UAAttributeComponent>(AttributeComponent);
            // UE4不允许直接将UObjects的成员函数用作原始方法委托。这是因为UObjects有自己的生命周期管理，包括垃圾回收机制，而原始委托不提供足够的上下文来安全地管理UObjects引用的生命周期。
            // AAttributeComponent->OnUIHealthChanged.BindRaw(this, &UACharacterHUDUI::ApplyHealthChange);
            ApplyHealthChange(nullptr, AAttributeComponent, AAttributeComponent->GetHealth(), AAttributeComponent->GetHealthMax(), 0);
            AAttributeComponent->OnUIHealthChanged.BindUFunction(this, FName("ApplyHealthChange"));
        }
        // NewPlayer->AttributeComponent->OnManaChange.AddDynamic(this, &UACharacterHUDUI::ApplyManaChange);
        // NewPlayer->AttributeComponent->OnStaminaChange.AddDynamic(this, &UACharacterHUDUI::ApplyStaminaChange);
        // NewPlayer->AttributeComponent->OnGoldChange.AddDynamic(this, &UACharacterHUDUI::ApplyGoldChange);
        // NewPlayer->AttributeComponent->OnExpChange.AddDynamic(this, &UACharacterHUDUI::ApplyExpChange);
        // NewPlayer->AttributeComponent->OnLevelChange.AddDynamic(this, &UACharacterHUDUI::ApplyLevelChange);
    }
}


