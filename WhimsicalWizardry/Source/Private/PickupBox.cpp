// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBox.h"
#include "PickupSpawner.h"
#include "Pooling/ActorPool.h"
#include "Pooling/PoolableActor.h"
#include "SpellInventoryComponent.h"

// Sets default values
APickupBox::APickupBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pickupHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Pickup Hitbox"));
	RootComponent = pickupHitbox;
	pickupHitbox->SetSimulatePhysics(false);

	pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	pickupMesh->SetupAttachment(pickupHitbox);

	if(GetLocalRole() == ROLE_Authority)
	pickupHitbox->OnComponentBeginOverlap.AddDynamic(this, &APickupBox::OnOverlapBegin);

	bReplicates = true;
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
		return; 

	// Calls spell inventory component on the wizard
	USpellInventoryComponent* tempInv;
	tempInv = Cast<USpellInventoryComponent>(wizard->GetComponentByClass(USpellInventoryComponent::StaticClass())); 
	tempInv->TryAddSpell(); 
	UPickupSpawner* outerSpawner = Cast<UPickupSpawner>(GetSpawningActorPool()->GetOuter()); 
	outerSpawner->Server_DelaySpawn(); 
	FTimerHandle deactivateTimer; 
	GetWorld()->GetTimerManager().SetTimer(deactivateTimer, this, &APickupBox::Deactivate, 0.1f, false); 
}

/*void APickupBox::Obliterate()
{
	Destroy();
}*/

//void APickupBox::SetOwnerSpawner(UPickupSpawner* newSpawner)
//{
//	ownerSpawner = newSpawner;
//}

// Called every frame
void APickupBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

//void APickupBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//	DOREPLIFETIME(APickupBox, ownerSpawner);
//}