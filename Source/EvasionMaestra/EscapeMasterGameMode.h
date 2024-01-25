// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "EscapeMasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class EVASIONMAESTRA_API AEscapeMasterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
    void PlayerDetected();

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> DetectedScreenClass;

	UPROPERTY()
	UUserWidget *Detected;

protected:
    void ShowDetectedWidget();
    void HandleDetectionOutcome();
};
