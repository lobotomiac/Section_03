// nemozenitkodirnitovo

#include "Grabber.h"
#include "EscapeRoom.h"
#include "DrawDebugHelpers.h"



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// looking for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// all works and no need to do anything thanks jesus
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component!"), *(GetOwner()->GetName()))
	}

	// looking for an input component (only appears at runtime)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has input handle!"), *(GetOwner()->GetName()))
			/// Bind the input action
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component!"), *(GetOwner()->GetName()))
	}
}


void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get Player viewpoint this tick

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("%s, %s"),*PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString())

	FVector TraceLineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	/// Draw a line to visualise algorithm
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		TraceLineEnd,
		FColor(0xFF00FF),
		false,
		0.f,
		0,
		5.f
	); 

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-cast (LineTrace) out to reach distance (basically a ray from your eye)
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		TraceLineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	/// See what I hit
	AActor *ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hitting %s"), *(ActorHit->GetName()))
	}
}

