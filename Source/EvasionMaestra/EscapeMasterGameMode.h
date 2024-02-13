// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "EscapeMasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class EVASIONMAESTRA_API AEscapeMasterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    void BeginPlay();

	UFUNCTION()
    void PlayerDetected();

    void ShowCompletedWidget();

    void HandleLevelCompletion();

private:

    UWorld* World;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> DetectedScreenClass;

	UPROPERTY()
	UUserWidget *Detected;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CompletedScreenClass;

	UPROPERTY()
	UUserWidget *Completed;

protected:
    void ShowDetectedWidget();
    void HandleDetectionOutcome();
};
