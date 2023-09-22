/*	Copyright 2023 Silver Standard Studios.All Rights Reserved.
	Derek Fallows

	Base class for any poolable actor that can be pooled with an ActorPool.
	Should be inherited from instead of AActor for any
	actor intended to be pooled this way.	*/

/*	Changelog
	2023-15-09 - Created
	*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDespawn, APoolableActor*, PoolActor);

UCLASS()
class WHIMSICALWIZARDRY_API APoolableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APoolableActor();

	FOnDespawn OnDespawn;

	UFUNCTION(Server, Reliable)
	virtual void Activate();

	UFUNCTION(Server, Reliable)
	virtual void Deactivate();

	void SetLifeSpan(float lifeSpawn);
	void SetActorIndex(int index);

	bool GetActiveState();
	int GetActorIndex();
	class UActorPool* GetPool();

	void SetHasLifespan(bool hasLifespan);
	void SetPool(UActorPool* actorPool);

protected:
	UPROPERTY(Replicated)
	bool IsActive;
	UPROPERTY(Replicated)
	bool HasLifespan = false;
	UPROPERTY(Replicated)
	float Lifespan = 0.0f;
	UPROPERTY(Replicated)
	int Index;

	FTimerHandle LifespanTimer;
	UActorPool* ActorPool;
};
