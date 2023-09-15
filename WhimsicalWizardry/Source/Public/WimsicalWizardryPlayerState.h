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
	
	int m_playerScore;

public:
	int GetPlayerScore();

};
