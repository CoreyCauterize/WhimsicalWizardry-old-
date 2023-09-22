// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSpellObject.h"
#include "FireballObject.generated.h"

/**
 * 
 */
UCLASS()
class WHIMSICALWIZARDRY_API AFireballObject : public AItemSpellObject
{
	GENERATED_BODY()

public:

	AFireballObject();

	virtual void Tick(float DeltaTime) override;

	virtual void OnLifetimeEnd() override;

	virtual void OnReflected() override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Replicated)
	class UNiagaraComponent* fireballVisual;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* fireballCollision;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector velocity;

public:

	void SetVelocity(FVector inVelocity) { velocity = inVelocity; }


};
