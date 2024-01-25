// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeMasterGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


void AEscapeMasterGameMode::PlayerDetected()
{
    ShowDetectedWidget();

    FTimerHandle UnusedHandle;
    GetWorldTimerManager().SetTimer(UnusedHandle, this, &AEscapeMasterGameMode::HandleDetectionOutcome, 2.0f, false);

}

void AEscapeMasterGameMode::ShowDetectedWidget()
{
    UWorld *World = GetWorld();

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