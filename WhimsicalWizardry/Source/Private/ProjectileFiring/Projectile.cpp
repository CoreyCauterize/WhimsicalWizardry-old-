//	Copyright 2023 Silver Standard Studios.All Rights Reserved.
//	Derek Fallows

#include "ProjectileFiring/Projectile.h"						// internal inclusions
#include "Pooling/ActorPool.h"
#include "Components/ArrowComponent.h"				// unreal inclusions
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
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
	Movement->Activate(false);	// activated later when taken out of the pool
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

// Take projectile out of the pool
void AProjectile::Activate_Implementation()
{
	APoolableActor::Activate();

	// cause the projectile to start moving again
	Movement->Activate(true);
	Movement->SetUpdatedComponent(GetRootComponent());
	Movement->SetVelocityInLocalSpace(GetPool()->GetFireComponent()->GetForwardVector() * Movement->InitialSpeed);

	/*Movement->Velocity = GetPool()->GetFireComponent()->GetForwardVector()
												* Movement->InitialSpeed;*/
												//Movement->SetVelocityInLocalSpace(GetPool()->GetFireComponent()->GetForwardVector() * Movement->InitialSpeed); 
}

// Put projectile back into the pool
void AProjectile::Deactivate_Implementation()
{
	APoolableActor::Deactivate();
}

/* Called on projectile impact
   Hitcomponent - Component of this actor hit | OtherActor - Actor hit
   OtherComp    - Component of other actor    | NormalImpulse - normal vector of collision
   Hit          - Hit result				  |											*/
void AProjectile::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector spawnLocation = GetActorLocation();

	// Emit impact particles
	if (ImpactParticles != nullptr)
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticles, spawnLocation,
			FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);

	// Play impact sound
	if (ImpactSound != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound,
			spawnLocation, FRotator::ZeroRotator);

	// Deactivate the projectile so it can be used again later
	Deactivate();
}