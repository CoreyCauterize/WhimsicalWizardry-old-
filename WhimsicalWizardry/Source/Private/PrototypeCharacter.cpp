// Copyright 2023 Silver Standard Studios. All rights reserved. 
// Derek Fallows

#include "PrototypeCharacter.h"				// internal inclusions
#include "PlayerKnockedOffComponent.h" 
#include "Camera/CameraComponent.h"			// unreal inclusions
#include "EnhancedInputComponent.h"
#include "pooling/ActorPool.h"	
#include "Spells/MagicMissileFiring.h"	

// Sets default values
APrototypeCharacter::APrototypeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera", false);

	MagicMissileFiring = CreateDefaultSubobject<UMagicMissileFiring>("Basic Fire", false); 
	PlayerKnockedOff = CreateDefaultSubobject<UPlayerKnockedOffComponent>("Projectile Pool", false);

	SetReplicates(true); 
	SetReplicateMovement(true); 
}

// Called when the game starts or when spawned
void APrototypeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APrototypeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APrototypeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &APrototypeCharacter::Fire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &APrototypeCharacter::Fire);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APrototypeCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APrototypeCharacter::StopJumping);

		//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APrototypeCharacter::Server_Move); 
	}
}

void APrototypeCharacter::Fire()
{
	Server_Fire(); 
}
void APrototypeCharacter::Jump()
{
	Server_Jump(); 
}

void APrototypeCharacter::Server_Fire_Implementation()
{
	check (1 == 2)
	MagicMissileFiring->StartFire(); 
}
void APrototypeCharacter::Server_Jump_Implementation()
{
	
}

void APrototypeCharacter::Server_Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>(); 

	MovementVector.x

	if (GetController() != nullptr)
	{

	}

}
//void APrototypeCharacter::Server_Move_Implementation(const FInputActionValue& value)
//{
//	
//}