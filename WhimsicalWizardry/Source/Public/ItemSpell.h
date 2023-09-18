// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpell.generated.h"

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
	float backfireChance;
	

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnFire();

	virtual void OnBackfire();

	virtual void OnRolled();

	

};
