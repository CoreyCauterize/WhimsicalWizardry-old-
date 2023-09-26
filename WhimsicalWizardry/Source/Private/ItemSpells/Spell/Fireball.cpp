// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpells/Spell/Fireball.h"
#include "ItemSpells/SpellObject/FireballObject.h"
#include "SpellInventoryComponent.h"
#include "GameFramework/Character.h"


AFireball::AFireball()
{
	removeFromInventoryOnFired = true; //I think it's stupid you can't do this in the initializer list
}

void AFireball::Server_OnFire_Implementation(USpellInventoryComponent* belongingInventory)
{
	FVector initialLocation = belongingInventory->GetOwner()->GetActorLocation();

	ACharacter* castingCharacter = Cast<ACharacter>(belongingInventory->GetOwner());

	FVector spawnLocation;
	FVector spawnVelocity;
	FRotator spawnRotation;

	if (castingCharacter)
	{
		spawnVelocity = castingCharacter->GetActorRotation().Vector() * 600; //Todo: Make the hardcoded 600 a const member variable in Fireball
		spawnLocation = initialLocation + (spawnVelocity.GetSafeNormal() * 60); //Todo: Make the hardcoded 60 a member variable in ItemSpell
		spawnRotation = castingCharacter->GetActorRotation();
		spawnVelocity.Z = 900;

		FActorSpawnParameters spawnParams;

		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* spawnedFireballActor = GetWorld()->SpawnActor<AFireballObject>(spawnLocation, spawnRotation, spawnParams);

		AFireballObject* spawnedFireball = Cast<AFireballObject>(spawnedFireballActor);


		if (spawnedFireball)
		{
			spawnedFireball->SetVelocity(spawnVelocity);
		}
	}
	else //This is not a character casting this, so just send it in a random direction
	{
		//Todo: implement. Mostly for potions on that one level I think
	}

	Super::Server_OnFire_Implementation(belongingInventory);
}

void AFireball::OnFire(USpellInventoryComponent* belongingInventory)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		Server_OnFire(belongingInventory);
	}
}
