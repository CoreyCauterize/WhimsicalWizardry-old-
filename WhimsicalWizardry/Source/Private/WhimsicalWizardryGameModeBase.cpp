// Copyright Epic Games, Inc. All Rights Reserved.


#include "WhimsicalWizardryGameModeBase.h"
#include "GameFramework/Pawn.h"


void AWhimsicalWizardryGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	APawn* NewPawn = NewPlayer->GetPawn();

	if (NewPawn)
	{
		NewPawn->GetController()
	}
}