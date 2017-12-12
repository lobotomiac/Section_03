// nemozenitkodirnitovo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
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
	// How far can the player reach in cm
	float Reach = 100.f;
	///  Ray Cast neccesities (view position and orientation)
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	UInputComponent *InputComponent = nullptr;

	// Ray cast and grab whats in reach
	void Grab();

	// Releases the grabbed object (button)
	void Release();

	// FInd (assumed) attached physics handle
	void FindPhysicsHandleComponent();

	// Setup (assumed) attached input component
	void SetupInputComponent();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// Return the Trace Line start
	FVector GetTraceLineStart();

	// Return the range of players reach (TraceLine) for interaction purposes
	FVector GetTraceLineEnd();		
	float TotalTriggerMass();
};
