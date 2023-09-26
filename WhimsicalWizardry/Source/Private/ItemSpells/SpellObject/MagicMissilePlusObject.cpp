// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpells/SpellObject/MagicMissilePlusObject.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Wizard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/ProjectileMovementComponent.h"


AMagicMissilePlusObject::AMagicMissilePlusObject()
{
	PrimaryActorTick.bCanEverTick = true;

	isReflectable = true;
	lifetime = 6.0f; //Could make this a const in the header
	hitForceScale = 300.0f;
	needsToCallOnLifetimeEnd = true;

	missileCollision = CreateDefaultSubobject<UBoxComponent>("MissilePlus Collision");
	missileCollision->SetCollisionProfileName("OverlapAll");
	SetRootComponent(missileCollision);

	missileCollision->SetBoxExtent(FVector(24, 24, 24)); //Todo: Make this a const in FireballObject header and adjust it to be the right size

	if (GetLocalRole() == ROLE_Authority)
	{
		missileCollision->OnComponentBeginOverlap.AddDynamic(this, &AMagicMissilePlusObject::OnOverlapBegin);
	}

	missileVisual = CreateDefaultSubobject<UNiagaraComponent>("MissilePlus Visual");
	missileVisual->SetupAttachment(RootComponent);
	missileVisual->SetRelativeLocation(FVector(-40, 0, 0));
	auto NSauto = ConstructorHelpers::FObjectFinder<UNiagaraSystem>(TEXT("/Game/Assets/NiagraSystems/MagicMissilePlus/MagicMissilePlus_NS.MagicMissilePlus_NS"));
	if (NSauto.Succeeded())
	{
		UNiagaraSystem* NS = Cast<UNiagaraSystem>(NSauto.Object);
		missileVisual->SetAsset(NS);
	}
	else
	{
		throw("NSauto was null");
	}

	FQuat rot(0, 180, 0, 0);
	missileCollision->SetRelativeRotation(rot);

	missileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("MissilePlus Movement");
	missileMovement->SetUpdatedComponent(RootComponent);
	missileMovement->ProjectileGravityScale = 0.0f;
}

void AMagicMissilePlusObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMagicMissilePlusObject::OnLifetimeEnd()
{
	Destroy();
}

void AMagicMissilePlusObject::OnReflected()
{
}

void AMagicMissilePlusObject::BeginPlay()
{
	Super::BeginPlay();
}

void AMagicMissilePlusObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWizard* HitWizard = Cast<AWizard>(OtherActor);

	if (HitWizard)
	{
		FVector LaunchVector = missileMovement->Velocity;
		LaunchVector.Normalize();
		LaunchVector.Z = 2;
		LaunchVector *= 5;

		LaunchHitWizard(HitWizard, LaunchVector);

	}

	Destroy();
}

void AMagicMissilePlusObject::SetVelocity(FVector inVelocity)
{
	missileMovement->Velocity = inVelocity;
}

void AMagicMissilePlusObject::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMagicMissilePlusObject, missileVisual);
}