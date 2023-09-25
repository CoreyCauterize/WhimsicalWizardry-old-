/*	Copyright 2023 Silver Standard Studios.All Rights Reserved.
	Derek Fallows

	Basic projectile fired by wizards without the need of a spell pickup. 
	Inherits functionality from PoolableActor to allow the projectile 
	to be pooled using an ActorPool.									*/

/*	Changelog
	2023-09-15 - Created (DF)
	2023-09-23 - Renamed from projectile to magic missile since it is the 
				 only class using this functionality in the prototype (DF)
	2023-09-24 - Cleaned up, fixed and networked (DF)
	*/

#pragma once


#include "CoreMinimal.h"
#include "../Pooling/PoolableActor.h"
#include "MagicMissile.generated.h"

UCLASS()
class WHIMSICALWIZARDRY_API AMagicMissile : public APoolableActor
{
	GENERATED_BODY()

public:
	AMagicMissile();

	// called every frame
	virtual void Tick(float Deltatime) override;

	// Takes projectile out of pool
	virtual void Activate_Implementation() override;

	// Collision capsule
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UCapsuleComponent* CollisionCapsule;

	// Sound used on impact
	UPROPERTY(EditAnywhere, Category = "Effects")
		class USoundBase* ImpactSound;

	// Static mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* Mesh;

	// Movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		class UProjectileMovementComponent* Movement;

	// Particle effect on impact
	UPROPERTY(EditAnywhere, Category = "Effects")
		class UParticleSystem* ImpactParticles;

protected:
	// called when game starts or when spawned
	virtual void BeginPlay() override;

	// Timer for delaying collision and preventing collisions with owner
	FTimerHandle CollisionDelayTimer;

	// Delays the collision being enabled to prevent colliding with the owner
	void DelayCollision(); 

	// Re-enables collision upon the delay timer's completion
	void ReEnableCollision(); 

	// Called on projectile impact
	// Hitcomponent - Component of this actor hit | OtherActor - Actor hit
	// OtherComp    - Component of other actor    | NormalImpulse - normal vector of collision
	// Hit          - Hit result
	UFUNCTION(Category = "Collision")
		virtual void OnProjectileImpact(UPrimitiveComponent* HitComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			FVector NormalImpulse, const FHitResult& Hit);

	// Projectile constants
	static const float BASE_CAPSULE_SIZE_X;
	static const float BASE_CAPSULE_SIZE_Y;
	static const float BASE_GRAVITY;
	static const float BASE_INITIAL_SPEED;
	static const float BASE_MAX_SPEED;
	static const float COLLISION_DELAY;
	static const float FIRING_OFFSET; 
};