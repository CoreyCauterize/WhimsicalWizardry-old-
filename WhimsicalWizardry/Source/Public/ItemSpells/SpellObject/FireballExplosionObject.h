// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSpellObject.h"
#include "FireballExplosionObject.generated.h"


/**
 * 
 */
UCLASS()
class WHIMSICALWIZARDRY_API AFireballExplosionObject : public AItemSpellObject
{
	GENERATED_BODY()

public:

	AFireballExplosionObject();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Replicated)
	class UNiagaraComponent* fireballExplosionVisual;

	UPROPERTY(EditAnywhere, Replicated)
	class USphereComponent* fireballExplosionCollision;

	FTimerHandle despawnHandle;

	
};
