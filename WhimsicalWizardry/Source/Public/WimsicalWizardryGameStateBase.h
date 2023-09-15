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

	UFUNCTION(BlueprintCallable, Category = "Score")
		int GetPlayer0Score();

	UFUNCTION(BlueprintCallable, Category = "Score")
		int GetPlayer1Score();

private:
	
	int m_player0Score;
	int m_player1Score;
};
