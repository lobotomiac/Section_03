// nemozenitkodirnitovo

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// creates Unchangable menu in OpenDoor component
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 90.0f;

	// creates trigger for OpenDoor component
	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate = NULL;

	// 
	UPROPERTY(EditAnywhere)
	AActor *ActorThatOpens; 
};
