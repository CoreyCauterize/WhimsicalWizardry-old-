// Fill out your copyright notice in the Description page of Project Settings.


#include "WimsicalWizardryGameStateBase.h"
#include "WimsicalWizardryPlayerState.h"
#include "Net/UnrealNetwork.h"

bool AWimsicalWizardryGameStateBase::lastPlayerStanding()
{
	AWimsicalWizardryPlayerState* wWPlayerState;
	int numTeam0Players = 0;
	int numTeam1Players = 0;

	//If only one player standing that player wins. if not no one has yet
	for (int i = 0; i < PlayerArray.Num(); i++)
	{
		wWPlayerState = Cast<AWimsicalWizardryPlayerState>(PlayerArray[i]);
		if (wWPlayerState->getLives() > 0)
		{
			if (wWPlayerState->getTeam() == 0)
			{
				numTeam0Players++;
			}
			else
			{
				numTeam1Players++;
			}
		}
	}

	if (numTeam0Players > 0 && numTeam1Players == 0)
	{
		m_teamThatWon = 0;
		return true;
	}
	else if (numTeam1Players > 0 && numTeam0Players == 0)
	{
		m_teamThatWon = 1;
		return true;
	}


	return false;
}

void AWimsicalWizardryGameStateBase::score()
{
	if (m_teamThatWon == 0)
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
