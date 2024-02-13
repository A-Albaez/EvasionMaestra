// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "EscapeMasterController.generated.h"

/**
 * 
 */
UCLASS()
class EVASIONMAESTRA_API AEscapeMasterController : public AController
{
	GENERATED_BODY()
	
public:
	// Variables de progreso del juego (ajusta según tus necesidades)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progreso del Juego")
    int32 NivelActual;

    void BeginPlay();

    void NivelCompletado();

    // Funciones para guardar y cargar el progreso del juego
    UFUNCTION(BlueprintCallable, Category = "Progreso del Juego")
    void GuardarProgresoJuego();

    UFUNCTION(BlueprintCallable, Category = "Progreso del Juego")
    void CargarProgresoJuego();
};
