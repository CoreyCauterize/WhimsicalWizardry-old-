// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpell.h"
#include "SpellInventoryComponent.h"

// Sets default values
AItemSpell::AItemSpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemSpell::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItemSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpell::OnFire(USpellInventoryComponent* belongingInventory)
{

}


void AItemSpell::OnRolled()
{
}

