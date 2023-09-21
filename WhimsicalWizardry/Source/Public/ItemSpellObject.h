// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpellObject.generated.h"

UCLASS(abstract)
class WHIMSICALWIZARDRY_API AItemSpellObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpellObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool isReflectable;
	float lifetime;
	float hitForceScale;
	bool needsToCallOnLifetimeEnd;

	FTimerHandle LifetimeEndTimerHandle;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnLifetimeEnd();

	virtual void OnReflected();

};
