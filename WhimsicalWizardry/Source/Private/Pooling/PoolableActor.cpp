//	Copyright 2023 Silver Standard Studios. All rights reserved.
//	Derek Fallows

#include "Pooling/PoolableActor.h"	// internal inclusions
#include "Net/UnrealNetwork.h"		// unreal inclusions
#include "Pooling/ActorPool.h"

APoolableActor::APoolableActor()
{
	bReplicates = true;	

	// Change this setting in the inheriting class 
	// for any actor that shouldn't replicate movement
	SetReplicateMovement(true);
}

/*	Activates this actor, causing it to be visible in world and
	enabling collision and ticking every frame if set to do so.
	If actor has a specified lifespan, also begins that timer	*/
void APoolableActor::Activate_Implementation()
{
	bIsActive = true; 

	SetActorHiddenInGame(false); 

	if (bPooledActorShouldCollide == true)
		SetActorEnableCollision(true);
	
	if (bPooledActorShouldTick == true)
		SetActorTickEnabled(true); 
	
	if (bHasOutOfPoolLifespan == true)
		GetWorldTimerManager().SetTimer(OutOfPoolLifespanTimer, this, &APoolableActor::Deactivate, OutOfPoolLifespan, false); 
}

/*	Deactivates this actor, stopping it from being visible in world
	and disabling collision and ticking every frame. Stops all timers
	on the actor, including timers for its lifespan out of the pool. */
void APoolableActor::Deactivate_Implementation()
{
	bIsActive = false; 

	SetActorHiddenInGame(true); 

	SetActorEnableCollision(false); 

	SetActorTickEnabled(false); 

	GetWorldTimerManager().ClearAllTimersForObject(this); 

	SpawningActorPool->DeactivateActiveActor(this); 
}

// Gets the state of the actor, i.e. whether it is active or in the pool
bool APoolableActor::GetActiveState()
	{ return bIsActive; }

// Gets the index of the actor in the pool that it spawned from
int APoolableActor::GetPoolIndex()
	{ return PoolIndex; }

// Gets the actor pool that spawned this actor
UActorPool* APoolableActor::GetSpawningActorPool()
	{ return SpawningActorPool; }

// Sets whether the actor has a limited duration of existence
// outside of the pool
void APoolableActor::SetHasOutOfPoolLifespan(bool hasOutOfPoolLifespan)
	{ bHasOutOfPoolLifespan = hasOutOfPoolLifespan; }

// Sets whether the actor should collide when active
void APoolableActor::SetIfPooledActorShouldCollide(bool pooledActorShouldCollide)
	{ bPooledActorShouldCollide = pooledActorShouldCollide; }

// Sets whether the actor should tick when active
void APoolableActor::SetIfPooledActorShouldTick(bool pooledActorShouldTick)
	{ bPooledActorShouldTick = pooledActorShouldTick; }

// Sets the active state of the actor (should be used only by the pool)
void APoolableActor::SetActiveState(bool activeState)
	{ bIsActive = activeState; }

// Sets the duration that the object exists outside of the pool 
// if set to have a limited lifespan
void APoolableActor::SetOutOfPoolLifespan(float outOfPoolLifespan)
	{ OutOfPoolLifespan = outOfPoolLifespan; }

// Sets the index of the actor in the pool that spawned it
void APoolableActor::SetPoolIndex(int index)
	{ PoolIndex = index; }

// Sets the actor pool that spawned this actor 
// to be referenced later
void APoolableActor::SetSpawningActorPool(UActorPool* spawningActorPool)
	{ SpawningActorPool = spawningActorPool; }


//void APoolableActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	// Variables to be replicated
//	/*DOREPLIFETIME(APoolableActor, bHasOutOfPoolLifespan);
//	DOREPLIFETIME(APoolableActor, bIsActive);
//	DOREPLIFETIME(APoolableActor, OutOfPoolLifespan);
//	DOREPLIFETIME(APoolableActor, bPooledActorShouldCollide);
//	DOREPLIFETIME(APoolableActor, bPooledActorShouldTick);
//	DOREPLIFETIME(APoolableActor, PoolIndex);*/
//}