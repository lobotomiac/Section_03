 // nemozenitkodirnitovo

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest OnOpenRequest;

private:
	// creates Unchangable menu in OpenDoor component
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 90.0f;

	// creates trigger for OpenDoor component
	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate = nullptr;

	// Delays the door closing by .f seconds
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;
 
	AActor *Door;
	
	float LastTimeDoorOpened;

	// total amount of weight on pressure plate
	float TotalTriggerMass();
};
