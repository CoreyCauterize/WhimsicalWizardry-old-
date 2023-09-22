// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpells/SpellObject/FireballObject.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Wizard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"



AFireballObject::AFireballObject()
{
	PrimaryActorTick.bCanEverTick = true;

	isReflectable = true;
	lifetime = 6.0f; //Could make this a const in the header
	hitForceScale = 300.0f;
	needsToCallOnLifetimeEnd = true;

	fireballCollision = CreateDefaultSubobject<UBoxComponent>("Fireball Collision");
	SetRootComponent(fireballCollision);
	
	fireballCollision->SetBoxExtent(FVector(24, 24, 24)); //Todo: Make this a const in FireballObject header and adjust it to be the right size
	
	if (GetLocalRole() == ROLE_Authority)
	{
		fireballCollision->OnComponentBeginOverlap.AddDynamic(this, &AFireballObject::OnOverlapBegin);
	}

	fireballVisual = CreateDefaultSubobject<UNiagaraComponent>("Fireball Visual");
	fireballVisual->SetupAttachment(RootComponent);
	fireballVisual->SetRelativeLocation(FVector(-40, 0, 0));
	auto NSauto = ConstructorHelpers::FObjectFinder<UNiagaraSystem>(TEXT("/Game/Assets/NiagraSystems/Fireball/Fireball_NS.Fireball_NS"));
	if (NSauto.Succeeded())
	{
		UNiagaraSystem* NS = Cast<UNiagaraSystem>(NSauto.Object);
		fireballVisual->SetAsset(NS);
	}
	else
	{
		throw("NSauto was null");
	}
	
	FQuat rot(0, 180, 0, 0);
	fireballCollision->SetRelativeRotation(rot);
}

void AFireballObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFireballObject::OnLifetimeEnd()
{
	Destroy();
}

void AFireballObject::OnReflected()
{
}

void AFireballObject::BeginPlay()
{
	Super::BeginPlay();
}


void AFireballObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWizard* HitWizard = Cast<AWizard>(OtherActor);

	if (HitWizard)
	{
		//Get projectile movement velocity
		//normalize said velocity
		//Make new vector with x and y from velocity, but custom z to launch up
		//multiply velocity by hitForceScale

		//Temp:
		FVector LaunchVector = FVector(1, 1, 2);

		HitWizard->LaunchCharacter(LaunchVector * hitForceScale, false, false);
		
	}
	else
	{

	}

	Destroy();
}

void  AFireballObject::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFireballObject, fireballVisual);
}
