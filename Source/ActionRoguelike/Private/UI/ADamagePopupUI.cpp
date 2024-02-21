// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ADamagePopupUI.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/TextBlock.h"

void UADamagePopupUI::NativeConstruct()
{
	Super::NativeConstruct();

	DamageText->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), DamageAmount)));
	
	TimeCreated = GetWorld()->GetTimeSeconds();
	RandomOffset = FVector2D(FMath::RandRange(-MaxOffset, MaxOffset), FMath::RandRange(-MaxOffset, 0.0f));

	PlayAnimation(PulseAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UADamagePopupUI::DestroySelf, Duration, false);
}

void UADamagePopupUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateDamageTextLocation();
}

void UADamagePopupUI::UpdateDamageTextLocation() const
{
	if(AttachedActor == nullptr)
	{
		return ;
	}
	const auto player = GetOwningPlayer();
	const auto attachedActorLocation = AttachedActor->GetActorLocation();

	FVector2D screenPosition;
	bool ret =UGameplayStatics::ProjectWorldToScreen(player, attachedActorLocation, screenPosition);
	ESlateVisibility visibility = ret ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed;

	auto viewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
	screenPosition /= viewportScale;
	auto offset = RandomOffset * (GetWorld()->GetTimeSeconds() - TimeCreated) / Duration;

	DamageText->SetRenderTranslation(screenPosition + offset);
	DamageText->SetVisibility(visibility);
}

void UADamagePopupUI::DestroySelf()
{
	RemoveFromParent();
}
