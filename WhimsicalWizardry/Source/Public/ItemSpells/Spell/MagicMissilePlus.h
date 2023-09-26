// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSpell.h"
#include "MagicMissilePlus.generated.h"

/**
 * 
 */
UCLASS()
class WHIMSICALWIZARDRY_API AMagicMissilePlus : public AItemSpell
{
	GENERATED_BODY()

public:
	AMagicMissilePlus();

	//UFUNCTION(Server, Reliable)
	void Server_OnFire_Implementation(USpellInventoryComponent* belongingInventory) override;
	//virtual void Server_OnFire(USpellInventoryComponent* belongingInventory) override;

	virtual void OnFire(USpellInventoryComponent* belongingInventory) override;
	
};
