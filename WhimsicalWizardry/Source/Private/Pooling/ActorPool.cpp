//	Copyright 2023 Silver Standard Studios.All Rights Reserved.
//	Derek Fallows

#include "Pooling/ActorPool.h"		// internal inclusions
#include "Net/UnrealNetwork.h"		// unreal inclusions
#include "Pooling/PoolableActor.h"

UActorPool::UActorPool()
{
	SetIsReplicatedByDefault(true);
	UWorld* world = GetWorld();
	for (int i = 0; i < 1; i++)
	{
		if (world)
		{
			APoolableActor* poolActor =													// CURRENT ISSUE
				world->SpawnActor<APoolableActor>(
					FVector(FVector::ZeroVector), FRotator(FRotator::ZeroRotator));

		}
		
		//check(poolActor != nullptr);

		//poolActor->SetPool(this);
		//poolActor->SetActorIndex(i);
		//poolActor->OnDespawn.AddDynamic(this, &UActorPool::OnDespawn);
		//PooledActors.Add(poolActor);
		//poolActor->Deactivate();
	}
}

void UActorPool::BeginPlay()
{
	Super::BeginPlay();

	if (PoolableActorClass == nullptr)
	{
		return;
	}

	
	//check(world != nullptr);

	
}

// Activates an actor (internal function used by the ActivateAnActor function) 
void UActorPool::ActivateActor_Implementation(APoolableActor* pooledActor)
{
	pooledActor->TeleportTo(FVector::ZeroVector, FRotator::ZeroRotator);

	if (ActorsHaveLifespan == true)
	{
		pooledActor->SetHasLifespan(true);
		pooledActor->SetLifeSpan(PooledActorLifespan);
	}

	pooledActor->Activate();
	PooledActorIndexes.Add(pooledActor->GetActorIndex());
}

// Activates an actor from the pool. If it fails to activate an actor, will 
// instead activate one that already exists in the world 
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
		APoolableActor* pooledActor = PooledActors[pooledActorIndex];
		check(pooledActor != nullptr);

		pooledActor->Deactivate();
		ActivateActor(pooledActor);
		PooledActorIndexes.Add(pooledActor->GetActorIndex());
		WaitingActor = pooledActor;
		HasActorWaiting = true;
		return;
	}
}

// Called automatically when deactivating an actor using the OnDespawn Delegate in PoolableActor
void UActorPool::OnDespawn_Implementation(APoolableActor* PoolActor)
{
	PooledActorIndexes.Remove(PoolActor->GetActorIndex());
}

// Sets whether the actors in the pool will only exist in the world for a set period of time
void UActorPool::SetActorsHaveLifespan(bool actorsHaveLifespan)
{
	ActorsHaveLifespan = actorsHaveLifespan;
}

// Sets the time that the actors will exist in the world, 
// if they are only set to exist in the world for a set time
void UActorPool::SetActorLifespan(float actorLifespan)
{
	PooledActorLifespan = actorLifespan;
}

void UActorPool::SetPoolableActor(TSubclassOf<class APoolableActor> poolableActorClass)
{
	PoolableActorClass = poolableActorClass;
}

// Sets the amount of actors that will be in the pool in total
void UActorPool::SetSizeOfPool(int size)
{
	Size = size;
}

// Sets whether the pool will start using active actors once it runs out of inactive actors to use
void UActorPool::SetUseActiveAfterRunningOut(bool useActiveAfterRunningOut)
{
	UseActiveAfterRunningOut = useActiveAfterRunningOut;
}

// Gets the fire component stored in the pool (used to help projectiles acess fireArrows
UArrowComponent* UActorPool::GetFireComponent()
{
	return FireArrow;
}

// Sets up the fire component to be stored in the pool (used to help projectiles access fireArrows)
void UActorPool::SetFireComponent(UArrowComponent* fireArrow)
{
	FireArrow = fireArrow;
}

void UActorPool::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Variables to be replicated
	DOREPLIFETIME(UActorPool, ActorsHaveLifespan);
	DOREPLIFETIME(UActorPool, HasActorWaiting);
	DOREPLIFETIME(UActorPool, PoolableActorClass);
	DOREPLIFETIME(UActorPool, PooledActorLifespan);
	DOREPLIFETIME(UActorPool, Size);
	DOREPLIFETIME(UActorPool, UseActiveAfterRunningOut);
	DOREPLIFETIME(UActorPool, WaitingActor);
}