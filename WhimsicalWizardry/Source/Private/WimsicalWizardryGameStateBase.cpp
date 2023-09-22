// Fill out your copyright notice in the Description page of Project Settings.


#include "WimsicalWizardryGameStateBase.h"
#include "WimsicalWizardryPlayerState.h"

bool AWimsicalWizardryGameStateBase::lastPlayerStanding()
{
	AWimsicalWizardryPlayerState* wWPlayerState;
	bool lastStanding = true;
	int numPlayersAlive = 0;
	//If only one player standing that player wins. if not no one has yet
	for (int i = 0; i < PlayerArray.Num(); i++)
	{
		wWPlayerState = Cast<AWimsicalWizardryPlayerState>(PlayerArray[i]);
		if (wWPlayerState->getLives())
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
	if (m_player0Score == 0)
	{
		m_player1Score++;
	}
	else if (m_player1Score == 0)
	{
		m_player0Score++;
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
