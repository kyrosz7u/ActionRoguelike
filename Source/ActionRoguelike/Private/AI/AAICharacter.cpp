// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AAICharacter.h"

#include "AAttributeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

class AAAIController;
// Sets default values
AAAICharacter::AAAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	AttributeComponent = CreateDefaultSubobject<UAAttributeComponent>("AttributeComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AAAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAAICharacter::OnSeePawn);
}

// Called every frame
void AAAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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
