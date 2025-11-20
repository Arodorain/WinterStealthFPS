// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Canvas.h"
#include "GameFramework/HUD.h"
#include "GUI/GameMenuWidget.h"
#include "GUI/SlateExample/SMainMenuWidget.h"
#include "GUI/SlateExample/SGameOverWidget.h"
#include "GUI/SlateExample/SSettingsWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */

UCLASS()
class WINTERSTEALTHFPS_API AGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly)
    UTexture2D* CrosshairTexture;

public:
    // Add 'void' here
    virtual void BeginPlay() override;

    // 1. HUD method of making UI
    virtual void DrawHUD() override;

    // 2 Saltes method of making UI
    TSharedPtr<class SSettingsWidget> SettingsWidget;
    TSharedPtr<class SWidget> SettingsWidgetContainer;

    void ShowSettingsMenu();
    void HideSettingsMenu();

    // --- Main Menu ---
    TSharedPtr<class SMainMenuWidget> MainMenuWidget;
    TSharedPtr<class SWidget> MainMenuWidgetContainer;

    void ShowMainMenu();
    void HideMainMenu();

    // --- Game Over ---
    TSharedPtr<class SGameOverWidget> GameOverWidget;
    TSharedPtr<class SWidget> GameOverWidgetContainer;

    void ShowGameOver();
    void HideGameOver();

    // 3. UMG method of making UI
    UPROPERTY(EditAnywhere)
    TSubclassOf<UGameMenuWidget> StartingGameWidget;
    UGameMenuWidget* GameMenuWidgetContainer;

    void SpawnGameMenu(TSubclassOf<UGameMenuWidget> NewGameMenuWidget);
};
