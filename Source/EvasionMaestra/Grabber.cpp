// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameSave.h"
#include "Kismet/GameplayStatics.h"
#include "PrisonerCharacter.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
	: RightHandSocketName(TEXT("RightHandMiddle1"))
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize the grabbed object
	GrabbedObject = nullptr;

	// Initialize the grab distance
	GrabDistance = 150.0f;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateGrabbedObject();

	UpdateHandReference();
}

void UGrabber::GrabObject()
{
	// Check if the hand component is valid
	if (Hand)
	{
		// Get the start location of the sphere trace from the socket
		FVector Start = Hand->GetSocketLocation(RightHandSocketName);

		// Perform a sphere trace and get the hit result
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetOwner());

		// Use SphereTraceSingle to check for objects within the specified radius
		float SphereRadius = 150.0f;
		if (GetWorld()->SweepSingleByChannel(Hit, Start, Start, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(SphereRadius), Params))
		{
			// Check if the hit result has the Grabbable component
			if (Hit.GetActor()->ActorHasTag("grabbable"))
			{
				GrabbedObject = Hit.GetActor();

				// Desactivar la simulación física del objeto
				GrabbedObject->SetActorEnableCollision(false);
				GrabbedObject->SetActorTickEnabled(false);

				// Adjuntar el objeto al componente de la mano
				FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
				GrabbedObject->AttachToComponent(Hand, AttachmentRules, RightHandSocketName);

				if (GrabbedObject)
				{
					if (Hit.GetActor()->ActorHasTag("tablet1"))
					{
						bIsGrabbing = true;
						CanHackDoor = true;
					}
					UE_LOG(LogTemp, Warning, TEXT("Objeto agarrado: %s"), *GrabbedObject->GetName());
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("GrabbedObject es nulo"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Objeto no tiene el tag grabbable: %s"), *Hit.GetActor()->GetName());
			}
		}

		UGameSave *GameSave = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
		if (GameSave)
		{
			if (GrabbedObject)
			{
				GameSave->GrabbedObjectType = GrabbedObject->GetClass();
				GameSave->GrabbedObjectLocation = GrabbedObject->GetActorLocation();
				GameSave->GrabbedObjectRotation = GrabbedObject->GetActorRotation();
				// Guardar el juego
				UGameplayStatics::SaveGameToSlot(GameSave, TEXT("NombreDelSlot"), 0);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("GrabbedObject es nulo"));
			}
		}
	}
}

void UGrabber::ReleaseObject()
{
	if (GrabbedObject)
	{
		// Habilita la simulación física del objeto
		GrabbedObject->SetActorEnableCollision(true);
		GrabbedObject->SetActorTickEnabled(true);

		// Desvincula el objeto del componente de la mano
		GrabbedObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		// Reinicia la referencia al objeto agarrado
		GrabbedObject = nullptr;

		CanHackDoor = false;
		bIsGrabbing = false;

		UE_LOG(LogTemp, Warning, TEXT("Objeto liberado"));

		if (UGameSave *GameSave = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("NombreDelSlot"), 0)))
		{
			GameSave->GrabbedObjectType = nullptr;
			// Guardar el juego
			UGameplayStatics::SaveGameToSlot(GameSave, TEXT("NombreDelSlot"), 0);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No hay objeto agarrado para soltar"));
	}
}

void UGrabber::UpdateGrabbedObject()
{
	// Check if the hand component and the grabbed object are valid
	if (Hand && GrabbedObject && GrabbedObject->IsValidLowLevel())

	{
		// Get the target location and rotation of the grabbed object from the socket
		FVector Location = Hand->GetSocketLocation(RightHandSocketName);
		FRotator Rotation = Hand->GetSocketRotation(RightHandSocketName);

		// Set the location and rotation of the grabbed object
		GrabbedObject->SetActorLocationAndRotation(Location, Rotation);
	}
}

void UGrabber::UpdateHandReference()
{
	// Obtén la referencia al componente de mano en PrisonerCharacter
	APrisonerCharacter *OwnerCharacter = dynamic_cast<APrisonerCharacter *>(GetOwner());
	if (OwnerCharacter)
	{
		Hand = OwnerCharacter->GetMesh();

		if (!Hand)
		{
			UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent not found on %s"), *OwnerCharacter->GetName());
		}
	}
}
