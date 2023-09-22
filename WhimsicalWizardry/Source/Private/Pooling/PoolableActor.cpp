//	Copyright 2023 Silver Standard Studios.All Rights Reserved.
//	Derek Fallows

#include "Pooling/PoolableActor.h"	// internal inclusions
#include "Net/UnrealNetwork.h"		// unreal inclusions
#include "Pooling/ActorPool.h"

APoolableActor::APoolableActor()
{
	bReplicates = true;				// Note: make sure this spawns on serve, not client or this will not work
	SetReplicateMovement(true);
}

/* Activates actor, causing it to be visible in world
 and enabling collision and ticking every frame
 If actor has a specified lifespan, also begins that timer */
void APoolableActor::Activate_Implementation()
{
	IsActive = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);

	if (HasLifespan == true)
		GetWorldTimerManager().SetTimer(LifespanTimer, this, &APoolableActor::Deactivate, Lifespan, false);
}

// Deactivates this actor, preventing it from being visible in the 
// world, disabling collision an preventing ticking every frame
void APoolableActor::Deactivate_Implementation()
{
	IsActive = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnDespawn.Broadcast(this);
}

// Sets the lifespan of this actor if it 
// is an actor that has a limited lifespan 
void APoolableActor::SetLifeSpan(float lifespan)
{
	Lifespan = lifespan;
}

// Sets the actor's index in the index vector
void APoolableActor::SetActorIndex(int index)
{
	Index = index;
}

// Returns whether the actor is active
bool APoolableActor::GetActiveState()
{
	return IsActive;
}

// Returns the actor's index in the index vector
int APoolableActor::GetActorIndex()
{
	return Index;
}

// Returns pointer to the pool the actor is a part of
UActorPool* APoolableActor::GetPool()
{
	return ActorPool;
}

// Sets whether the actor will deactivate after a set period of time
void APoolableActor::SetHasLifespan(bool hasLifespan)
{
	HasLifespan = hasLifespan;
}

// Sets up a pointer to the pool the actor is a part of
void APoolableActor::SetPool(UActorPool* actorPool)
{
	ActorPool = actorPool;
}

void APoolableActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Variables to be replicated
	DOREPLIFETIME(APoolableActor, IsActive);
	DOREPLIFETIME(APoolableActor, HasLifespan);
	DOREPLIFETIME(APoolableActor, Lifespan);
	DOREPLIFETIME(APoolableActor, Index);
}