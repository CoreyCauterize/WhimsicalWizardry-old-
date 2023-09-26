// Fill out your copyright notice in the Description page of Project Settings.
/*
Pickup Code Written by: Owen Burgess
Code for the powerups and pickups 

Pooling implementation by: Derek Fallows
*/

#pragma once

#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "PickupBox.generated.h"


UCLASS()
class WHIMSICALWIZARDRY_API APickupBox : public APoolableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBox();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* pickupMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCapsuleComponent* pickupHitbox;

	//UPROPERTY(Replicated)
	//class UPickupSpawner* ownerSpawner;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//void Obliterate();

	
public:
	UFUNCTION()
	void SetOwnerSpawner(UPickupSpawner* newSpawner);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
