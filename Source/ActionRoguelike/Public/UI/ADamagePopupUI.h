// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ADamagePopupUI.generated.h"

class UTextBlock;

UCLASS()
class ACTIONROGUELIKE_API UADamagePopupUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	// https://www.cnblogs.com/sin998/p/15390903.html
	UPROPERTY(Transient, meta=(BindWidget))
	UTextBlock *DamageText;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation *PulseAnim;

	UPROPERTY(BlueprintReadWrite, Category="UIAttributes", meta=(ExposeOnSpawn=true))
	AActor* AttachedActor;

	UPROPERTY(BlueprintReadWrite, Category="UIAttributes", meta=(ExposeOnSpawn=true))
	float DamageAmount;

	UPROPERTY(EditAnywhere, Category="UIAttributes")
	float MaxOffset = 45.f;

	UPROPERTY(EditAnywhere, Category="UIAttributes")
	float Duration = 1.5f;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void UpdateDamageTextLocation() const;
	void DestroySelf();

	float TimeCreated;
	FVector2D RandomOffset;
	FTimerHandle TimerHandle;
};
