/*	Copyright 2023 Silver Standard Studios. All rights reserved. 
	Derek Fallows											
   
	Base prototype character										*/

/*	Changelog
	2023-18-09 - Created
	*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PrototypeCharacter.generated.h"

UCLASS()
class WHIMSICALWIZARDRY_API APrototypeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APrototypeCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Pooling")
		class UActorPool* MagicMissilePool;
	UPROPERTY(EditAnywhere, Category = "MagicMissileFiring")
		class UMagicMissileFiring* MagicMissileFiring;


	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* FireAction;
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	void Fire();
	void Jump(); 

	UFUNCTION(Server, Reliable)
		void Server_Fire();
	UFUNCTION(Server, Reliable)
		void Server_Jump();
		/*
	UFUNCTION(Server, Reliable)
		void Server_Move(const FInputActionValue& value);*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UPlayerKnockedOffComponent* PlayerKnockedOff; 

};
