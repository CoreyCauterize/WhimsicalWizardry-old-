// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellInventoryComponent.h"
#include "ItemSpell.h"
#include "ItemSpells/Spell/Fireball.h"
#include "ItemSpells/Spell/MagicMissilePlus.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
USpellInventoryComponent::USpellInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	for (int i = 0; i < MAX_NUM_SPELLS; i++)
	{
		heldSpells.Add(nullptr);
	}

	

	//TEMP (Rolling functionality to be moved to a static struct or something):
	m_ListOfAllSpells.Add(AFireball::StaticClass());
	m_ListOfAllSpells.Add(AMagicMissilePlus::StaticClass());

	
	// ..
}


// Called when the game starts
void USpellInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	SetIsReplicated(true);

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
		if (GetOwner()->GetLocalRole() == ROLE_Authority)
		{
			Server_AddSpell(spellToAdd);
		}
	}
	else
	{
		RollSpell();

		//for (int i = 0; i < MAX_NUM_SPELLS; i++)
		//{
		//	if (heldSpells[i] == nullptr)
		//	{
		//		heldSpells[i] = rolledSpell;
		//		rolledSpell->OnRolled();
		//		return;
		//	}
		//}
	}
}

void USpellInventoryComponent::CycleSpells()
{
	for (int i = 0; i < heldSpells.Num(); i++)
	{
		heldSpells[i] = nullptr;

		if (i != heldSpells.Num() - 1)
		{
			heldSpells[i] = heldSpells[i + 1];
		}
	}
}

void USpellInventoryComponent::Server_SpawnSpell_Implementation(UClass* rolledSpell)
{
	FActorSpawnParameters params;
	params.Owner = GetOwner();
	
	AItemSpell* spawned = Cast<AItemSpell>(GetWorld()->SpawnActor(rolledSpell));
	for (int i = 0; i < MAX_NUM_SPELLS; i++)
	{
		if (heldSpells[i] == nullptr)
		{
			heldSpells[i] = spawned;
			spawned->OnRolled();
			return;
		}
	}
}

void USpellInventoryComponent::Server_AddSpell_Implementation(AItemSpell* spellToAdd)
{
	for (int i = 0; i < MAX_NUM_SPELLS; i++)
	{
		if (heldSpells[i] == nullptr)
		{
			if (GetOwner()->GetLocalRole() == ROLE_Authority)
			{
				heldSpells[i] = spellToAdd;
				spellToAdd->OnRolled();
			}
			return;
		}
	}
	
}

void USpellInventoryComponent::RollSpell()
{
	if (m_ListOfAllSpells.Num() > 0)
	{
		int spellNum = FMath::RandRange(0, m_ListOfAllSpells.Num() - 1);

		//AItemSpell* rolledSpell = Cast<AItemSpell>(GetWorld()->SpawnActor(m_ListOfAllSpells[spellNum]));
		Server_SpawnSpell(m_ListOfAllSpells[spellNum]);

	}

}

void  USpellInventoryComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USpellInventoryComponent, heldSpells);
}
