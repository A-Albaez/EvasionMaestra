
#include "EscapeMasterController.h"
#include "Kismet/GameplayStatics.h"
#include "GameSave.h"

void AEscapeMasterController::BeginPlay()
{
    Super::BeginPlay();
    
    // Inicializar el nivel al comienzo del juego
    NivelActual = 1; // O cualquier valor predeterminado que desees
}

void AEscapeMasterController::NivelCompletado()
{
    // Incrementar el nivel al completar uno
    NivelActual++;
    
    // Guardar el progreso del juego después de completar un nivel
    GuardarProgresoJuego();
}

void AEscapeMasterController::GuardarProgresoJuego()
{
    // Crear una instancia de la clase UGameSave
    UGameSave* GameSaveInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));

    if (GameSaveInstance)
    {
        // Establecer las variables de progreso del juego (aquí podrías obtener la información del juego)
        GameSaveInstance->CurrentLevel = NivelActual;

        // Guardar el juego
        UGameplayStatics::SaveGameToSlot(GameSaveInstance, TEXT("NombreDelSlot"), 0);
    }
}

void AEscapeMasterController::CargarProgresoJuego()
{
    // Cargar el juego guardado desde el slot
    UGameSave* GameSaveInstance = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("NombreDelSlot"), 0));

    if (GameSaveInstance)
    {
        // Recuperar las variables de progreso del juego y aplicarlas (aquí podrías establecer el estado del juego)
        NivelActual = GameSaveInstance->CurrentLevel;

        // Puedes hacer más cosas con la información cargada si es necesario
    }
}
