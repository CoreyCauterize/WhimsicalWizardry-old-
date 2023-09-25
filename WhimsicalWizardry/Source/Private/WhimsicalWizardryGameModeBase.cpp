// Copyright Epic Games, Inc. All Rights Reserved.


#include "WhimsicalWizardryGameModeBase.h"

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


}
