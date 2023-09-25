/*	Copyright 2023 Silver Standard Studios (based on base ACharacter by Epic Games, Inc. All rights reserved.

	Component allowing a controlled character to fire basic magic
	projectiles that don't require getting a pickup.			*/

	/*	Changelog
		2023-09-18 - Created (DF)
		2023-09-22 - Added magic missile firing (DF)
		2023-09-24 - Cleaned up and networked magic missile firing (DF)
		*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "Wizard.generated.h"

UCLASS(config = Game)
class AWizard : public ACharacter
{
	GENERATED_BODY()

public: 
	AWizard();

	/* -- Base Camera ----------------------------------------------------------------- */

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/* -- Basic Magic Missile Projectile Firing	---------------------------------------- */

	// Returns magic missile firing arrow
	UArrowComponent* GetMagicMissileFiringArrow() const { return MagicMissileFiringArrow; }

	// Basic magic missile firing
	UPROPERTY(EditAnywhere, Category = "Magic Missile")
		class UMagicMissileFiring* MagicMissileFiring = nullptr;

private:
	// To add mapping context
	virtual void BeginPlay();

	/* -- Basic Movement and Input ------------------------------------------------------ */

	// Called for looking input
	void Look(const FInputActionValue& Value);

	// Called for movement input 
	void Move(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* -- Basic Magic Missile Projectile Firing	------------------------------------------ */

	// Called for firing basic magic missile
	UFUNCTION(Server, Reliable)
		void FireMagicMissile();

	/* -- Spell Pickup Management	------------------------------------------------------- */

	// Called for firing item spell input
	void FireItemSpell();

private:

	/* -- Base Follow Camera --------------------------------------------------------------- */

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/* -- Basic Movement and Input ---------------------------------------------------------- */

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	/* -- Basic Projectile Firing	---------------------------------------------------------- */

	// Fire basic magic missile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* FireMagicMissileAction;

	// FiringArrow
	UPROPERTY(EditAnywhere, Category = "FiringArrow")
		class UArrowComponent* MagicMissileFiringArrow = nullptr;

	/* -- Defeat ----------------------------------------------------------------------------- */

	/** Component for logic on hitting a kill plane*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Custom, meta = (AllowPrivateAccess = "true"))
		class UPlayerKnockedOffComponent* PlayerKnockedOffComponent;

	/* -- Spell Pickup Management	----------------------------------------------------------- */

	/* Fire Item Spell Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* FireItemSpellAction;

	/* Spell Inventory Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Custom, meta = (AllowPrivateAccess = "true"))
		class USpellInventoryComponent* SpellInventoryComponent;

	UFUNCTION(Server,Reliable)
		void Server_SetViewTarget();

	void SetViewTarget();

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(Replicated)
		AActor* CameraActor;

	void SpawnCamera();
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

