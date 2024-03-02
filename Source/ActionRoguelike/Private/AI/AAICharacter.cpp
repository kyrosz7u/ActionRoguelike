// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AAICharacter.h"

#include "AAttributeComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"

class AAAIController;
// Sets default values
AAAICharacter::AAAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	AttributeComponent = CreateDefaultSubobject<UAAttributeComponent>("AttributeComp");
	
	AttributeComponent->AttackDamage = 5.0f;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAAICharacter::OnSeePawn);
	AttributeComponent->OnHealthChange.AddDynamic(this, &AAAICharacter::OnHealthChange);
}

void AAAICharacter::OnSeePawn(APawn* SeenPawn)
{
	// Print Pawn Name to the screen
	UE_LOG(LogTemp, Warning, TEXT("I see %s"), *SeenPawn->GetName());

	AAIController* AIController = Cast<AAIController>(GetController());

	if(AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
		BlackboardComp->SetValueAsObject("TargetActor", SeenPawn);
	}
}

void AAAICharacter::OnHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue,
	float MaxValue, float Delta)
{
	if(Delta < 0.0f && NewValue <= 0.0f)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if(AIController)
		{
			AIController->GetBrainComponent()->StopLogic("Dead");
		}
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionProfileName("Ragdoll");
		GetMesh()->SetAllBodiesSimulatePhysics(true);

		SetLifeSpan(10.0f);
	}
}
