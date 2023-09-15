// Copyright 2023 INSERT COMPANY NAME HERE. All Rights Reserved.
// Derek Fallows

// Changelog
// 2023-15-09 - Created
// 

#pragma once

#include "CoreMinimal.h"
#include "Projectile.generated.h"

// Base projectile class from which all projectiles (usually created by spells) inherit functionality

UCLASS()
class WHIMSICALWIZARDRY_API AProjectile : public AActor
{
	GENERATED_BODY()

	public: 
		AProjectile();
		
		// called every frame
		virtual void Tick(float Deltatime) override; 

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

		// Called on projectile impact
		// Hitcomponent - Component of this actor hit | OtherActor - Actor hit
		// OtherComp    - Component of other actor    | NormalImpulse - normal vector of collision
		// Hit          - Hit result
		UFUNCTION(Category = "Collision")
		virtual void OnProjectileImpact(UPrimitiveComponent* HitComponent, 
			AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			const FHitResult& Hit);

		// Projectile constants
		static const float BASE_CAPSULE_SIZE_X; 
		static const float BASE_CAPSULE_SIZE_Y; 
		static const float BASE_GRAVITY; 
		static const float BASE_INITIAL_SPEED; 
		static const float BASE_MAX_SPEED; 

};