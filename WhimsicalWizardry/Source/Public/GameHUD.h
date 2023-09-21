// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class WHIMSICALWIZARDRY_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AGameHUD();

	UPROPERTY(EditAnywhere, Category = "Game Hud")
	TSubclassOf<class UUserWidget> m_playerGuiClass;

	UPROPERTY()
	class UUserWidget* m_playerGui;

protected:

	virtual void BeginPlay() override;
};
