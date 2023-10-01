// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSpellObject.h"
#include "MagicMissilePlusObject.generated.h"

/**
 * 
 */
UCLASS()
class WHIMSICALWIZARDRY_API AMagicMissilePlusObject : public AItemSpellObject
{
	GENERATED_BODY()
	
public:

	AMagicMissilePlusObject();

	virtual void Tick(float DeltaTime) override;

	virtual void OnLifetimeEnd() override;

	virtual void OnReflected() override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Replicated)
	class UNiagaraComponent* missileVisual;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* missileCollision;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* missileMovement;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector velocity;

	bool bHasExploded;

public:

	void SetVelocity(FVector inVelocity);
};
