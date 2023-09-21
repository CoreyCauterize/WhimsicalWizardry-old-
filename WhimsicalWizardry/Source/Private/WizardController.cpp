/* =============================================================================================================================
 * Copyright: Silver Standard Studios © 2023
 * Author: Sidney Allen
 * -----------------------------------------------------------------------------------------------------------------------------
 * CHANGELOG:
 * - Sep 21, 2023	Started WizardController.cpp class.
 * ============================================================================================================================= */

#include "WizardController.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Pawn.h"

/// <summary> WizardController Constructor </summary>
/// <param> 0 params </param>
/// <returns> no return </returns>
// Sets default values
AWizardController::AWizardController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

/// <summary> Called on WizardController start </summary>
/// <param> 0 params </param>
/// <returns> no return </returns>
// Called on game startup/spawn.
void AWizardController::BeginPlay()
{
	Super::BeginPlay();
	
	// Checks if there's a preexisting UEhancedInputLocalPlayerSubsystem in place.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		// Wipes any preexisting mappings, then adds class specific context.
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMapping, 0);
	}
	//ENDIF
}
/// <summary> Sets inputs for this controller </summary>
/// <param> 0 params </param>
/// <returns> no return </returns>
// Accesses inputs from within the controller and binds them.
void AWizardController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Casts the InputComponent into an Enhanced component's pointer.
	UEnhancedInputComponent* EIComponent = Cast<UEnhancedInputComponent>(InputComponent);

	// For ease of access (to be removed later) :
	// WASD - Move
	// LMB - Base Attack
	// RMB - Pickup Attack
	// MMB - Melee

	// Would change MoveAction ETriggerEvent to Triggered, so it continues until it stops.
	// Binded actions for use during the game.
	EIComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AWizardController::Move);
	EIComponent->BindAction(CastBaseAction, ETriggerEvent::Started, this, &AWizardController::BaseCast);
	EIComponent->BindAction(CastPickupAction, ETriggerEvent::Started, this, &AWizardController::PickupCast);
	EIComponent->BindAction(MeleeAction, ETriggerEvent::Started, this, &AWizardController::Melee);
}

/// <summary> Movement input function </summary>
/// <param> name = Value: const FInputActionValue& </param>
/// <returns> no return </returns>
// Function used to move the player around.
void AWizardController::Move(const FInputActionValue& Value)
{
	// Call the networked server Move function.
	Server_Move(Value);
}

/// <summary> Server Movement input function </summary>
/// <param> name = Value: const FInputActionValue& </param>
/// <returns> no return </returns>
// Function used to move the player around.
void AWizardController::Server_Move_Implementation(const FInputActionValue& Value)
{
	// Temp debug message.
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString("Move Message"));

}

/// <summary> Base Casting input function </summary>
/// <param> name = Value: const FInputActionValue& </param>
/// <returns> no return </returns>
// Function used to shoot basic projectiles.
void AWizardController::BaseCast(const FInputActionValue& Value)
{
	// Call the networked server BaseCast function.
	Server_BaseCast(Value);
}

/// <summary> Server Base Casting input function </summary>
/// <param> name = Value: const FInputActionValue& </param>
/// <returns> no return </returns>
// Function used to shoot basic projectiles.
void AWizardController::Server_BaseCast_Implementation(const FInputActionValue& Value)
{
	// Temp debug message.
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString("BaseCast Fired"));

}

/// <summary> Pickup Casting input function </summary>
/// <param> name = Value: const FInputActionValue& </param>
/// <returns> no return </returns>
// Function used to cast picked up spells.
void AWizardController::PickupCast(const FInputActionValue& Value)
{
	// Call the networked server PickupCast function.
	Server_PickupCast(Value);
}

/// <summary> Server Pickup Casting input function </summary>
/// <param> name = Value: const FInputActionValue& </param>
/// <returns> no return </returns>
// Function used to cast picked up spells.
void AWizardController::Server_PickupCast_Implementation(const FInputActionValue& Value)
{
	// Temp debug message.
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("PickupCast Fired"));

}

/// <summary> Melee attack input function </summary>
/// <param> name = Value: const FInputActionValue& </param>
/// <returns> no return </returns>
// Function used to physically attack with the player.
void AWizardController::Melee(const FInputActionValue& Value)
{
	// Call the networked server Melee function.
	Server_Melee(Value);
}

/// <summary> Server Melee attack input function </summary>
/// <param> name = Value: const FInputActionValue& </param>
/// <returns> no return </returns>
// Function used to physically attack with the player.
void AWizardController::Server_Melee_Implementation(const FInputActionValue& Value)
{
	// Temp debug message.
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString("Melee Attack"));
	
}