// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellInventoryComponent.h"
#include "ItemSpell.h"

// Sets default values for this component's properties
USpellInventoryComponent::USpellInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	for (int i = 0; i < MAX_NUM_SPELLS; i++)
	{
		heldSpells[i] = nullptr;
	}

	// ...
}


// Called when the game starts
void USpellInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpellInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpellInventoryComponent::TryAddSpell(AItemSpell* spellToAdd)
{
	if (spellToAdd)
	{
		for (int i = 0; i < MAX_NUM_SPELLS; i++)
		{
			if (heldSpells[i] == nullptr)
			{
				heldSpells[i] = spellToAdd;
				spellToAdd->OnRolled();
				return;
			}
		}
	}
}

