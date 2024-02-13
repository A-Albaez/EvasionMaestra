// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EscapeMasterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EVASIONMAESTRA_API AEscapeMasterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void PlayerCompletedObjective();

    void SaveGameOnEvent();
    void LoadGameOnStart();
    
};
