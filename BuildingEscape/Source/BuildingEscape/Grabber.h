// Copyright Braeden Brettin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// How far ahead of the player can we reach in cm
	float Reach = 100.f;
	
	// handles grabbing and releasing components
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	// handles user input
	UInputComponent* InputComponent = nullptr;

	// Find attached physics handle
	void FindPhysicsHandleComponent();

	// Look for attached Input Component (only appears at run time)
	void SetupInputComponent();

	// Ray-cast and grab what's in reach
	void Grab();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// Return the start point of the component
	FVector GetReachLineStart();

	// Return the end point of the component's grabbing reach
	FVector GetReachLineEnd();

	// Releases the physics handle
	void Release();
};
