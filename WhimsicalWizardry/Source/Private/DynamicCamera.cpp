// Fill out your copyright notice in the Description page of Project Settings.

#include "DynamicCamera.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

ADynamicCamera::ADynamicCamera()
{
	CameraSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Focal Point"));
	CameraSphere->InitSphereRadius(42.0f);
	CameraSphere->SetupAttachment(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(CameraSphere);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	DynamicCamera = GetCameraComponent();
	//DynamicCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DynamicCamera"));
	//DynamicCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//DynamicCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GetCameraComponent()->AttachToComponent(DynamicCamera, FAttachmentTransformRules::KeepRelativeTransform);
}

void ADynamicCamera::BeginPlay()
{
	Super::BeginPlay();
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Cast<APlayerController>(&Iterator);
		
		FVector Loc = DynamicCamera->GetRelativeLocation();
		FActorSpawnParameters SpawnInfo;

		//GetWorld()->SpawnActor<ADynamicCamera>(Loc, FRotator(0, 0 ,0), SpawnInfo);
	}
}

FVector ADynamicCamera::FindAverageLocation()
{
	return FVector(0, 0, 0);
}
