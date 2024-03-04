// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\UI\AWorldAttributeBarUI.h"

#include "AAttributeComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"


void UAWorldAttributeBarUI::NativeConstruct()
{
	Super::NativeConstruct();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UAWorldAttributeBarUI::HideWidget, 2.0f, false);
}

void UAWorldAttributeBarUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateDisplayLocation();
}

void UAWorldAttributeBarUI::UpdateDisplayLocation()
{
	if(!IsValid(AttachedActor))
	{
		RemoveFromParent();
		return;
	}
	const auto player = GetOwningPlayer();
	const auto attachedActorLocation = AttachedActor->GetActorLocation() + AttachedActor->GetActorUpVector() * 75.f;
	
	FVector2D screenPosition;
	bool ret =UGameplayStatics::ProjectWorldToScreen(player, attachedActorLocation, screenPosition);
	ESlateVisibility visibility = ret ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed;

	auto viewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
	screenPosition /= viewportScale;

	FVector cameraLocation = player->GetViewTarget()->GetActorLocation();
	float DistanceFromCamera = FVector::Distance(cameraLocation, AttachedActor->GetActorLocation());
	float DistanceScale = FMath::Clamp(DistanceFromCamera / 1000.f, 0.0f, 0.5f);
	DistanceScale = 1.f - DistanceScale;
	
	DisplayContainer->SetRenderTranslation(screenPosition);
	DisplayContainer->SetRenderScale(FVector2D(DistanceScale, DistanceScale));

	const auto ActorAttr = Cast<UAAttributeComponent>(AttachedActor->GetComponentByClass(UAAttributeComponent::StaticClass()));
	if(ActorAttr)
	{
		ProgressImage->GetDynamicMaterial()->SetScalarParameterValue("ProgressRate", ActorAttr->GetHealthPercent());
	}
}

void UAWorldAttributeBarUI::HideWidget()
{
	SetVisibility(ESlateVisibility::Collapsed);
}


