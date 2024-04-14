// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeMasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameSave.h"
#include "EscapeMasterPlayerController.h"

void AEscapeMasterGameMode::BeginPlay()
{
    Super::BeginPlay();
    World = GetWorld();

    if (bGameProgressLoaded || bLoadingInProgress)
    {
        return;
    }

    bLoadingInProgress = true;

    ShowLoadingScreen();

    UGameSave *GameSaveInstance = NewObject<UGameSave>();
    if (GameSaveInstance)
    {
        AEscapeMasterPlayerController *PlayerController = Cast<AEscapeMasterPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
        if (PlayerController && !GameSaveInstance->bLevelRestarted)
        {
            PlayerController->LoadGameProgress([this](bool bSuccess)
            {
                bLoadingInProgress = false;

                if (bSuccess)
                {
                    bGameProgressLoaded = true;
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Loading game failed"));
                    bLoadingInProgress = false; // Reset the flag in case of error
                }

                HideLoadingScreen();
            });
        }
        else
        {
            bLoadingInProgress = false;
            UE_LOG(LogTemp, Error, TEXT("Failed to load game progress"));
            HideLoadingScreen();
        }
    }
    else
    {
        bLoadingInProgress = false;
        UE_LOG(LogTemp, Error, TEXT("Error creating game save object"));
        HideLoadingScreen();
    }
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
        FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
        FString NextLevelName = "Level2";
        if (CurrentLevelName != NextLevelName)
        {
            UGameplayStatics::OpenLevel(World, *NextLevelName, false);
        }
        
    }
}

void AEscapeMasterGameMode::ShowLoadingScreen()
{
    if (World)
    {
        UE_LOG(LogTemp, Error, TEXT("Valid World"));

        LoadingScreen = CreateWidget<UUserWidget>(World, LoadingScreenClass);
        if (LoadingScreen)
        {
            UE_LOG(LogTemp, Error, TEXT("Loading screen created"));

            LoadingScreen->AddToViewport();
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Loading screen not created"));
        }
    }
    else
        UE_LOG(LogTemp, Error, TEXT("Invalid World"));
}

void AEscapeMasterGameMode::HideLoadingScreen()
{
    if (bGameProgressLoaded && LoadingScreen && LoadingScreen->IsVisible())
    {
        UE_LOG(LogTemp, Error, TEXT("Loading screen removed"));

        LoadingScreen->RemoveFromParent();
    }
    else
        UE_LOG(LogTemp, Error, TEXT("Loading screen did not exist"));
}

void AEscapeMasterGameMode::HideWidgets()
{
    // Hide level widget if it's visible
    if (Completed && Completed->IsVisible())
    {
        Completed->RemoveFromParent();
    }

    // Hide detection widget if it's visible
    if (Detected && Detected->IsVisible())
    {
        Detected->RemoveFromParent();
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
    // Show loading screen
    ShowLoadingScreen();

    // Define la duración del retraso en segundos
    constexpr auto DelayInSeconds = 3.0f;

    // Configura un temporizador para abrir el nivel después del retraso
    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AEscapeMasterGameMode::OpenLevelAndHideLoadingScreen, DelayInSeconds, false);  
}

void AEscapeMasterGameMode::OpenLevelAndHideLoadingScreen()
{
    UGameplayStatics::OpenLevel(GetWorld(), *GetWorld()->GetName(), false);
    HideLoadingScreen();
}
