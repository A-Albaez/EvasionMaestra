#include "BTService_PlayerLocationIfSeen.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "Camera/CameraComponent.h"
#include "PrisonerCharacter.h"
#include "EscapeMasterGameMode.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = "Update Player Location If Seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr)
    {
        return;
    }

    AAIController *AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr)
    {
        return;
    }

    AActor *DronActor = AIController->GetPawn();
    if (DronActor == nullptr)
    {
        return;
    }

    // Get Drone camera
    UCameraComponent *DronCamera = DronActor->FindComponentByClass<UCameraComponent>();
    if (DronCamera == nullptr)
    {
        return;
    }

    FVector CameraForward = DronCamera->GetForwardVector();

    FVector PlayerLocation = PlayerPawn->GetActorLocation();

    // Verifica si el jugador está dentro del rango de visión del dron
    if (FVector::DotProduct(CameraForward, (PlayerLocation - DronActor->GetActorLocation()).GetSafeNormal()) > 0)
    {
        APrisonerCharacter *PrisonerCharacter = Cast<APrisonerCharacter>(PlayerPawn);
        if (PrisonerCharacter)
        {
            AEscapeMasterGameMode *GameMode = Cast<AEscapeMasterGameMode>(GetWorld()->GetAuthGameMode());

            if (GameMode)
            {
                GameMode->PlayerDetected();
            }
        }
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
        UE_LOG(LogTemp, Warning, TEXT("¡Dron ve al jugador!"));
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
