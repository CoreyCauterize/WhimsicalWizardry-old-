//	Copyright 2023 Silver Standard Studios. All rights reserved.
//	Derek Fallows

#include "MagicProjectile/MagicMissile.h"				// internal inclusions
#include "MagicProjectile/MagicMissileFiring.h"
#include "Pooling/ActorPool.h"
#include "Pooling/PoolableActor.h"
#include "Wizard.h"
#include "Components/ArrowComponent.h"					// unreal inclusions
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"

// Projectile Constants
const float AMagicMissile::BASE_CAPSULE_SIZE_X = 20.0f;
const float AMagicMissile::BASE_CAPSULE_SIZE_Y = 30.0f;
const float AMagicMissile::BASE_GRAVITY = 1.0f;
const float AMagicMissile::BASE_INITIAL_SPEED = 2500.0f;
const float AMagicMissile::BASE_MAX_SPEED = 4000.0f;
const float AMagicMissile::COLLISION_DELAY = 1.0f;
const float AMagicMissile::FIRING_OFFSET = 45.0f;

// Initializes projectile
AMagicMissile::AMagicMissile()
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
	CollisionCapsule->OnComponentHit.AddDynamic(this, &AMagicMissile::OnProjectileImpact);

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
void AMagicMissile::BeginPlay()
{
	Super::BeginPlay();
}

// Delays the collision being enabled to prevent colliding with the owner
void AMagicMissile::DelayCollision()
{
	SetActorEnableCollision(false);
	GetWorldTimerManager().SetTimer(CollisionDelayTimer, this, &AMagicMissile::ReEnableCollision, COLLISION_DELAY, false); 
}

// Re-enables collision upon the delay timer's completion
void AMagicMissile::ReEnableCollision()
{
	SetActorEnableCollision(true); 
}

// Called every frame
void AMagicMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Take projectile out of the pool
void AMagicMissile::Activate_Implementation()
{
	// Cause the projectile to start moving again
	Movement->Activate(true); 
	Movement->SetUpdatedComponent(GetRootComponent());

	AWizard* wizard = Cast<AWizard>(GetSpawningActorPool()->GetOwner()); 

	UArrowComponent* firingArrow = wizard->GetMagicMissileFiringArrow(); 
	
	TeleportTo(firingArrow->GetComponentLocation() + firingArrow->GetForwardVector() * FIRING_OFFSET, FRotator().ZeroRotator);\
	
	SetActorRotation(wizard->GetActorRotation()); 

	//SetActorRotation(firingArrow->GetForwardVector().Rotation());

	FVector fVelocity = GetActorForwardVector()* Movement->InitialSpeed; 
	Movement->Velocity.Set(fVelocity.X, fVelocity.Y, fVelocity.Z); 

	//Movement->SetVelocityInLocalSpace(GetActorForwardVector() * Movement->InitialSpeed); 
		
	// Call super AFTER to enable collision without colliding with things at orgigin (should change that later to move to origin in deactivate)
	Super::Activate_Implementation();

	//DelayCollision(); 


	/*Movement->Velocity = GetPool()->GetFireComponent()->GetForwardVector()
												* Movement->InitialSpeed;*/
												//Movement->SetVelocityInLocalSpace(GetPool()->GetFireComponent()->GetForwardVector() * Movement->InitialSpeed); 
}

/* Called on projectile impact
   Hitcomponent - Component of this actor hit | OtherActor - Actor hit
   OtherComp    - Component of other actor    | NormalImpulse - normal vector of collision
   Hit          - Hit result				  |											*/
void AMagicMissile::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor,
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