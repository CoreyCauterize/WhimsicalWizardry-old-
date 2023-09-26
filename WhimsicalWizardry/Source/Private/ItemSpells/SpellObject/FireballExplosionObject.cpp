// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpells/SpellObject/FireballExplosionObject.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include <Net/UnrealNetwork.h>
#include "GameFramework/CharacterMovementComponent.h"



AFireballExplosionObject::AFireballExplosionObject()
{
	needsToCallOnLifetimeEnd = true;
	lifetime = 3.0f;

	fireballExplosionCollision = CreateDefaultSubobject<USphereComponent>("Fireball Explosion Collision");
	fireballExplosionCollision->SetSphereRadius(275.0f);
	fireballExplosionCollision->SetEnableGravity(false);
	fireballExplosionCollision->SetCollisionProfileName("OverlapAll");
	fireballExplosionCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetRootComponent(fireballExplosionCollision);

	fireballExplosionVisual = CreateDefaultSubobject<UNiagaraComponent>("Fireball Explosion Visual");
	fireballExplosionVisual->SetupAttachment(RootComponent);
	auto NSauto = ConstructorHelpers::FObjectFinder<UNiagaraSystem>(TEXT("/Game/Assets/NiagraSystems/Fireball/FireBoom_NS.FireBoom_NS"));
	if (NSauto.Succeeded())
	{
		UNiagaraSystem* NS = Cast<UNiagaraSystem>(NSauto.Object);
		fireballExplosionVisual->SetAsset(NS);
	}
}

void AFireballExplosionObject::Explode()
{
	TArray<AActor*> OverlappingActors;

	fireballExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (int i = 0; i < OverlappingActors.Num(); i++)
	{
		UCharacterMovementComponent* CMC = Cast<UCharacterMovementComponent>(OverlappingActors[i]->GetComponentByClass(UCharacterMovementComponent::StaticClass()));

		if (CMC)
		{
			FVector direction = OverlappingActors[i]->GetActorLocation() - GetActorLocation();
			direction.Normalize();
			direction.Z = 2;
			direction *= 50000; //TODO: member variable this, maybe const
			CMC->StopMovementImmediately();
			CMC->AddImpulse(direction);
		}
	}
}

void AFireballExplosionObject::BeginPlay()
{
	Super::BeginPlay();
}

void AFireballExplosionObject::OnLifetimeEnd()
{
	Destroy();
}

void AFireballExplosionObject::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFireballExplosionObject, fireballExplosionVisual);
	DOREPLIFETIME(AFireballExplosionObject, fireballExplosionCollision);
}