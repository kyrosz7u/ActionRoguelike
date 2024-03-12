// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AAction.generated.h"

class UAActionComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class ACTIONROGUELIKE_API UAAction : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void Initialize(UAActionComponent* InActionComp);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

	virtual UWorld* GetWorld() const override;
	
protected:

public:
	// AActionComponent在执行Start/StopActionByName时会通过ActionName来查找对应的Action对象
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

private:
	UPROPERTY()
	UAActionComponent* OwnerComp;
};
