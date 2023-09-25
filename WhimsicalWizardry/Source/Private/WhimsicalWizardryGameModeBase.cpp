// Copyright Epic Games, Inc. All Rights Reserved.


#include "WhimsicalWizardryGameModeBase.h"
#include "GameFramework/Pawn.h"

AWhimsicalWizardryGameModeBase::AWhimsicalWizardryGameModeBase()
{
}

void AWhimsicalWizardryGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	APawn* NewPawn = NewPlayer->GetPawn();

	if (NewPawn)
	{
		NewPawn->GetController()
	}
}

void AWhimsicalWizardryGameModeBase::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
}

void AWhimsicalWizardryGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    Super::HandleStartingNewPlayer_Implementation(NewPlayer);


}
