// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "WimsicalWizardryGameStateBase.generated.h"


/**
 * 
 */
UCLASS()
class WHIMSICALWIZARDRY_API AWimsicalWizardryGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	bool lastPlayerStanding();

	void score();

	void resetGame();

	UFUNCTION(BlueprintCallable, Category = "Score")
		int GetPlayer0Score();

	UFUNCTION(BlueprintCallable, Category = "Score")
		int GetPlayer1Score();

private:
	UPROPERTY(Replicated)
		int m_player0Score;
	UPROPERTY(Replicated)
		int m_player1Score;
	int m_teamThatWon;
};
