// Fill out your copyright notice in the Description page of Project Settings.


#include "WimsicalWizardryPlayerState.h"

int AWimsicalWizardryPlayerState::getLives()
{
    return m_lives;
}

int AWimsicalWizardryPlayerState::getPlayerScore()
{
    return m_playerScore;
}

void AWimsicalWizardryPlayerState::setLives(int lives)
{
    m_lives = lives;
}

void AWimsicalWizardryPlayerState::setPlayerScore(int playerScore)
{
    m_playerScore = playerScore;
}

void AWimsicalWizardryPlayerState::increasePlayerScore()
{
    m_playerScore++;
}

void AWimsicalWizardryPlayerState::takePlayerLife()
{
    m_lives--;
}

