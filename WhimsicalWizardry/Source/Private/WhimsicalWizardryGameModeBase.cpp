// Copyright Epic Games, Inc. All Rights Reserved.


#include "WhimsicalWizardryGameModeBase.h"
#include "WimsicalWizardryGameStateBase.h"
#include "WimsicalWizardryPlayerState.h"
#include "GameFramework/Pawn.h"
#include "DynamicCamera.h"
#include "Camera/CameraComponent.h"


AWhimsicalWizardryGameModeBase::AWhimsicalWizardryGameModeBase()
{
}

void AWhimsicalWizardryGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AWhimsicalWizardryGameModeBase::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
}

void AWhimsicalWizardryGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	APawn* NewPawn = NewPlayer->GetPawn();
	setNewPlayersTeam(NewPawn);
	//NMC_SpawnPlayerCamera(NewPlayer);
	
}

void AWhimsicalWizardryGameModeBase::setNewPlayersTeam(APawn* pawn)
{
	AWimsicalWizardryPlayerState* newPlayerState = Cast<AWimsicalWizardryPlayerState>(pawn->GetPlayerState());
	if (newPlayerState != nullptr)
	{
		newPlayerState->setTeam(m_nextPlayersTeam);
		if (m_nextPlayersTeam == 0)
		{
			m_nextPlayersTeam = 1;
		}
		else if (m_nextPlayersTeam == 1)
		{
			m_nextPlayersTeam = 0;
		}
	}
}

void AWhimsicalWizardryGameModeBase::NMC_SpawnPlayerCamera_Implementation(APlayerController* NewPlayer)
{
	//GEt teh pawn
	APawn* NewPawn = NewPlayer->GetPawn();
	FVector pos;
	FRotator rot;
	if (NewPawn)
	{
		pos = NewPawn->GetActorLocation();
		rot = NewPawn->GetActorForwardVector().Rotation();
	}

	FVector cameraOffset = FVector(0, 0, 300) - (350 * NewPawn->GetActorForwardVector());
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = NewPlayer;
	
    ADynamicCamera* DynamicCamera = GetWorld()->SpawnActor<ADynamicCamera>(DynamicCameraClass, pos + cameraOffset ,rot);
	if (DynamicCamera)
	{
		FRotator direction = (pos - DynamicCamera->GetCameraComponent()->GetComponentLocation()).Rotation();
		//DynamicCamera->SetActorRotation(rot);
		DynamicCamera->SetOwner(NewPlayer);
		DynamicCamera->GetCameraComponent()->SetWorldRotation(direction);
		//DynamicCamera->GetDynamicCamera()->SetRelativeRotation(direction);
		NewPlayer->SetViewTargetWithBlend(DynamicCamera, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
	}
}