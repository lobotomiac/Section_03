// nemozenitkodirnitovo

#include "OpenDoor.h"
#include "Engine/World.h"
#include "Gameframework/Actor.h"
#include "Grabber.h"

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
	Door = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	// Set the door rotation
	Door->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	// Set the door rotation
	Door->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,  TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (TotalTriggerMass() > 50.f)	// TODO make into a propper parameter
	{
		OpenDoor();
		LastTimeDoorOpened = GetWorld()->GetTimeSeconds();
	}
	
	// check if door need to be closed
	if ((GetWorld()->GetTimeSeconds()) >= LastTimeDoorOpened + DoorCloseDelay)
	{
		CloseDoor();
	}
}


float UOpenDoor::TotalTriggerMass()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	
	for (const auto& Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(Actor->GetName()))
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%f"), TotalMass)
	}
	return TotalMass;
}