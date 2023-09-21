// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSpell.h"
#include "Fireball.generated.h"

/**
 * 
 */
UCLASS()
class WHIMSICALWIZARDRY_API AFireball : public AItemSpell
{
	GENERATED_BODY()

public:

	AFireball();

	virtual void OnFire(USpellInventoryComponent* belongingInventory) override;

protected:


	
};
