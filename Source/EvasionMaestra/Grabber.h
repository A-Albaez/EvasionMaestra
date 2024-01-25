// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Grabber.generated.h"

class APrisonerCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVASIONMAESTRA_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Try to grab the nearest object with the Grabbable component
	UFUNCTION(BlueprintCallable, Category = "Grabber")
	void GrabObject();

	// Release the grabbed object
	UFUNCTION(BlueprintCallable, Category = "Grabber")
	void ReleaseObject();

	// Update the position and rotation of the grabbed object
	UFUNCTION(BlueprintCallable, Category = "Grabber")
	void UpdateGrabbedObject();

	class APrisonerCharacter* PrisonerCharacter;

	const FName RightHandSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool CanHackDoor;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	// The grabbed object
	AActor* GrabbedObject;

	// The distance to grab objects
	float GrabDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grab", meta = (AllowPrivateAccess = "true"))
	bool bIsGrabbing;

	void UpdateHandReference();
	USkeletalMeshComponent* Hand;

};
