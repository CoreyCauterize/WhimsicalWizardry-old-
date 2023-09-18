// Copyright 2023 Silver Standard Studios. All rights reserved. 
// Derek Fallows

#include "Spells/MagicMissileFiring.h"	// internal inclusions
#include "Pooling/ActorPool.h"
#include "Spells/Projectile.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Components/ArrowComponent.h"	// unreal inclusions
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Weapon constants
const float UMagicMissileFiring::BASE_FIRE_RATE = 0.25f; 
const float UMagicMissileFiring::PROJECTILE_LIFESPAN = 10.0f; 
const FString UMagicMissileFiring::EMPTY_STRING = "";

UMagicMissileFiring::UMagicMissileFiring() : FireRate(BASE_FIRE_RATE)
{
	// This component doesn't need to tick. If this changes, remove this
	PrimaryComponentTick.bCanEverTick = false; 

	ProjectilePool = CreateDefaultSubobject<UActorPool>("Projectile Pool", false); 
	ProjectilePool->SetActorsHaveLifespan(true);
	ProjectilePool->SetActorLifespan(PROJECTILE_LIFESPAN); 

	SetIsReplicatedByDefault(true); 
}

// Called when game starts or when spawned
void UMagicMissileFiring::BeginPlay()
{
	Super::BeginPlay();

	// Allows the pool of projectiles to have access to the fire arrow
	ProjectilePool->SetFireComponent(FireArrow); 

	//InputComponent->BindAction()
}

/* Called every frame. 
   DeltaTime        - Time since last update
   ELevelTick       - The type of tick
   ThisTickFunction - Pointer to this tick function	*/
void UMagicMissileFiring::TickComponent(float DeltaTime, ELevelTick TickType,
							FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); 

	if (bWaitingForProjectileFromPool == true && ProjectilePool->HasActorWaiting == true)
	{
		LateFireProjectile(ProjectilePool->WaitingActor); 
		bWaitingForProjectileFromPool = false; 
		ProjectilePool->HasActorWaiting = false; 
		ProjectilePool->WaitingActor = nullptr; 
	}
}

// Sets up the FireArrow the component fires from
void UMagicMissileFiring::SetFireArrow(UArrowComponent* fireArrow)
{
	check(fireArrow != nullptr); 
	FireArrow = fireArrow; 
}

// Begins projectile fire sequence. 
void UMagicMissileFiring::StartFire_Implementation()
{
	if (bIsBeingFired == false)
	{
		bIsBeingFired = true; 

		// Set timer for fire delay
		UWorld* world = GetWorld();
		FTimerHandle& timerHandle = FiringTimer; 
		world->GetTimerManager().SetTimer(timerHandle, this, 
			&UMagicMissileFiring::StopFire, FireRate, false); 

		// Fire the projectile
		FireProjectile();

		// Play firing sound effect
		UGameplayStatics::PlaySoundAtLocation(nullptr, 
				FireSound, GetOwner()->GetActorLocation(), 
				1.0f, 1.0f, 0.0f, nullptr, nullptr, nullptr); 

		// This is where an animation can be called to play when we have one
	}
}

// Ends the fire sequence and allows a new fire sequence to be started
void UMagicMissileFiring::StopFire_Implementation()
{
	bIsBeingFired = false; 
}

// Fires the projectile. 
void UMagicMissileFiring::FireProjectile_Implementation()
{
	bWaitingForProjectileFromPool = true; 
	ProjectilePool->ActivateAnActor(); 
}

void UMagicMissileFiring::LateFireProjectile_Implementation(APoolableActor* poolableActor)
{
	AProjectile* projectile = Cast<AProjectile>(poolableActor); 
	check(projectile != nullptr);
	if (projectile != nullptr)
	{
		FVector fireLocation = FireArrow->GetComponentLocation();
		FRotator fireRotation = FireArrow->GetForwardVector().Rotation(); 

		projectile->SetActorLocation(fireLocation, false, nullptr, ETeleportType::None);
		projectile->SetActorRotation(fireRotation, ETeleportType::None); 
	}
}

void UMagicMissileFiring::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Here we list the variables we want to replicate
	DOREPLIFETIME(UMagicMissileFiring, bIsBeingFired);
	DOREPLIFETIME(UMagicMissileFiring, FireArrow);
	DOREPLIFETIME(UMagicMissileFiring, FireRate);
	DOREPLIFETIME(UMagicMissileFiring, bWaitingForProjectileFromPool);
}