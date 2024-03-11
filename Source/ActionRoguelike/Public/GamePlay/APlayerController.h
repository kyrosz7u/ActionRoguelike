// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "APlayerController.generated.h"

/**
 * 
 */

class UACharacterHUDUI;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnRespawnSignature, APawn*, RespawnedPawn);

UCLASS()
class ACTIONROGUELIKE_API AAPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="AttributeUI")
	TSubclassOf<UACharacterHUDUI> MainHUDUIBP;
	
	FOnPawnRespawnSignature OnPawnRespawnDelegate;
	
	virtual void SetPawn(APawn* InPawn) override;

	virtual void BeginPlay() override;

private:
	UACharacterHUDUI* MainHUDUI;
};
