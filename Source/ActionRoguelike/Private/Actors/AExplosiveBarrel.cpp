// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AExplosiveBarrel.h"

#include "AAttributeComponent.h"
#include "AGameModeBase.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AAExplosiveBarrel::AAExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("staticMesh");
	RootComponent = staticMesh;

	radialForce = CreateDefaultSubobject<URadialForceComponent>("radialForce");
	radialForce->SetupAttachment(staticMesh);
}

// Called when the game starts or when spawned
void AAExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void AAExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	staticMesh->OnComponentHit.AddDynamic(this, &AAExplosiveBarrel::Onhit);
}

// Called every frame
void AAExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/Physics/Collision/Overview/
void AAExplosiveBarrel::Onhit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor!=nullptr)
	{
		UAAttributeComponent* comp = Cast<UAAttributeComponent>(OtherActor->GetComponentByClass(UAAttributeComponent::StaticClass()));
		if(comp != nullptr)
		{
			UE_LOG(LogActionRoguelike, Warning, TEXT("Barrel boom! Hit %s"), *OtherActor->GetName());
			comp->ApplyHealthChanged(this, -20.0f);
			radialForce->FireImpulse();
		}
	}
}

void AAExplosiveBarrel::Explode()
{
	radialForce->FireImpulse();
}

