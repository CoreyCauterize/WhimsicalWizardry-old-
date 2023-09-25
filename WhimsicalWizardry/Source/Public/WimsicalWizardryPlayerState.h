// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WimsicalWizardryPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class WHIMSICALWIZARDRY_API AWimsicalWizardryPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	int getLives();
	int getPlayerScore();

	void setLives(int lives);
	void setPlayerScore(int playerScore);

	void increasePlayerScore();
	void takePlayerLife();

private:
	int m_lives = 3;
	int m_playerScore = 0;
};
