// Copyright 2023 INSERT TEAM NAME HERE. All Rights Reserved. 
// Derek Fallows

// Changelog
// 2023-15-09 - Created
// 

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
			APoolableActor* ActivateAnActor(); 

		UPROPERTY(Replicated, Reliable, Category = "Actor Pool")
			int Size = 5; 

		UPROPERTY(Replicated, EditAnywhere, Category = "Actor Pool")
			float PooledActorLifespawn = 0.0f; 

		UFUNCTION(Server, Reliable)
			void OnDespawn(APoolableActor* PoolActor); 

		void SetActorsHaveLifespan(bool actorshaveLifespan); 
		void SetActorLifespan(float actorLifespan); 
		void SetPoolableActor(TSubclassOf<class APoolableActor> poolableActorClass);
		void SetSizeOfPool(int size);
		void SetUseActiveAfterRunningOut(bool useActiveAfterRunningout); 
		
		// Assists in firing of projectiles for weapons     // REMOVE
		class UArrowComponent* GetFireComponent(); 
		void SetFireComponent(UArrowComponent* fireArrow); 

		UPROPERTY(Replicated)
			bool HasActorWaiting = false; 
		UPROPERTY(Replicated)
			APoolableActor* WaitingActor; 

	protected: 
		// called when the game starts
		virtual void BeginPlay() override;

		UFUNCTION(Server, Reliable)
		void ActivateActor(APoolableActor* pooledActor); 

		// Actor class to be spawned
		UPROPERTY(Replicated)
			TSubclassOf<class APoolableActor> PoolableActorClass; 

		UPROPERTY(Replicated)
			TArray<APoolableActor*> PooledActors;

		UPROPERTY(Replicated)
			TArray<int> PooledActorIndexes; 
		
		UPROPERTY(Replicated)
			bool ActorsHaveLifespan = false; 
		
		UPROPERTY(Replicated)
			bool UseActiveAfterRunningOut = true; 

		// Assists in firing of projectiles for weapons
		UArrowComponent FireArrow; 
};