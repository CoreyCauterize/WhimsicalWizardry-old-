/*	Copyright 2023 Silver Standard Studios.All Rights Reserved.
	Derek Fallows

	Component class for managing a pool of preloaded actors to
	avoid repetitive object creation at runtime.
	Can only pool actors that inherit from the PoolableActor class.	*/

	/*	Changelog
		2023-15-09 - Created
		*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WHIMSICALWIZARDRY_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

public:
	// Creates a pool with default properties which can be set
	// in code with the setter functions below or in blueprint
	UActorPool();

	UFUNCTION(Server, Reliable, Category = "Actor Pool")
		void ActivateAnActor();

	UPROPERTY(Replicated, EditAnywhere, Category = "Actor Pool")
		int Size = 5;

	UPROPERTY(Replicated, EditAnywhere, Category = "Actor Pool")
		float PooledActorLifespan = 0.0f;

	UFUNCTION(Server, Reliable)
		void OnDespawn(APoolableActor* PoolActor);

	void SetActorsHaveLifespan(bool actorshaveLifespan);
	void SetActorLifespan(float actorLifespan);
	void SetPoolableActor(TSubclassOf<class APoolableActor> poolableActorClass);
	void SetSizeOfPool(int size);
	void SetUseActiveAfterRunningOut(bool useActiveAfterRunningout);

	// Assists in firing of projectiles for weapons				// REMOVE
	class UArrowComponent* GetFireComponent();
	void SetFireComponent(UArrowComponent* fireArrow);

	// Actor class to be spawned
	UPROPERTY(Replicated, EditAnywhere)
		TSubclassOf<class APoolableActor> PoolableActorClass;

	UPROPERTY(Replicated)
		bool HasActorWaiting = false;
	UPROPERTY(Replicated)
		APoolableActor* WaitingActor;

protected:
	// called when the game starts
	virtual void BeginPlay() override;

	// Internal function for activating any actor
	UFUNCTION(Server, Reliable)
		void ActivateActor(APoolableActor* pooledActor);

	// Actors pooled
	UPROPERTY(Replicated)
		TArray<APoolableActor*> PooledActors;

	// Indexes of actors pooled
	UPROPERTY(Replicated)
		TArray<int> PooledActorIndexes;

	// Whether the actors pooled in this pool have a set lifespan after being spawned
	UPROPERTY(Replicated)
		bool ActorsHaveLifespan = false;

	// Whether the actors managed by this pool should despawn the oldest existing actor 
	// to supply requested new instances (alternatively, it will fail to activate one while empty)	
	UPROPERTY(Replicated)
		bool UseActiveAfterRunningOut = true;

	// Assists in firing of projectiles for weapons
	UArrowComponent* FireArrow;
};