// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpells/SpellObject/FireballExplosionObject.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include <Net/UnrealNetwork.h>


AFireballExplosionObject::AFireballExplosionObject()
{
	needsToCallOnLifetimeEnd = true;
	lifetime = 6.0f;

	fireballExplosionCollision = CreateDefaultSubobject<USphereComponent>("Fireball Explosion Collision");
	fireballExplosionCollision->SetSphereRadius(5.0f);
	SetRootComponent(fireballExplosionCollision);

	fireballExplosionVisual = CreateDefaultSubobject<UNiagaraComponent>("Fireball Explosion Visual");
	fireballExplosionVisual->SetupAttachment(RootComponent);
	auto NSauto = ConstructorHelpers::FObjectFinder<UNiagaraSystem>(TEXT("/Game/Assets/NiagraSystems/Fireball/Fireball_Explosion_NS.Fireball_Explosion_NS"));
	if (NSauto.Succeeded())
	{
		UNiagaraSystem* NS = Cast<UNiagaraSystem>(NSauto.Object);
		fireballExplosionVisual->SetAsset(NS);
	}
}

void AFireballExplosionObject::BeginPlay()
{
	Super::BeginPlay();


}

void AFireballExplosionObject::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFireballExplosionObject, fireballExplosionVisual);
	DOREPLIFETIME(AFireballExplosionObject, fireballExplosionCollision);
}