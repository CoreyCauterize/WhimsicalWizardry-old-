// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpells/Spell/MagicMissilePlus.h"
#include "ItemSpells/SpellObject/MagicMissilePlusObject.h"
#include "SpellInventoryComponent.h"
#include "GameFramework/Character.h"

AMagicMissilePlus::AMagicMissilePlus()
{
	removeFromInventoryOnFired = true;
}

void AMagicMissilePlus::Server_OnFire_Implementation(USpellInventoryComponent* belongingInventory)
{
	FVector initialLocation = belongingInventory->GetOwner()->GetActorLocation();

	ACharacter* castingCharacter = Cast<ACharacter>(belongingInventory->GetOwner());

	FVector spawnLocation;
	FVector spawnVelocity;
	FRotator spawnRotation;

	if (castingCharacter)
	{
		spawnVelocity = castingCharacter->GetActorRotation().Vector() * 600; //Todo: Make the hardcoded 600 a const member variable in Fireball
		spawnLocation = initialLocation + (spawnVelocity.GetSafeNormal() * 75); //Todo: Make the hardcoded 75 a member variable in ItemSpell
		spawnRotation = castingCharacter->GetActorRotation();
		spawnVelocity.Z = 0;

		FActorSpawnParameters spawnParams;

		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* spawnedMissileActor = GetWorld()->SpawnActor<AMagicMissilePlusObject>(spawnLocation, spawnRotation, spawnParams);

		AMagicMissilePlusObject* spawnedMissile = Cast<AMagicMissilePlusObject>(spawnedMissileActor);


		if (spawnedMissile)
		{
			spawnedMissile->SetVelocity(spawnVelocity);
		}
	}
	else //This is not a character casting this, so just send it in a random direction
	{
		//Todo: implement. Mostly for potions on that one level I think
	}

	Super::Server_OnFire_Implementation(belongingInventory);
}

void AMagicMissilePlus::OnFire(USpellInventoryComponent* belongingInventory)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		Server_OnFire(belongingInventory);
	}
}
