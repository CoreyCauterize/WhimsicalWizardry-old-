/*	Copyright 2023 Silver Standard Studios (based on base ACharacter by Epic Games, Inc. All rights reserved.
 
	Component allowing a controlled character to fire basic magical
	projectiles that don't require getting a pickup.			*/

	/*	Changelog
		2023-15-08 - Created
		2023-15-09 - Added magic missile firing
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

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** Component for logic on hitting a kill plane*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Custom, meta = (AllowPrivateAccess = "true"))
		class UPlayerKnockedOffComponent* PlayerKnockedOffComponent;

	/**Spell Inventory Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Custom, meta = (AllowPrivateAccess = "true"))
		class USpellInventoryComponent* SpellInventoryComponent;

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

	/**Fire Item Spell Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* FireItemSpellAction;

	// Fire basic magic missile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* FireMagicMissileAction;

	// Basic magic missile firing
	UPROPERTY(EditAnywhere, Category = "Magic Missile")
		class UMagicMissileFiring* MagicMissileFiring = nullptr; 
	// Magic missile pool
	UPROPERTY(EditAnywhere, Category = "Magic Missile")
		class UActorPool* MagicMissilePool = nullptr; 
	UPROPERTY(EditAnywhere, Category = "Magic Missile")
		int MagicMissilePoolAmount = 15; 
	// Magic missile class (must be a poolable actor)
	UPROPERTY(Replicated, EditAnywhere)
		TSubclassOf<class APoolableActor> MagicMissileClass = nullptr; 
	// FiringArrow
	UPROPERTY(EditAnywhere, Category = "FiringArrow")
		class UArrowComponent* FiringArrow = nullptr; 


public:
	AWizard();


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for firing item spell input */
	void FireItemSpell();

	// Called for firing basic magic missile
	void FireMagicMissile();


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

