/*	Copyright 2023 Silver Standard Studios. All rights reserved.
	Derek Fallows

	Component allowing a controlled character to fire basic magical
	projectiles that don't require getting a pickup.			*/

/*	Changelog
	2023-09-15 - Created (DF)
	2023-09-24 - Cleaned up (DF)
	*/

#pragma once


#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
#include "MagicMissileFiring.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WHIMSICALWIZARDRY_API UMagicMissileFiring : public UActorComponent
{
	GENERATED_BODY()

public:
	UMagicMissileFiring();

	// Gets the firing arrow the component fires from
	// (usually attached to and set by the owner)
	UFUNCTION(Category = "Firing")
		class UArrowComponent* GetFiringArrow(); 

	// Sets the firing arrow the component fires from
	// (usually attached to and set by the owner)
	UFUNCTION(Category = "Firing")
		void SetFiringArrow(class UArrowComponent* firingArrow);

	// Begins projectile fire sequence
	// UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Gameplay")
		void StartFire();

	// Ends the fire action and allows a new fire action to be started
	// UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Gameplay")
		void StopFire();

	// Sound played when weapon fires
	UPROPERTY(EditAnywhere, Category = "Effects")
		class USoundBase* FireSound = nullptr;

	// Actor class to be spawned by this pool
	UPROPERTY(EditAnywhere, Category = "Actor Pool")
		TSubclassOf<class APoolableActor> PoolableActorClass;

protected:
	// Called when game starts or when spawned
	virtual void BeginPlay() override;

	// Fires the projectile
	//UFUNCTION(Server, Reliable, Category = "Gameplay")
		virtual void FireProjectile();

	// Whether the weapon is being fired
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		bool bIsBeingFired = false;

	// Makes the weapon wait for a projectile if there is any lag
	UPROPERTY(BlueprintReadOnly, Category = "Network")
		bool bWaitingForProjectileFromPool = false;

	// Delay between shots in seconds, 
	// tracked so it can be changed by other factors
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float FireRate;

	// Timer handle for providing fire rate delay
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		FTimerHandle FiringTimer;

	// Pool of projectiles - set in constructor of weapon to
	// fill with appropriate projectile type
	class UActorPool* ProjectilePool;

	// Arrow Component on actor, used to determine where to fire projectiles
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		UArrowComponent* FiringArrow = nullptr;
		
	// Firing constants
	static const float BASE_FIRE_RATE;
	static const float MAGIC_MISSILE_LIFESPAN;
	static const int MAGIC_MISSILE_AMOUNT = 10;
	static const FString EMPTY_STRING;
};

//archive

/* Called every frame
   DeltaTime        - Time since last update
   ELevelTick       - The type of tick
   ThisTickFunction - Pointer to this tick function */
   /*virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	   FActorComponentTickFunction* ThisTickFunction) override;*/