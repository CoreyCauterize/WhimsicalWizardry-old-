// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBox.h"
#include "SpellInventoryComponent.h"

// Sets default values
APickupBox::APickupBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pickupHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Pickup Hitbox"));
	pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	RootComponent = pickupHitbox;
	pickupMesh->SetupAttachment(pickupHitbox);

	pickupHitbox->SetSimulatePhysics(false);
	pickupHitbox->OnComponentBeginOverlap.AddDynamic(this, &APickupBox::OnOverlapBegin);


	SetReplicates(true);

}

// Called when the game starts or when spawned
void APickupBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* wizard = Cast<ACharacter>(OtherActor);
	if (wizard == nullptr)
	{
		return;
	}
	USpellInventoryComponent* tempInv;
	// Put Riley's method here when it is done, but for now I will disappear!
	tempInv = Cast <USpellInventoryComponent>(wizard->GetComponentByClass(USpellInventoryComponent::StaticClass()));
	tempInv->TryAddSpell();
	SetActorHiddenInGame(true);
	
}

// Called every frame
void APickupBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APickupBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}