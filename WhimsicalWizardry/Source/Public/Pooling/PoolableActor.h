/*	Copyright 2023 Silver Standard Studios.All Rights Reserved.
	Derek Fallows

	Base class for any poolable actor that can be pooled with an ActorPool.
	Should be inherited from instead of AActor for any
	actor intended to be pooled this way.	*/

/*	Changelog
	2023-09-15 - Created (DF)
	2023-09-24 - Cleaned up (DF)
	*/

#pragma once

#include "CoreMinimal.h"
#include "PoolableActor.generated.h"

UCLASS()
class WHIMSICALWIZARDRY_API APoolableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APoolableActor();

	/*	Activates this actor, causing it to be visible in world and
		enabling collision and ticking every frame if set to do so.
		If actor has a specified lifespan, also begins that timer	*/
	UFUNCTION(Server, Reliable)
		virtual void Activate();

	/*	Deactivates this actor, stopping it from being visible in world
		and disabling collision and ticking every frame. Stops all timers 
		on the actor, including timers for its lifespan out of the pool. */
	UFUNCTION(Server, Reliable)
		virtual void Deactivate();

	// Gets the state of the actor, i.e. whether it is active or in the pool
	bool GetActiveState();

	// Gets the index of the actor in the pool that it spawned from
	int GetPoolIndex();

	// Gets the actor pool that spawned this actor
	class UActorPool* GetSpawningActorPool();

	// Sets whether the actor has a limited duration of existence
	// outside of the pool
	void SetHasOutOfPoolLifespan(bool hasOutOfPoolLifespan);

	// Sets whether the actor should collide when active
	void SetIfPooledActorShouldCollide(bool pooledActorShouldCollide); 

	// Sets whether the actor should tick when active
	void SetIfPooledActorShouldTick(bool pooledActorShouldTick); 

	// Sets the active state of the actor (should be used only by the pool)
	void SetActiveState(bool activeState); 

	// Sets the duration that the object exists outside of the pool 
	// if set to have a limited lifespan
	void SetOutOfPoolLifespan(float outOfPoolLifespan);

	// Sets the index of the actor in the pool that spawned it
	void SetPoolIndex(int index);

	// Sets the actor pool that spawned this actor 
	// to be referenced later
	void SetSpawningActorPool(UActorPool* spawningActorPool);

	/* Index for keeping track of actors in the pool.
	   Will be set automatically if spawned by the actor pool.
	   If this is -1 at any point, this has been spawned
				erronously through some other method */
	UPROPERTY(VisibleAnywhere)
		int PoolIndex = -1;

protected:
	// Whether the pooled actor has a lifespan
	//UPROPERTY(Replicated)
		bool bHasOutOfPoolLifespan = false;

	// Whether the pooled actor is currently active
		bool bIsActive = false;

	// Whether the pooled actor should enable collision upon activation
		bool bPooledActorShouldCollide = true;

	// Whether the pooled actor should enable ticking upon activation
		bool bPooledActorShouldTick = true;

	// The total lifespan of the pooled actor
		float OutOfPoolLifespan = 0.0f;

	// The timer before the pooled actor is returned to its pool if it has a lifespan timer
		FTimerHandle OutOfPoolLifespanTimer;

	// The pool that the actor was spawned by
		UActorPool* SpawningActorPool = nullptr;
};
