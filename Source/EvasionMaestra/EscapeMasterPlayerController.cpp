// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeMasterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PrisonerCharacter.h"
#include "Grabber.h"
#include "EscapeMasterGameMode.h"
#include "GameSave.h"

void AEscapeMasterPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AEscapeMasterPlayerController::LevelCompleted()
{
    UGameSave *GameSaveInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
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

void AEscapeMasterPlayerController::SaveGameProgress(UGameSave *GameSaveInstance)
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
        UE_LOG(LogTemp, Warning, TEXT("saved game"));

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("saved game failed in SaveGameProgress"));
    }
}

void AEscapeMasterPlayerController::LoadGameProgress(TFunction<void(bool)> OnLoadCompleted)
{
    if (UGameplayStatics::DoesSaveGameExist("SaveSlotName",0))
    {
        // Intenta cargar el archivo de guardado existente
        if (UGameSave *GameSaveInstance = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlotName"), 0)))
        {
            UE_LOG(LogTemp, Warning, TEXT("Success to load the saved game"));

            // Game save loaded successfully
            bool bSuccess = true;
            UE_LOG(LogTemp, Warning, TEXT("bSuccess Value: %d"), bSuccess);

            // Retrieve game progress variables and apply them
            CurrentLevel = GameSaveInstance->CurrentLevel;
            FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);

            // Load the last played level
            if (!GameSaveInstance->LastPlayedLevelName.IsEmpty() && CurrentLevelName != *GameSaveInstance->LastPlayedLevelName)
            {
                UGameplayStatics::OpenLevel(GetWorld(), *GameSaveInstance->LastPlayedLevelName, true);
                // Reset bLevelRestarted
                GameSaveInstance->bLevelRestarted = true;
                UE_LOG(LogTemp, Error, TEXT("bLevelRestarted Value: %d"), GameSaveInstance->bLevelRestarted);
            }

            // Move the existing grabbed object if exists
            if (PrisonerCharacter && PrisonerCharacter->GrabberComponent && GameSaveInstance->GrabbedObjectType)
            {
                // Get the existing object that the player is grabbing
                auto GrabbedObject = PrisonerCharacter->GrabberComponent->GrabbedObject;

                // If there is an exist grabbed object, move it to the saved location
                if (GrabbedObject)
                {
                    GrabbedObject->SetActorLocation(GameSaveInstance->GrabbedObjectLocation);
                    GrabbedObject->SetActorRotation(GameSaveInstance->GrabbedObjectRotation);
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("No grabbed object to restore"));
            }

            // Call the callback function with success status
            OnLoadCompleted(true);
        }
        else
        {
            // Si el archivo de guardado no existe, informa del error
            UE_LOG(LogTemp, Error, TEXT("Failed to load the saved game"));

            // Call the callback function with failure status
            OnLoadCompleted(false);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No existe un archivo de guardado en el slot "));
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