// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PickupComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WHIMSICALWIZARDRY_API UPickupComponent : public USceneComponent
{
	GENERATED_BODY()

	



public:	
	// Sets default values for this component's properties
	UPickupComponent();

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* pickupMesh;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
