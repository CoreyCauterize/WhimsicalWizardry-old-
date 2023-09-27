// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpells/SpellObject/FireballObject.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Wizard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ItemSpells/SpellObject/FireballExplosionObject.h"
#include "NiagaraFunctionLibrary.h"





AFireballObject::AFireballObject() : bHasExploded(false)
{
	PrimaryActorTick.bCanEverTick = true;

	isReflectable = true;
	lifetime = 6.0f; //Could make this a const in the header
	hitForceScale = 300.0f;
	needsToCallOnLifetimeEnd = true;

	fireballCollision = CreateDefaultSubobject<UBoxComponent>("Fireball Collision");
	fireballCollision->SetCollisionProfileName("OverlapAll");
	SetRootComponent(fireballCollision);
	
	fireballCollision->SetBoxExtent(FVector(24, 24, 24)); //Todo: Make this a const in FireballObject header and adjust it to be the right size
	
	if (GetLocalRole() == ROLE_Authority)
	{
		fireballCollision->OnComponentBeginOverlap.AddDynamic(this, &AFireballObject::OnOverlapBegin);
	}

	fireballVisual = CreateDefaultSubobject<UNiagaraComponent>("Fireball Visual");
	fireballVisual->SetupAttachment(RootComponent);
	fireballVisual->SetRelativeLocation(FVector(-40, 0, 0));
	auto NSauto = ConstructorHelpers::FObjectFinder<UNiagaraSystem>(TEXT("/Game/Assets/NiagraSystems/Fireball/Fireball_NS.Fireball_NS"));
	if (NSauto.Succeeded())
	{
		UNiagaraSystem* NS = Cast<UNiagaraSystem>(NSauto.Object);
		fireballVisual->SetAsset(NS);
	}
	else
	{
		throw("NSauto was null");
	}
	
	FQuat rot(0, 180, 0, 0);
	fireballCollision->SetRelativeRotation(rot);

	fireballMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Fireball Movement");
	fireballMovement->SetUpdatedComponent(RootComponent);
	fireballMovement->ProjectileGravityScale = 1.5f;
}

void AFireballObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFireballObject::OnLifetimeEnd()
{
	Destroy();
}

void AFireballObject::OnReflected()
{
}

void AFireballObject::BeginPlay()
{
	Super::BeginPlay();
}


void AFireballObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWizard* HitWizard = Cast<AWizard>(OtherActor);

	if (HitWizard)
	{
		FVector LaunchVector = fireballMovement->Velocity;
		LaunchVector.Normalize();
		LaunchVector.Z = 2;
		LaunchVector *= 3;

		LaunchHitWizard(HitWizard, LaunchVector);
		
	}

	if (!bHasExploded)
	{
		bHasExploded = true;

		FActorSpawnParameters spawnParams;

		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AFireballExplosionObject* spawnedFireballExplosionActor = Cast<AFireballExplosionObject>(GetWorld()->SpawnActor<AFireballExplosionObject>(FVector(0,0,20000), FRotator::ZeroRotator, spawnParams));

		spawnedFireballExplosionActor->TeleportTo(GetActorLocation(), FRotator::ZeroRotator);

		spawnedFireballExplosionActor->Explode();

	}


	Destroy();
}

void AFireballObject::SetVelocity(FVector inVelocity)
{
	fireballMovement->Velocity = inVelocity;
}

void  AFireballObject::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFireballObject, fireballVisual);
}
