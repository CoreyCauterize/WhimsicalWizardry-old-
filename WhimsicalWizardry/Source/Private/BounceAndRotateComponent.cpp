// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceAndRotateComponent.h"

// Sets default values for this component's properties
UBounceAndRotateComponent::UBounceAndRotateComponent() : elapsedTime(0.0f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBounceAndRotateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBounceAndRotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector deltaPosition = FVector(0, 0, FMath::Sin(elapsedTime) * 0.333);

	deltaRotation = FRotator(0, DeltaTime * 50, 0);

	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + deltaPosition);

	GetOwner()->AddActorWorldRotation(deltaRotation);


	elapsedTime += DeltaTime;


	// ...
}

