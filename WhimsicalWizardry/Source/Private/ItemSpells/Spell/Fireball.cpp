// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpells/Spell/Fireball.h"
#include "ItemSpells/SpellObject/FireballObject.h"
#include "SpellInventoryComponent.h"
#include "GameFramework/Character.h"


AFireball::AFireball()
{
	removeFromInventoryOnFired = true; //I think it's stupid you can't do this in the initializer list
}

void AFireball::OnFire(USpellInventoryComponent* belongingInventory)
{
	FVector initialLocation = belongingInventory->GetOwner()->GetActorLocation();

	ACharacter* castingCharacter = Cast<ACharacter>(belongingInventory->GetOwner());

	FVector spawnLocation;
	FVector spawnVelocity;
	FRotator spawnRotation;

	if (castingCharacter)
	{
		spawnVelocity = castingCharacter->GetActorForwardVector() * 3; //Todo: Make the hardcoded 3 a const member variable in Fireball
		spawnLocation = initialLocation + (spawnVelocity.GetSafeNormal() * 60); //Todo: Make the hardcoded 60 a member variable in ItemSpell
		spawnRotation = castingCharacter->GetActorRotation();

		AFireballObject* spawnedFireball = Cast<AFireballObject>(GetWorld()->SpawnActor<AFireballObject>(spawnLocation, spawnRotation));

		spawnedFireball->SetVelocity(spawnVelocity);
	}
	else //This is not a character casting this, so just send it in a random direction
	{
		//Todo: implement. Mostly for potions on that one level I think
	}

	Super::OnFire(belongingInventory);
	
}
