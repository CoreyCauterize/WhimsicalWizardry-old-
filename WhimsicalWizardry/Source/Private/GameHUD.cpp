// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AGameHUD::AGameHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> playerHud(TEXT("/Game/Blueprints/UI/BP_PlayerScores"));
    if (playerHud.Succeeded())
    {
        m_playerGuiClass = playerHud.Class;
    }
}

void AGameHUD::BeginPlay()
{

    m_playerGui = CreateWidget<UUserWidget>(GetGameInstance(), m_playerGuiClass);

    m_playerGui->AddToViewport();
}
