// Fill out your copyright notice in the Description page of Project Settings.

#include "SecurityDroneAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <string>

void ASecurityDroneAIController::BeginPlay()
{
    Super::BeginPlay();
    FVector Patrol(1160.000000, 1630.000000, 170.000000);

    if (AIBehavior != nullptr)
    {
        APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

        GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolRoute"), Patrol);
    }
}
