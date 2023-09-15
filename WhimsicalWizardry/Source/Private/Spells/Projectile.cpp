// Copyright 2023 INSERT TEAM NAME HERE. All Rights Reserved
// Derek Fallows

#include "Spells/Projectile.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"

// Projectile Constants
const float AProjectile::BASE_CAPSULE_SIZE_X = 20.0f; 
const float AProjectile::BASE_CAPSULE_SIZE_Y = 30.0f; 
const float AProjectile::BASE_GRAVITY = 1.0f;
const float AProjectile::BASE_INITIAL_SPEED = 2500.0f; 
const float AProjectile::BASE_MAX_SPEED = 4000.0f; 

// Initializes projectile
AProjectile::AProjectile()
{
	// Projectiles call Tick() every frame
	PrimaryActorTick.bCanEverTick = true; 

	// Set up collision capsule
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent")); 
	CollisionCapsule->InitCapsuleSize(BASE_CAPSULE_SIZE_X, BASE_CAPSULE_SIZE_Y); 
	CollisionCapsule->SetCollisionProfileName(TEXT("BlockAllDynamic")); 
	RootComponent = CollisionCapsule; 

	// Set up mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	Mesh->SetupAttachment(RootComponent); 

	// Register projectile impact function on a hit event
	CollisionCapsule->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileImpact);

	// Set up projectile movement
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	Movement->SetUpdatedComponent(CollisionCapsule); 
	Movement->InitialSpeed = BASE_INITIAL_SPEED; 
	Movement->MaxSpeed = BASE_MAX_SPEED; 
	Movement->ProjectileGravityScale = BASE_GRAVITY; 
	Movement->bRotationFollowsVelocity = true; 
	//Movement->Activate(false);	// deactivates for pooling later
}

// Called when game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay(); 
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called on projectile impact
// Hitcomponent - Component of this actor hit | OtherActor - Actor hit
// OtherComp    - Component of other actor    | NormalImpulse - normal vector of collision
// Hit          - Hit result
void AProjectile::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, Const FHitResult& Hit)
{
	
}