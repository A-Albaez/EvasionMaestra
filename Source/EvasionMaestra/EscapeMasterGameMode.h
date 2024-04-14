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

	UFUNCTION(BlueprintCallable)
    void PlayerDetected();

    void ShowCompletedWidget();

    void HandleLevelCompletion();

	UFUNCTION(BlueprintCallable)
    void ShowLoadingScreen();
	
	bool bGameProgressLoaded;
	bool bLoadingInProgress;


	void OpenLevelAndHideLoadingScreen();


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

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoadingScreenClass;
	
	UUserWidget *LoadingScreen;

protected:
	UFUNCTION(BlueprintCallable)
    void HideLoadingScreen();

    void HideWidgets();
    void ShowDetectedWidget();
    void HandleDetectionOutcome();
};
