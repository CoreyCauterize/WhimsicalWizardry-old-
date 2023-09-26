// Fill out your copyright notice in the Description page of Project Settings.

#include "DynamicCamera.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Wizard.h"
#include "Net/UnrealNetwork.h"

ADynamicCamera::ADynamicCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Focal Point"));
	CameraSphere->InitSphereRadius(42.0f);
	CameraSphere->SetCollisionProfileName(FName("NoCollision"));
	SetRootComponent(CameraSphere);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(CameraSphere);
	CameraBoom->TargetArmLength = 1200.0f;
	CameraBoom->bIsCameraFixed = true;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	CameraBoom->ProbeChannel = ECollisionChannel::ECC_GameTraceChannel1;

	GetCameraComponent()->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
	SetReplicates(true);
	SetReplicateMovement(true);

	SetActorEnableCollision(false);
}

void ADynamicCamera::GetAllWizards()
{
	Server_GetAllWizards();
}

void ADynamicCamera::Server_GetAllWizards_Implementation()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWizard::StaticClass(), WizardList);

}

void ADynamicCamera::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &ADynamicCamera::GetAllWizards, 1.5f, false);
}

void ADynamicCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Average = FindAverageLocation();
	
	SetActorLocation(FMath::Lerp(GetActorLocation(), Average, DeltaTime));
}

FVector ADynamicCamera::FindAverageLocation()
{
	FVector Loc;

	for (int i = 0; i < WizardList.Num(); i++)
	{
		Loc += WizardList[i]->GetActorLocation();
	}

	if (WizardList.Num() > 0)
	{
		return Loc / WizardList.Num();
	}
	else
	{
		return FVector(0, 0, 0);
	}

}

void ADynamicCamera::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADynamicCamera, WizardList);
}