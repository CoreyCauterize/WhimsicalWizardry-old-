// Fill out your copyright notice in the Description page of Project Settings.
/*
Pickup Code Written by: Owen Burgess
Code for the powerups and pickups 
*/

#pragma once

#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "PickupBox.generated.h"


UCLASS()
class WHIMSICALWIZARDRY_API APickupBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBox();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	UStaticMeshComponent* pickupMesh;
	//Set These to replicated when implementing networking, they don't like not having the other function and I don't want to do it
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	UCapsuleComponent* pickupHitbox;
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
