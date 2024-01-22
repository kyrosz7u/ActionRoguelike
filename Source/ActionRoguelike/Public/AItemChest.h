// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "AItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AAItemChest : public AActor, public IAGameplayInterface
{
	GENERATED_BODY()
	
	void Interact_Implementation(APawn* InstigatorPawn);
	
public:
	// Sets default values for this actor's properties
	AAItemChest();

protected:
	UPROPERTY(EditAnywhere)
	float LidOpenAngle = 110.0f;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
