// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerKnockedOffComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UPlayerKnockedOffComponent::UPlayerKnockedOffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerKnockedOffComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	RespawnLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UPlayerKnockedOffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerKnockedOffComponent::OnKnockedOff()
{
	GetOwner()->SetActorLocation(RespawnLocation);

	Cast<ACharacter>(GetOwner())->GetCharacterMovement()->StopMovementImmediately();
}

