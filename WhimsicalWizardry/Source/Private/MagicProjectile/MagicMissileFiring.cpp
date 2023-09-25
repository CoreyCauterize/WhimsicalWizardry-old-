//	Copyright 2023 Silver Standard Studios. All rights reserved.
//	Derek Fallows

#include "MagicProjectile/MagicMissileFiring.h"		// internal inclusions
#include "MagicProjectile/MagicMissile.h"
#include "Pooling/ActorPool.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Components/ActorComponent.h"				// unreal inclusions
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Weapon constants
const float UMagicMissileFiring::BASE_FIRE_RATE = 0.25f;
const float UMagicMissileFiring::MAGIC_MISSILE_LIFESPAN = 10.0f;
const FString UMagicMissileFiring::EMPTY_STRING = "";

UMagicMissileFiring::UMagicMissileFiring() : FireRate(BASE_FIRE_RATE)
{
	// This component doesn't need to tick. If this changes, remove this
	PrimaryComponentTick.bCanEverTick = false;

	ProjectilePool = CreateDefaultSubobject<UActorPool>("Magic Missile Pool", false);
	ProjectilePool->SetPooledActorsHaveOutOfPoolLifespan(true); 
	ProjectilePool->SetActorOutOfPoolLifespan(MAGIC_MISSILE_LIFESPAN);
	ProjectilePool->SetPooledActorsShouldCollide(true); 
	ProjectilePool->SetPooledActorsShouldTick(false);
	ProjectilePool->SetSizeOfPool(MAGIC_MISSILE_AMOUNT);

	//SetIsReplicatedByDefault(true);
}

// Called when game starts or when spawned
void UMagicMissileFiring::BeginPlay()
{
	Super::BeginPlay();
	ProjectilePool->SetPoolableActorClass(PoolableActorClass);
}

// Gets the firing arrow the component fires from
// (usually attached to and set by the owner)
UArrowComponent* UMagicMissileFiring::GetFiringArrow()
{
	check(FiringArrow != nullptr); 
	return FiringArrow;
}

// Sets up the FireArrow the component fires from
void UMagicMissileFiring::SetFiringArrow(UArrowComponent* firingArrow)
{
	check(firingArrow != nullptr)
	FiringArrow = firingArrow;
}

// Begins projectile fire sequence. 
void UMagicMissileFiring::StartFire()
{
	if (bIsBeingFired == false)
	{
		bIsBeingFired = true; 
		
		// Set timer for fire delay
		UWorld* world = GetWorld(); 
		FTimerHandle& firingTimerHandle = FiringTimer; 
		world->GetTimerManager().SetTimer(firingTimerHandle, this, 
					&UMagicMissileFiring::StopFire, FireRate, false); 
		
		// Fire the projectile
		FireProjectile(); 

		UGameplayStatics::PlaySoundAtLocation(nullptr, FireSound, 
								  GetOwner()->GetActorLocation(), 
												1.0f, 1.0f, 0.0f, 
									  nullptr, nullptr, nullptr); 

		// This is where animation can be called to play when we have one. 
	}
}

// Ends the fire sequence and allows a new fire sequence to be started
void UMagicMissileFiring::StopFire()
	{ bIsBeingFired = false; }

// Fires the projectile. 
void UMagicMissileFiring::FireProjectile()
{
	AMagicMissile* magicMissile = Cast<AMagicMissile>(ProjectilePool->ActivateASpawnedActor()); 
	check(magicMissile != nullptr); 
}

//void UMagicMissileFiring::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	// Here we list the variables we want to replicate
//	/*DOREPLIFETIME(UMagicMissileFiring, bIsBeingFired);
//	DOREPLIFETIME(UMagicMissileFiring, FireRate);
//	DOREPLIFETIME(UMagicMissileFiring, FiringArrow); 
//	DOREPLIFETIME(UMagicMissileFiring, bWaitingForProjectileFromPool);*/
//}

// archive

/* Called every frame.
   DeltaTime        - Time since last update
   ELevelTick       - The type of tick
   ThisTickFunction - Pointer to this tick function	*/
   //void UMagicMissileFiring::TickComponent(float DeltaTime, ELevelTick TickType,
   //	FActorComponentTickFunction* ThisTickFunction)
   //{
   //	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
   //}