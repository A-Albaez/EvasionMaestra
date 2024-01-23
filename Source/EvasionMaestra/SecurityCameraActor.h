// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "SecurityCameraActor.generated.h"

class UCurveFloat;

UCLASS()
class EVASIONMAESTRA_API ASecurityCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASecurityCameraActor();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void TimelineProgress(float value);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    FTimeline CurveFTimeline;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveFloat;

	UPROPERTY( EditAnywhere, Category ="Timeline")
	float ZOffset;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> DetectedScreenClass;

	UPROPERTY(EditAnywhere)
	UUserWidget *Detected;

	UCapsuleComponent *CapsuleComp;

    UPROPERTY(EditAnywhere)
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere)
    float RotationSpeed;

    UPROPERTY(EditAnywhere)
	FRotator StartRotation;

    UPROPERTY(EditAnywhere)
    FRotator TargetRotation;

	UPROPERTY(EditAnywhere)
    FRotator DeltaRotation;

};

