// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpells/SpellObject/FireballObject.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"


AFireballObject::AFireballObject()
{
	isReflectable = true;
	lifetime = 6.0f; //Could make this a const in the header
	hitForceScale = 3.0f;
	needsToCallOnLifetimeEnd = true;

	fireballCollision = CreateDefaultSubobject<UBoxComponent>("Fireball Collision");
	SetRootComponent(fireballCollision);
	fireballCollision->SetBoxExtent(FVector(2, 2, 2)); //Todo: Make this a const in FireballObject header and adjust it to be the right size

	fireballVisual = CreateDefaultSubobject<UNiagaraComponent>("Fireball Visual");
	fireballVisual->SetupAttachment(RootComponent);
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
