// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeMasterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EscapeMasterGameMode.h"
#include "GameSave.h"


void AEscapeMasterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    // Cargar el juego al inicio
    LoadGameOnStart();
}

void AEscapeMasterPlayerController::SaveGameOnEvent()
{
    // Lógica para determinar cuándo guardar el juego
    UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
    if (SaveGameInstance)
    {
        SaveGameInstance->PlayerLocation = GetPawn()->GetActorLocation(); // Ejemplo: obtén la ubicación del jugador
        // Guarda otros datos necesarios

        UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SaveSlot"), 0); // Guarda en un archivo llamado "SaveSlot"
    }
}

void AEscapeMasterPlayerController::LoadGameOnStart()
{
    // Lógica para cargar el juego al inicio
    UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot"), 0));
    if (SaveGameInstance)
    {
        // Restaurar la ubicación del jugador
        if (GetPawn())
        {
            GetPawn()->SetActorLocation(SaveGameInstance->PlayerLocation);
        }
        // Restaurar otros datos necesarios
    }
}

void AEscapeMasterPlayerController::PlayerCompletedObjective()
{
    AEscapeMasterGameMode *MyGameMode = GetWorld()->GetAuthGameMode<AEscapeMasterGameMode>();
    if (MyGameMode)
    {
        MyGameMode->ShowCompletedWidget();
    }
}


