/* =============================================================================================================================
 * Copyright: Silver Standard Studios © 2023
 * Author: Sidney Allen
 * -----------------------------------------------------------------------------------------------------------------------------
 * CHANGELOG:
 * - Sep 21, 2023	Started WizardController.h class.
 * ============================================================================================================================= */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

#include "WizardController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class WHIMSICALWIZARDRY_API AWizardController : public APlayerController
{
	GENERATED_BODY()

public:
	// Controller's constructor.
	AWizardController();

	// Called on game startup/spawn.
	virtual void BeginPlay() override;

	// Used to access inputs from within the controller.
	virtual void SetupInputComponent() override;

protected:
	// UInput properties.
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
		UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
		UInputAction* CastBaseAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
		UInputAction* CastPickupAction;
		
	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
		UInputAction* MeleeAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
		UInputMappingContext* InputMapping;

	// UInput UFunctions.

	UFUNCTION(Category = "Enhanced Input")
		void Move(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable, Category = "Enhanced Input")
		void Server_Move(const FInputActionValue& Value);

	UFUNCTION(Category = "Enhanced Input")
		void BaseCast(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable, Category = "Enhanced Input")
		void Server_BaseCast(const FInputActionValue& Value);

	UFUNCTION(Category = "Enhanced Input")
		void PickupCast(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable, Category = "Enhanced Input")
		void Server_PickupCast(const FInputActionValue& Value);

	UFUNCTION(Category = "Enhanced Input")
		void Melee(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable, Category = "Enhanced Input")
		void Server_Melee(const FInputActionValue& Value);
};
