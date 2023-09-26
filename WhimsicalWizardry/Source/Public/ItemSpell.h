// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpell.generated.h"

class USpellInventoryComponent;

UCLASS(abstract)
class WHIMSICALWIZARDRY_API AItemSpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	bool removeFromInventoryOnFired;	

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
	virtual void Server_OnFire(USpellInventoryComponent* belongingInventory);

	virtual void OnFire(USpellInventoryComponent* belongingInventory);



	virtual void OnRolled();

	

};
