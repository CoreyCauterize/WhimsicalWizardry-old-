// Fill out your copyright notice in the Description page of Project Settings.


#include "KillPlaneComponent.h"
#include "PlayerKnockedOffComponent.h"
#include "Public/WhimsicalWizardryGameModeBase.h"
#include "Public/WimsicalWizardryGameStateBase.h"
#include "Public/WimsicalWizardryPlayerState.h"

// Sets default values for this component's properties
UKillPlaneComponent::UKillPlaneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKillPlaneComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UKillPlaneComponent::OnOverlapBegin);

	// ...
	
}


// Called every frame
void UKillPlaneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UKillPlaneComponent::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor)
	{

		AWhimsicalWizardryGameModeBase* gameMode = Cast<AWhimsicalWizardryGameModeBase>(GetWorld()->GetAuthGameMode());

		AWimsicalWizardryGameStateBase* gameState = gameMode->GetGameState<AWimsicalWizardryGameStateBase>();


		//Add Logic here
		//AWimsicalWizardryPlayerState* playerState = Cast<AWimsicalWizardryPlayerState>(gameState->PlayerArray[0]);

		UPlayerKnockedOffComponent* knockedOffComp = OtherActor->GetComponentByClass<UPlayerKnockedOffComponent>();

		if (knockedOffComp)
		{
			knockedOffComp->OnKnockedOff();
		}

	}

	
}