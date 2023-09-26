// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "Wizard.h"
#include "Components/SceneComponent.h"
#include "PickupSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WHIMSICALWIZARDRY_API UPickupSpawner : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupSpawner();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Server, Reliable)
		void Server_DelaySpawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned Object")
		TSubclassOf<class APickupBox> PickupBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Properties")
		float SpawnHeight;

	//This one is temporary until the pooling is implemented fully
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Properties")
		int SpawnAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Properties")
		float SpawnRadius;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Spawner Functions")
		void Server_SpawnPickups(FVector SpawnLocation);

	void SpawnPickups();

	FVector CalcSpawnCoords();

	class UActorPool* PickupPool = nullptr;
};
