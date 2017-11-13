// nemozenitkodirnitovo

#include "OpenDoor.h"
#include "Engine/World.h"
#include "Gameframework/Actor.h"



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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	// Set the door rotation
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	// Set the door rotation
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,  TickType, ThisTickFunction);

	// Poll the Trigger Volume  (check continually for colisions with the pressure plate)
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		// If ActorThatOpens is in the volume
		OpenDoor();
		LastTimeDoorOpened = GetWorld()->GetTimeSeconds();
	}
	
	// check if door need to be closed
	if ((GetWorld()->GetTimeSeconds()) >= LastTimeDoorOpened + DoorCloseDelay)
	{
		CloseDoor();
	}
}

