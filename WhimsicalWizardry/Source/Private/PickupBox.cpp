// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBox.h"

// Sets default values
APickupBox::APickupBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pickupHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Pickup Hitbox"));
	pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	RootComponent = pickupHitbox;
	pickupHitbox->SetupAttachment(pickupMesh);

	pickupHitbox->SetSimulatePhysics(false);
	pickupHitbox->OnComponentBeginOverlap.AddDynamic(this, &APickupBox::OnOverlapBegin);

}

// Called when the game starts or when spawned
void APickupBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Make this dissappear when overlapping with players
}

// Called every frame
void APickupBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

