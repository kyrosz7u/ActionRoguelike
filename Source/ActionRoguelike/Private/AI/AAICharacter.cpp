// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AAICharacter.h"

#include "AAttributeComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "../../Public/UI/AWorldAttributeBarUI.h"
#include "Components/TimelineComponent.h"

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

	FOnTimelineFloat onTimelineCallback;
	onTimelineCallback.BindUFunction(this, FName("HandleDissolveProgress"));

	if(DeadDissolveCurve!=nullptr)
	{
		float TimelineLength = DeadDissolveTimeline.GetTimelineLength();
		DeadDissolveTimeline.AddInterpFloat(DeadDissolveCurve, onTimelineCallback);
		DeadDissolveTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
		DeadDissolveTimeline.SetPlayRate(1.0f / DeadDissolveTime);
		DeadDissolveTimeline.SetLooping(false);
	}
}

void AAAICharacter::BeginPlay()
{
	Super::BeginPlay();

	AAIController* AIController = Cast<AAIController>(GetController());
	ControllerBBCopm = AIController->GetBlackboardComponent();
}

void AAAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(DeadDissolveTimeline.IsPlaying())
	{
		DeadDissolveTimeline.TickTimeline(DeltaSeconds);
	}
}

void AAAICharacter::SetTargetActor(APawn* NewTarget)
{
	if(ControllerBBCopm)
	{
		ControllerBBCopm->SetValueAsObject("TargetActor", NewTarget);
		CachedTarget = NewTarget;
	}
}

void AAAICharacter::OnSeePawn(APawn* SeenPawn)
{
	// Print Pawn Name to the screen
	// UE_LOG(LogTemp, Warning, TEXT("I see %s"), *SeenPawn->GetName());
	SetTargetActor(SeenPawn);
}

void AAAICharacter::HandleDissolveProgress(float Ratio)
{
	GetMesh()->SetScalarParameterValueOnMaterials("DissolveAmount", Ratio);
}

void AAAICharacter::OnHealthChange(AActor* InstigatorActor, UAAttributeComponent* OwningComp, float NewValue,
	float MaxValue, float Delta)
{
	if(Delta < 0.0f)
	{
		if(InstigatorActor && InstigatorActor != CachedTarget)
		{
			SetTargetActor(Cast<APawn>(InstigatorActor));
		}

		if(!IsValid(ActiveHealthBar))
		{
			if(HealthBarClass != nullptr)
			{
				ActiveHealthBar = CreateWidget<UAWorldAttributeBarUI>(GetWorld(), HealthBarClass);
				ActiveHealthBar->AttachedActor = this;
				ActiveHealthBar->AddToViewport();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("HealthBarClass Of AAICharacter is nullptr"));
			}
		}
		else if(ActiveHealthBar->Visibility == ESlateVisibility::Collapsed)
		{
			ActiveHealthBar->PopUp();
		}
	}
	
	if(NewValue <= 0.0f)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if(AIController)
		{
			AIController->GetBrainComponent()->StopLogic("Dead");
		}
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionProfileName("Ragdoll");
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		ActiveHealthBar->SetVisibility(ESlateVisibility::Collapsed);

		SetLifeSpan(DeadDissolveTime);
		DeadDissolveTimeline.PlayFromStart();
	}

	if(AttributeComponent->GetHealthPercent() < 0.41f)
	{
		ControllerBBCopm->SetValueAsBool("LowHealth", true);
	}
	else
	{
		ControllerBBCopm->SetValueAsBool("LowHealth", false);
	}
}
