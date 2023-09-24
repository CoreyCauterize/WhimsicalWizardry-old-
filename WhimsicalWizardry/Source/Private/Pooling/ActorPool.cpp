//	Copyright 2023 Silver Standard Studios.All Rights Reserved.
//	Derek Fallows

#include "Pooling/ActorPool.h"		// internal inclusions
#include "Net/UnrealNetwork.h"		// unreal inclusions
#include "Pooling/PoolableActor.h"

UActorPool::UActorPool()
{
	SetIsReplicatedByDefault(true);
}

// Called when the game starts. Spawns the actors to fill the pool. 
void UActorPool::BeginPlay()
{
	Super::BeginPlay();

	if (PoolableActorClass != nullptr)
	{
		// Spawns a number of actors based on the size of the pool
		UWorld* const world = GetWorld(); 
		check(world != nullptr); 
		for (int i = 0; i < Size; i++)
		{
			// Spawns an actor
			APoolableActor* poolableActor = world->SpawnActor<APoolableActor>(
													PoolableActorClass, 
													FVector().ZeroVector, 
													FRotator().ZeroRotator); 
			if (poolableActor != nullptr)
			{
				// Deactivates the actor's functionality until it is activated again
				poolableActor->SetActiveState(false); 
				poolableActor->SetActorHiddenInGame(true); 
				poolableActor->SetActorEnableCollision(false); 
				poolableActor->SetActorTickEnabled(false);

				// Sets the actor's properties based on this pool's properties
				poolableActor->SetHasOutOfPoolLifespan(ActorsHaveOutOfPoolLifespan);
				poolableActor->SetIfPooledActorShouldCollide(ActorsCollide); 
				poolableActor->SetIfPooledActorShouldTick(ActorsTick);
				poolableActor->SetOutOfPoolLifespan(ActorOutOfPoolLifespan);
				poolableActor->SetSpawningActorPool(this);

				// Adds the actor to the pool
				poolableActor->SetPoolIndex(i);
				ActorPool.Add(poolableActor); 
			}
		}
	}
}

/*	Activates an actor, automatically choosing the next one in the pool
	and returning a pointer to it. Actor is set to spawn at origin by
	default. It must then be manually teleported elsewhere.		*/
APoolableActor* UActorPool::ActivateASpawnedActor()
{
	// activates an actor for use
	for (APoolableActor* poolableActor : ActorPool)
	{
		// Only activates an actor this way if it is in the pool and is not active
		if (poolableActor != nullptr && poolableActor->GetActiveState() == false)
		{
			// Teleports the actor to origin to prevent any 
			// interference from its previous position
			poolableActor->TeleportTo(FVector().ZeroVector, 
									FRotator().ZeroRotator);

			// Re-enables the actor's functionality
			poolableActor->Activate(); 

			// Adds the actor's index to an array of active 
			// indexes to keep track of it
			ActiveActorIndexes.Add(poolableActor->GetPoolIndex()); 
			
			// Returns a ptr to the actor so it can be identified 
			// by the class that called for it
			return poolableActor; 
		}
	}

	// If the above failed to produce a valid actor (usually because all actors 
	// in the pool are active) and the pool is allowed to deactivate actors to 
	// fill requests for actors, it does so. 
	if (ActiveActorIndexes.Num() > 0 && UseActiveActorsWhenEmpty == true)
	{
		// Gets unique index of oldest active pooled actor in the scene
		int requiredActorIndex = ActiveActorIndexes[0]; 

		// Remove that unique index from the array of active actors since
		// it is to be deactivated and reactivated
		ActiveActorIndexes.Remove(requiredActorIndex);

		// Gets a ptr to the actor at that index
		APoolableActor* requiredActor = ActorPool[requiredActorIndex];

		if (requiredActor != nullptr)
		{
			// Teleports the actor to origin to prevent any 
			// interference from its previous position
			requiredActor->TeleportTo(FVector().ZeroVector,
				FRotator().ZeroRotator); 
			requiredActor->Activate();
			// Adds the actor's index to an array of active 
			// indexes to keep track of it
			ActiveActorIndexes.Add(requiredActor->GetPoolIndex());
			// Returns a ptr to the actor so it can be identified 
			// by the class that called for it
			return requiredActor;
		}
	}
}

// Called by poolableActors on deactivation to alert the actorPool to 
// remove them from the active actors index list
void UActorPool::DeactivateActiveActor(APoolableActor* activeActor)
{ 
	// Remove the actor's unique index from the array of active actors 
	ActiveActorIndexes.Remove(activeActor->GetPoolIndex());
}

// Sets the out of pool lifespan of actors spawned by this pool
void UActorPool::SetActorOutOfPoolLifespan(float actorOutOfPoolLifespan)
	{ ActorOutOfPoolLifespan = actorOutOfPoolLifespan; }

// Sets whether actors in this pool have a lifespan for which they 
// can exist out of the pool before deactivating	
void UActorPool::SetPooledActorsHaveOutOfPoolLifespan(bool pooledActorsHaveOutOfPoolLifespan)
	{ ActorsHaveOutOfPoolLifespan = pooledActorsHaveOutOfPoolLifespan; }

// Sets whether actors should collide when active
void UActorPool::SetPooledActorsShouldCollide(bool pooledActorsShouldCollide)
	{ ActorsCollide = pooledActorsShouldCollide; }

// Sets whether actors should tick when active
void UActorPool::SetPooledActorsShouldTick(bool pooledActorsShouldTick)
	{ ActorsTick = pooledActorsShouldTick; }

// Sets the amount of actors this pool should spawn
void UActorPool::SetSizeOfPool(int size)
	{ Size = size; }

/*	Sets whether the pool should deactivate actors spawned by it
	when it has no already deactivated actors to activate upon a
	request for more actors (alternatively, such requests will
	fail to produce a new actor) */
void UActorPool::SetUseActiveActorsWhenEmpty(bool useActiveActorsWhenEmpty)
	{ UseActiveActorsWhenEmpty = useActiveActorsWhenEmpty; } 

void UActorPool::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Variables to be replicated
	DOREPLIFETIME(UActorPool, ActorOutOfPoolLifespan);
	DOREPLIFETIME(UActorPool, ActorsHaveOutOfPoolLifespan);
	DOREPLIFETIME(UActorPool, ActorsCollide);
	DOREPLIFETIME(UActorPool, ActorsTick);
	DOREPLIFETIME(UActorPool, Size);
}