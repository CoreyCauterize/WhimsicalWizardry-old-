// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpellObject.h"

// Sets default values
AItemSpellObject::AItemSpellObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemSpellObject::BeginPlay()
{
	Super::BeginPlay();
	

	if (needsToCallOnLifetimeEnd)
	{
		GetWorld()->GetTimerManager().SetTimer(LifetimeEndTimerHandle, this, &AItemSpellObject::OnLifetimeEnd, lifetime);
	}
}

// Called every frame
void AItemSpellObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpellObject::OnLifetimeEnd()
{
}

void AItemSpellObject::OnReflected()
{
}

