// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpellObject.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"
#include "Wizard.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AItemSpellObject::AItemSpellObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Network stuff
	bReplicates = true;
	SetReplicateMovement(true);

}

// Called when the game starts or when spawned
void AItemSpellObject::BeginPlay()
{
	Super::BeginPlay();
	
	if (needsToCallOnLifetimeEnd && GetLocalRole() == ROLE_Authority)
	{
		GetWorld()->GetTimerManager().SetTimer(LifetimeEndTimerHandle, this, &AItemSpellObject::OnLifetimeEnd, lifetime);
	}
}

// Called every frame
void AItemSpellObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpellObject::OnLifetimeEnd()
{
}

void AItemSpellObject::OnReflected()
{
}

void AItemSpellObject::NMC_LaunchHitWizard_Implementation(AWizard* hitWizard, FVector launchVelocity)
{
	hitWizard->LaunchCharacter(launchVelocity * hitForceScale, false, false);
}

void AItemSpellObject::LaunchHitWizard(AWizard* hitWizard, FVector launchVelocity)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		NMC_LaunchHitWizard(hitWizard, launchVelocity);
	}
}

void AItemSpellObject::NMC_ImpulseCMC_Implementation(FVector impulse, UCharacterMovementComponent* CMC)
{
	CMC->AddImpulse(impulse * hitForceScale, false);
}

void AItemSpellObject::ImpulseCMC(FVector impulse, UCharacterMovementComponent* CMC)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		NMC_ImpulseCMC(impulse, CMC);
	}
}

void  AItemSpellObject::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AItemSpellObject, hitForceScale);
}
