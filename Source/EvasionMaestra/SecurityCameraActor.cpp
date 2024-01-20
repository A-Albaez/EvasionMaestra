#include "SecurityCameraActor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

ASecurityCameraActor::ASecurityCameraActor()
{
    SetActorTickEnabled(true);
    PrimaryActorTick.bCanEverTick = true;

    CameraComponent = FindComponentByClass<UCameraComponent>();

    RotationSpeed = 15.0f;
}

void ASecurityCameraActor::BeginPlay()
{
    Super::BeginPlay();

    if ((CapsuleComp = FindComponentByClass<UCapsuleComponent>()) != nullptr)
    {
        CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ASecurityCameraActor::OnBeginOverlap);
    }
}

void ASecurityCameraActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Rotar la cámara
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += RotationSpeed * DeltaTime;
    SetActorRotation(NewRotation);
}

void ASecurityCameraActor::OnBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
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

    UE_LOG(LogTemp, Warning, TEXT("Superposición detectada con la cápsula"));
}