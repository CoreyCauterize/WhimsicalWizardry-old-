// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSpawner.h"
#include "PickupBox.h"
#include "Pooling/ActorPool.h"
#include "Pooling/PoolableActor.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UPickupSpawner::UPickupSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PickupPool = CreateDefaultSubobject<UActorPool>(TEXT("Pickup Pool"));
	PickupPool->SetPoolableActorClass(PickupBox);
	PickupPool->SetSizeOfPool(SpawnAmount);
	PickupPool->SetPooledActorsHaveOutOfPoolLifespan(false);
	PickupPool->SetPooledActorsShouldCollide(true);
	PickupPool->SetPooledActorsShouldTick(true);
	
	//PickupBox = CreateDefaultSubobject<APickupBox>(TEXT("Pickup Box"));
	// ...
}


// Called when the game starts
void UPickupSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnPickups();
	// ...
	
}

void UPickupSpawner::Server_SpawnPickups_Implementation(FVector SpawnLocation)
{
	APickupBox* box = Cast<APickupBox>(PickupPool->ActivateASpawnedActor());
	box->TeleportTo(SpawnLocation, FRotator::ZeroRotator);

	/*UWorld* coolWorld = GetWorld();
	APickupBox* tempBox =Cast<APickupBox>( coolWorld->SpawnActor(PickupBox, &SpawnLocation, &FRotator::ZeroRotator));*/

	//tempBox->SetOwnerSpawner(this);
}

//void UPickupSpawner::Server_DelaySpawn_Implementation()
//{
//		FTimerHandle timer;
//		GetWorld()->GetTimerManager().SetTimer(timer, this, &UPickupSpawner::SpawnPickups, FMath::RandRange(10,30), false);
//	
//}

void UPickupSpawner::SpawnPickups()
{
	FVector chosenLoc = CalcSpawnCoords() + GetOwner()->GetActorLocation();
	UWorld* coolWorld = GetWorld();
	TArray<FHitResult> OutHits;
	// Come here if things start spawning on the roof, should we have one
	FVector Start = chosenLoc + FVector(0, 0, 1000);
	FVector End = chosenLoc - FVector(0, 0, 1000);

	coolWorld->LineTraceMultiByChannel(OutHits, Start, End, ECollisionChannel::ECC_WorldStatic);
	float closest = 2000;
	for (int i = 0; i < OutHits.Num(); i++)
	{
		float distance = FVector::Dist(chosenLoc, OutHits[i].Location);
		if (distance < closest)
		{
			closest = distance;
			chosenLoc = OutHits[i].Location;
		}
	}
	Server_SpawnPickups(chosenLoc + FVector(0,0,90));
	
	
}

FVector UPickupSpawner::CalcSpawnCoords()
{
	float r = SpawnRadius * sqrt(rand());
	float theta = 2 * PI * rand();

	float x = r * cos(theta);
	float z = r * sin(theta);

	return FVector(x, z, 0);
}


// Called every frame
void UPickupSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

