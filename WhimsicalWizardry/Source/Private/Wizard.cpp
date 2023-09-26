//	Copyright 2023 Silver Standard Studios (based on base class by Epic Games, Inc.) All rights reserved.

#include "Wizard.h"						// internal inclusions
#include "ItemSpell.h"
#include "PlayerKnockedOffComponent.h"
#include "Pooling/ActorPool.h"
#include "Pooling/PoolableActor.h"
#include "MagicProjectile/MagicMissileFiring.h"
#include "SpellInventoryComponent.h"
#include "Camera/CameraComponent.h"		// unreal inclusions
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AWizard

AWizard::AWizard()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Creating the component for killplane logic
	PlayerKnockedOffComponent = CreateDefaultSubobject<UPlayerKnockedOffComponent>("Player Knocked Off Component");

	//Create the inventory
	SpellInventoryComponent = CreateDefaultSubobject<USpellInventoryComponent>("Spell Inventory Component");

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	
	// Create firing arrow for projectiles
	MagicMissileFiringArrow = CreateDefaultSubobject<UArrowComponent>("Firing Arrow"); 
	MagicMissileFiringArrow->SetupAttachment(RootComponent);

	// Create magic missile firing 
	MagicMissileFiring = CreateDefaultSubobject<UMagicMissileFiring>("Magic Missile Firing Component");
	MagicMissileFiring->SetFiringArrow(MagicMissileFiringArrow);

}

void AWizard::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//Cast<APlayerController>(GetController())->ConsoleCommand("show collision", false);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWizard::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWizard::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWizard::Look);

		//Firing item spells
		EnhancedInputComponent->BindAction(FireItemSpellAction, ETriggerEvent::Started, this, &AWizard::FireItemSpell);

		//Firing magic missile
		EnhancedInputComponent->BindAction(FireMagicMissileAction, ETriggerEvent::Triggered, this, &AWizard::FireMagicMissile);
	}
}

void AWizard::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWizard::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWizard::FireItemSpell()
{
	Server_FireItemSpell();

}


void AWizard::Server_FireItemSpell_Implementation()
{
	if (SpellInventoryComponent)
	{
		AItemSpell* firstSpell = SpellInventoryComponent->GetFirstHeldSpell();

		if (firstSpell)
		{
			firstSpell->OnFire(SpellInventoryComponent);
		}
	}


}

void AWizard::FireMagicMissile_Implementation()
{
	MagicMissileFiring->StartFire();
}

void  AWizard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
