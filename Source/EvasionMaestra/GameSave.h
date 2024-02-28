// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSave.generated.h"

/**
 * 
 */
UCLASS()
class EVASIONMAESTRA_API UGameSave : public USaveGame
{
	GENERATED_BODY()
	
public:
    UPROPERTY(VisibleAnywhere, Category = "Level")
    int32 CurrentLevel;
    
    UPROPERTY(VisibleAnywhere, Category = "Level")
    FString LastPlayedLevelName;

    UPROPERTY(VisibleAnywhere)
    FVector PlayerLocation;

     UPROPERTY(VisibleAnywhere, Category = "Grabber")
    TSubclassOf<AActor> GrabbedObjectType;

    UPROPERTY(VisibleAnywhere, Category = "Grabber")
    FVector GrabbedObjectLocation;

    UPROPERTY(VisibleAnywhere, Category = "Grabber")
    FRotator GrabbedObjectRotation;
};
