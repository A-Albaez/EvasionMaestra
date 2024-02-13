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
    UPROPERTY(VisibleAnywhere, Category = Basic)
    int32 CurrentLevel;

    UPROPERTY(VisibleAnywhere)
    FVector PlayerLocation;
};
