// Copyright Braeden Brettin

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (!PressurePlate)
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *(Owner->GetName()));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume
	// If the total mass of all actors on the pressure plate is more than the specified trigger mass, open the door
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
		OnOpen.Broadcast();
	else
		OnClose.Broadcast();
}

// Returns total mass in kg
float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate)
		return TotalMass;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them adding their masses
	for (const auto* Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("found %s"), *(Actor->GetName()));
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

