#include "SecurityCameraActor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "PrisonerCharacter.h"
#include "EscapeMasterGameMode.h"

ASecurityCameraActor::ASecurityCameraActor()
{
    SetActorTickEnabled(true);
    PrimaryActorTick.bCanEverTick = true;

    CameraComponent = FindComponentByClass<UCameraComponent>();

    RotationSpeed = 15.0f;
    DeltaRotation = FRotator(0.0f, -140.0f, 0.0f);
}

void ASecurityCameraActor::BeginPlay()
{
    Super::BeginPlay();

    StartRotation = GetActorRotation();
    TargetRotation = StartRotation + DeltaRotation;

    if ((CapsuleComp = FindComponentByClass<UCapsuleComponent>()) != nullptr)
    {
        CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ASecurityCameraActor::OnBeginOverlap);
    }

    if (CurveFloat)
    {
        FOnTimelineFloat TimelineProgress;
        TimelineProgress.BindUFunction(this, FName("TimelineProgress"));

        CurveFTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
        CurveFTimeline.SetLooping(true);

        CurveFTimeline.PlayFromStart();
    }
}

void ASecurityCameraActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CurveFTimeline.TickTimeline(DeltaTime);
}

void ASecurityCameraActor::OnBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    APrisonerCharacter* PrisonerCharacter = Cast<APrisonerCharacter>(OtherActor);
    if (PrisonerCharacter)
    {
        AEscapeMasterGameMode* GameMode = Cast<AEscapeMasterGameMode>(GetWorld()->GetAuthGameMode());

        if (GameMode)
        {
            GameMode->PlayerDetected();
        }
    }
}


void ASecurityCameraActor::TimelineProgress(float value)
{
    FRotator NewRotator = FMath::Lerp(StartRotation, TargetRotation, value);
    SetActorRotation(NewRotator);
}
