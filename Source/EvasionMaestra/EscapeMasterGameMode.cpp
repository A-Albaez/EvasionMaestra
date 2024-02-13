// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeMasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EscapeMasterPlayerController.h"

void AEscapeMasterGameMode::BeginPlay()
{
    Super::BeginPlay();

    AEscapeMasterPlayerController *PlayerController = Cast<AEscapeMasterPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    if (PlayerController)
    {
        PlayerController->LoadGameOnStart();
    }
    World = GetWorld();
}

void AEscapeMasterGameMode::PlayerDetected()
{
    ShowDetectedWidget();

    FTimerHandle UnusedHandle;
    GetWorldTimerManager().SetTimer(UnusedHandle, this, &AEscapeMasterGameMode::HandleDetectionOutcome, 2.0f, false);
}

void AEscapeMasterGameMode::ShowCompletedWidget()
{
    if (World)
    {
        Completed = CreateWidget<UUserWidget>(World, CompletedScreenClass);

        if (Completed)
        {
            Completed->AddToViewport();

            FTimerHandle UnusedHandle;
            GetWorldTimerManager().SetTimer(UnusedHandle, this, &AEscapeMasterGameMode::HandleLevelCompletion, 2.0f, false);
        }
    }
}

void AEscapeMasterGameMode::HandleLevelCompletion()
{
    if (World)
    {
        // Nombre del siguiente nivel
        FString NextLevelName = "Level2";

        UGameplayStatics::OpenLevel(World, *NextLevelName, false);
    }
}

void AEscapeMasterGameMode::ShowDetectedWidget()
{
    if (World)
    {
        Detected = CreateWidget<UUserWidget>(World, DetectedScreenClass);

        if (Detected)
        {
            Detected->AddToViewport();
        }
    }
}

void AEscapeMasterGameMode::HandleDetectionOutcome()
{
    UGameplayStatics::OpenLevel(GetWorld(), *GetWorld()->GetName(), false);
}