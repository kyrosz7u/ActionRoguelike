// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AWorldAttributeBarUI.generated.h"

class UImage;
class USizeBox;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UAWorldAttributeBarUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category="UIAttributes", meta=(ExposeOnSpawn=true))
	AActor* AttachedActor;

	UPROPERTY(BlueprintReadOnly, Category="UIAttributes")
	bool bHasRemoved = false;

	void PopUp();

protected:
	UPROPERTY(Transient, meta = (BindWidget))
	USizeBox* DisplayContainer;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(Transient, meta = (BindWidget))
	UImage* ProgressImage;
	
	FTimerHandle TimerHandle;
	
	void UpdateDisplayLocation();
	void HideWidget();
};
