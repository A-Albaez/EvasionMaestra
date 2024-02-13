// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SecurityDroneAIController.generated.h"

/**
 * 
 */
UCLASS()
class EVASIONMAESTRA_API ASecurityDroneAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnyWhere)
	class UBehaviorTree* AIBehavior;
};
