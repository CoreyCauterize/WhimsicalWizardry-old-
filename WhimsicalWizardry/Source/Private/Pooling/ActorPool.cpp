// Copyright 2023 INSERT TEAM NAME HERE. All Rights Reserved. 
// Derek Fallows

#include "Constants.h"
#include "Pooling/ActorPool.h"

#include "Net/UnrealNetwork.h"
#include "Pooling/PoolableActor.h"

UActorPool::UActorPool()
{
	SetIsReplicatedByDefault(true);
}

void UActorPool::BeginPlay()
{
	Super::BeginPlay(); 

	if (PoolableActorClass == nullptr)
	{ return; }

	UWorld* world = GetWorld(); 
	check(world != nullptr);

	for (int i = 0; i < Size; i++)
	{
		APoolableActor* poolActor = world->SpawnActor<APoolableActor>(PoolableActorClass, FVector(ZERO_VECTOR), FRotator(ZERO_ROTATOR)); 
		check(poolActor != nullptr); 

		poolActor->SetPool(this); 
		poolActor->Activate();
		poolActor->SetActorIndex(i);
		poolActor->OnDespawn.AddDynamic(this, &UActorPool::OnDespawn);
		PooledActors.Add(poolActor);
		poolActor->Deactivate();
	}
}

/* Activates an actor (internal function used by the ActivateAnActor function) */
void UActorPool::ActivateActor_Implementation(APoolableActor* pooledActor)
{
	pooledActor->TeleportTo(ZERO_VECTOR, ZERO_ROTATOR); 

	if (ActorsHaveLifespan == true)
	{ 
		pooledActor->SetHasLifespan(true);
		pooledActor->SetLifeSpan(PooledActorLifespan); 
	}

	pooledActor->Activate();
	PooledActorIndexes.Add(pooledActor->GetActorIndex());
}

/* Activates an actor from the pool. If it fails to activate an actor, will 
instead activate one that already exists in the world */
void UActorPool::ActivateAnActor_Implementation()
{
	for (APoolableActor* pooledActor : PooledActors)
	{
		check(pooledActor != nullptr);
		if (pooledActor->GetActiveState() == false)
		{
			ActivateActor(pooledActor); 
			WaitingActor = pooledActor; 
			HasActorWaiting = true; 
			return; 
		}
	}

	if (PooledActorIndexes.Num() > 0 && UseActiveAfterRunningOut == true)
	{
		int pooledActorIndex = PooledActorIndexes[0];
		PooledActorIndexes.Remove(pooledActorIndex); 
		APoolableActor* pooledActor = Pooledctors[pooledActorsIndex]; 
		check(pooledActor != nullptr); 

		pooledActor->Deactivate(); 
		ActivateActor(pooledActor); 
		PooledActorIndexes.Add(pooledActor->GetActorIndex()); 
		WaitingActor = pooledActor; 
		HasActorWaiting = true; 
		return; 
	}
}

/* Called automatically when deactivating an actor using the OnDespawn Delegate in PoolableActor */
void UActorPool::OnDespawn_Implementation(APoolableActor* PoolActor)
{
	PooledActorIndexes.Remove(PoolActor->GetActorIndex()); 
}

/* Sets whether the actors in the pool will only exist in the world for a set period of time */
void UActorPool::SetActorsHaveLifespan(bool actorsHaveLifespan)
{
	ActorsHaveLifespan = actorsHaveLifespan; 
}

/* Sets the time that the actors will exist in the world, 
if they are only set to exist in the world for a set time*/
void UActorPool::SetActorLifespan(float actorLifespan)
{
	PooledActorLifespan = actorLifespan; 
}

/* Sets the poolable ctor class to spawn */
void UActorPool::SetPoolableActor(TSubclassOf<class APoolablActor> poolableActorClass)
{
	PoolableActorClass = poolableActorClass; 
}

