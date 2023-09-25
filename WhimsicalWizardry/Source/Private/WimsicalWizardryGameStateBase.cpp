// Fill out your copyright notice in the Description page of Project Settings.


#include "WimsicalWizardryGameStateBase.h"
#include "WimsicalWizardryPlayerState.h"
#include "Net/UnrealNetwork.h"

bool AWimsicalWizardryGameStateBase::lastPlayerStanding()
{
	AWimsicalWizardryPlayerState* wWPlayerState;
	bool lastStanding = true;
	int numPlayersAlive = 0;
	//If only one player standing that player wins. if not no one has yet
	for (int i = 0; i < PlayerArray.Num(); i++)
	{
		wWPlayerState = Cast<AWimsicalWizardryPlayerState>(PlayerArray[i]);
		if (wWPlayerState->getLives() > 0)
		{
			numPlayersAlive++;
		}
	}

	if (numPlayersAlive > 1)
	{
		lastStanding = false;
	}

	return lastStanding;
}

void AWimsicalWizardryGameStateBase::score()
{
	AWimsicalWizardryPlayerState* wWPlayerState;
	wWPlayerState = Cast<AWimsicalWizardryPlayerState>(PlayerArray[0]);
	if (wWPlayerState->getLives() != 0)
	{
		m_player0Score++;
	}
	else
	{
		m_player1Score++;
	}
}

void AWimsicalWizardryGameStateBase::resetGame()
{
	AWimsicalWizardryPlayerState* wWPlayerState;
	for (int i = 0; i < PlayerArray.Num(); i++)
	{
		wWPlayerState = Cast<AWimsicalWizardryPlayerState>(PlayerArray[i]);
		wWPlayerState->setLives(3);
	}
}

int AWimsicalWizardryGameStateBase::GetPlayer0Score()
{
	return m_player0Score;
}

int AWimsicalWizardryGameStateBase::GetPlayer1Score()
{
	return m_player1Score;
}

void AWimsicalWizardryGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWimsicalWizardryGameStateBase, m_player0Score);
	DOREPLIFETIME(AWimsicalWizardryGameStateBase, m_player1Score);
}
