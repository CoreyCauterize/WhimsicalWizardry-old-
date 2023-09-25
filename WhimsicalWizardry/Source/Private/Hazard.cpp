#include "Hazard.h"

AHazard::AHazard()
{
	PrimaryActorTick.bCanEverTick = true;

	HazardHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hazard Hitbox"));
	HazardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hazard Mesh"));
	RootComponent = HazardHitbox;
	HazardMesh->SetupAttachment(HazardHitbox);

	HazardHitbox->SetSimulatePhysics(false);
	HazardHitbox->OnComponentBeginOverlap.AddDynamic(this, &AHazard::OnOverlapBegin);


	SetReplicates(true);
}

void AHazard::BeginPlay()
{
	Super::BeginPlay();
}

void AHazard::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Detects when a playertouches the hazard
	ACharacter* wizard = Cast<ACharacter>(OtherActor);
	if (wizard == nullptr)
	{
		return;
	}
	//Launches the player after being hit in the opposite direction
	wizard->LaunchCharacter(FVector(wizard->GetActorForwardVector().X * -LaunchScale, wizard->GetActorForwardVector().Y * -LaunchScale, 2 * LaunchScale), true, false);

	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player Launched!")); <-debug if needed
}

void AHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
