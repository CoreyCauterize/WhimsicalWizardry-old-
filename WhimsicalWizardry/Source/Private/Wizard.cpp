// Copyright Epic Games, Inc. All Rights Reserved.

#include "Wizard.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerKnockedOffComponent.h"
#include "SpellInventoryComponent.h"
#include "ItemSpell.h"
#include "WhimsicalWizardryGameModeBase.h"
#include "Public/WimsicalWizardryGameStateBase.h"
#include "DynamicCamera.h"
#include "Net/UnrealNetwork.h"

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
	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Creating the component for killplane logic
	PlayerKnockedOffComponent = CreateDefaultSubobject<UPlayerKnockedOffComponent>("Player Knocked Off Component");

	//Create the inventory
	SpellInventoryComponent = CreateDefaultSubobject<USpellInventoryComponent>("Spell Inventory Component");

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	SetReplicates(true);
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

		if (GetLocalRole() == ROLE_Authority)
		{
			SpawnCamera();
			PlayerController->SetViewTarget(CameraActor);
		}
		else
		{
			Server_SetViewTarget();

		}
	}


	

	//Client_SpawnCamera();
	
}

void AWizard::Server_SetViewTarget_Implementation()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		SpawnCamera();
		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, this, &AWizard::SetViewTarget, 0.5f, false);
        //PlayerController->SetViewTarget(CameraActor);
    }
}

void AWizard::SetViewTarget()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
        PlayerController->SetViewTarget(CameraActor);
    }
}

void AWizard::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APlayerController* PlayerController = Cast<APlayerController>(NewController);
	if (PlayerController)
	{



	}

}

void AWizard::SpawnCamera()
{
	FVector SpawnLocation = GetActorLocation() + (FVector(0, 0, 300) - (350 * GetActorForwardVector()));
	FRotator SpawnRotation = GetActorForwardVector().Rotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Name = FName("DynamicCamera_" + GetName());

	ADynamicCamera* cam = GetController()->GetWorld()->SpawnActor<ADynamicCamera>(ADynamicCamera::StaticClass(), FVector(-940.0, 0, 810), FRotator(-20, 0, 0), SpawnParams);

	CameraActor = cam;
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
		EnhancedInputComponent->BindAction(FireItemSpellAction, ETriggerEvent::Triggered, this, &AWizard::FireItemSpell);

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
	if (SpellInventoryComponent)
	{
		AItemSpell* firstSpell = SpellInventoryComponent->GetFirstHeldSpell();

		if (firstSpell)
		{
			firstSpell->OnFire(SpellInventoryComponent);
		}
	}
}

void AWizard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWizard, CameraActor);
}