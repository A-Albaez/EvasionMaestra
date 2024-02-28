// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeMasterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PrisonerCharacter.h"
#include "Grabber.h"
#include "EscapeMasterGameMode.h"
#include "GameSave.h"
#include "GameFramework/PlayerStart.h" 


void AEscapeMasterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    // Load game progress when the game starts
    LoadGameProgress();
}

void AEscapeMasterPlayerController::LevelCompleted()
{
    UGameSave* GameSaveInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
    if (!GameSaveInstance)
    {
        // Log an error if failed to load the saved game
        UE_LOG(LogTemp, Error, TEXT("Failed to load the saved game"));
        return;
    }

    // Increment the level upon completion
    CurrentLevel++;

    // Update the name of the last played level
    if (CurrentLevel == 2)
    {
        GameSaveInstance->LastPlayedLevelName = "Level2";
    }

    // Save game progress after completing a level
    SaveGameProgress(GameSaveInstance);

    AEscapeMasterGameMode *MyGameMode = GetWorld()->GetAuthGameMode<AEscapeMasterGameMode>();
    if (MyGameMode)
    {
        // Show completed widget if game mode is valid
        MyGameMode->ShowCompletedWidget();
    }
}

void AEscapeMasterPlayerController::SaveGameProgress(UGameSave* GameSaveInstance)
{
    if (GameSaveInstance)
    {
        // Save player location if exists
        if (GetPawn())
        {
            GameSaveInstance->PlayerLocation = GetPawn()->GetActorLocation();
        }

        // Save grabbed object state if exists
        if (PrisonerCharacter && PrisonerCharacter->GrabberComponent && PrisonerCharacter->GrabberComponent->GrabbedObject)
        {
            GameSaveInstance->GrabbedObjectType = PrisonerCharacter->GrabberComponent->GrabbedObject->GetClass();
            GameSaveInstance->GrabbedObjectLocation = PrisonerCharacter->GrabberComponent->GrabbedObject->GetActorLocation();
            GameSaveInstance->GrabbedObjectRotation = PrisonerCharacter->GrabberComponent->GrabbedObject->GetActorRotation();
        }

        // Save Game
        UGameplayStatics::SaveGameToSlot(GameSaveInstance, TEXT("SaveSlotName"), 0);
    }
}

void AEscapeMasterPlayerController::LoadGameProgress()
{
    // Load the saved game from the slot
    UGameSave* GameSaveInstance = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlotName"), 0));

    if (GameSaveInstance)
    {
        // Retrieve game progress variables and apply them
        CurrentLevel = GameSaveInstance->CurrentLevel;
        FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);

        // Load the last played level
        if (GameSaveInstance->LastPlayedLevelName.IsEmpty())
        {
            // Log a warning if no last played level is found
            UE_LOG(LogTemp, Warning, TEXT("Last played level name is empty"));
        }
        else
        {
            UGameplayStatics::OpenLevel(GetWorld(), *GameSaveInstance->LastPlayedLevelName, true); // Change the true/false parameter as needed for seamless travel
        }

        // Move the existing grabbed object if exists
        if (PrisonerCharacter && PrisonerCharacter->GrabberComponent && GameSaveInstance->GrabbedObjectType)
        {
            // Get the existing object that the player is grabbing
            AActor* GrabbedObject = PrisonerCharacter->GrabberComponent->GrabbedObject;

            // If there is an existing grabbed object, move it to the saved location
            if (GrabbedObject)
            {
                GrabbedObject->SetActorLocation(GameSaveInstance->GrabbedObjectLocation);
                GrabbedObject->SetActorRotation(GameSaveInstance->GrabbedObjectRotation);
            }
        }
        else
             UE_LOG(LogTemp, Warning, TEXT("No grabbed object to restore"));
    }
}

void AEscapeMasterPlayerController::PlayerCompletedObjective()
{
    AEscapeMasterGameMode *MyGameMode = GetWorld()->GetAuthGameMode<AEscapeMasterGameMode>();
    if (MyGameMode)
    {
        // Show completed widget if game mode is valid
        MyGameMode->ShowCompletedWidget();
    }
}
