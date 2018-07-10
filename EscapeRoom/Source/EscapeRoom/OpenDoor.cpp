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
	Door = GetOwner(); // finds the owning Actor
	if (!Door) { return; }
	if (!PressurePlate)
		UE_LOG(LogTemp, Error, TEXT("%s missing a trigger volume"), *(GetOwner()->GetName()))
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,  TickType, ThisTickFunction);

	// Poll the Trigger Volume
	
	if (TotalTriggerMass() > TriggerMass)
		OnOpen.Broadcast();
	else
		OnClose.Broadcast();
	
}


float UOpenDoor::TotalTriggerMass()
{
	float TotalMass = 0.0f;

	TArray<AActor*> OverlappingActors;
	if (!PressurePlate)	{	return TotalMass;	}
	
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	
	for (const auto* Actor : OverlappingActors)
	{
		// mouse over OverlappingActors
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(Actor->GetName()))
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%f"), TotalMass)
	}
	return TotalMass;
}