/*	Copyright 2023 Silver Standard Studios.All Rights Reserved.
	Derek Fallows

	Component class for managing a pool of preloaded actors to
	avoid repetitive object creation at runtime.
	Can only pool actors that inherit from the PoolableActor class.	*/

/*	Changelog
	2023-09-15 - Created (DF)
	2023-09-24 - Cleaned up and fixed (DF)
	*/

#pragma once

//#include "Components/ActorComponent.h"

#include "CoreMinimal.h"
#include "ActorPool.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WHIMSICALWIZARDRY_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

public:
	UActorPool();

	/*	Activates an actor, automatically choosing the next one in the pool
	and returning a pointer to it. Actor is set to spawn at origin by
	default. It must then be manually teleported elsewhere.		*/
	class APoolableActor* ActivateASpawnedActor();

	// Called by poolableActors on deactivation to alert the actorPool to 
	// put them back in the pool in the right spot in the list
	//UFUNCTION(Server, Reliable)
		void DeactivateActiveActor(class APoolableActor* activeActor);

	// Sets the out of pool lifespan of actors spawned by this pool
	void SetActorOutOfPoolLifespan(float actorOutOfPoolLifespan);

	// Sets the poolable actor class
	void SetPoolableActorClass(TSubclassOf<class APoolableActor> poolableActorClass);

	// Sets whether actors in this pool have a lifespan for which they 
	// can exist out of the pool before deactivating	
	void SetPooledActorsHaveOutOfPoolLifespan(bool pooledActorsHaveOutOfPoolLifespan);

	// Sets whether actors should collide when active
	void SetPooledActorsShouldCollide(bool pooledActorsShouldCollide); 

	// Sets whether actors should tick when active
	void SetPooledActorsShouldTick(bool pooledActorsShouldTick); 

	// Sets the amount of actors this pool should spawn
	void SetSizeOfPool(int size); 

	/*	Sets whether the pool should deactivate actors spawned by it
		when it has no already deactivated actors to activate upon a 
		request for more actors (alternatively, such requests will 
		fail to produce a new actor) */
	void SetUseActiveActorsWhenEmpty(bool useActiveActorsWhenEmpty);

	// Actor class to be spawned by this pool
	UPROPERTY(EditAnywhere, Category = "Actor Pool")
		TSubclassOf<class APoolableActor> PoolableActorClass;

protected:
	// Called when the game starts. Spawns the actors to fill the pool. 
	virtual void BeginPlay() override;

	// Time that actors spawned by this pool are allowed to exist 
	// outside of the pool
	UPROPERTY(EditAnywhere, Category = "Actor Pool")
		float ActorOutOfPoolLifespan = 3.0f;

	// Whether the actors in the pool should collide when out of the pool
	UPROPERTY(EditAnywhere, Category = "Actor Pool")
		bool bActorsCollide = true;

	// Whether the actors in this pool have a set lifespan after being spawned
	UPROPERTY(EditAnywhere, Category = "Actor Pool")
		bool bActorsHaveOutOfPoolLifespan = true;

	// Whether the actors in the pool should tick when out of the pool
	UPROPERTY(EditAnywhere, Category = "Actor Pool")
		bool bActorsTick = true;

	/*	Whether the pool should deactivate actors spawned by it
		when it has no already deactivated actors to activate
		upon a request for more actors (alternatively, such
		requests will fail to produce a new actor).
		This is usually only disabled for ammo systems and
		similar mechanics that require a specific pool size
		to be maintained									*/
		bool bUseActiveActorsWhenEmpty = true;
		
	// Amount of actors to be spawned by this pool
	UPROPERTY(EditAnywhere, Category = "Actor Pool")
		int Size = 10;

	// Array of actors in this pool
	TArray<APoolableActor*> ActorPool;

	// Indexes of actors in this pool's array that are currently active
	//UPROPERTY(Replicated)
		TArray<int> ActiveActorIndexes;
};