// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameSave.h"
#include "EscapeMasterPlayerController.generated.h"

/**
 * 
 */

class APrisonerCharacter;

UCLASS()
class EVASIONMAESTRA_API AEscapeMasterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    void BeginPlay() override;

public:
    // Increment the level upon completion
    UFUNCTION(BlueprintCallable)
    void LevelCompleted();

    // Save game progress after completing a level
    void SaveGameProgress(UGameSave *GameSaveInstance);

    // Load game progress when the game starts
    void LoadGameProgress();

    // Show completed objective
    void PlayerCompletedObjective();

private:
    // Current level
    int32 CurrentLevel = 1;

    // Reference to the Prisoner character
    UPROPERTY()
    APrisonerCharacter* PrisonerCharacter = nullptr;
};
