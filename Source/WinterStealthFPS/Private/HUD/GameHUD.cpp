// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameHUD.h"
#include "Widgets/SWeakWidget.h"
#include "Kismet/GameplayStatics.h"

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();

    ShowGameOver();

    //ShowMainMenu();

    // 2. Slates method of making UI
    //ShowSettingsMenu();

    // 3. UMG method of making UI
    SpawnGameMenu(StartingGameWidget);
}

void AGameHUD::DrawHUD()
{
    Super::DrawHUD();

    if (!CrosshairTexture) return;

    // Canvas Dimensions
    float CanvasWidth = Canvas->ClipX;
    float CanvasHeight = Canvas->ClipY;
    FVector2D CanvasCenter(CanvasWidth * 0.5, CanvasHeight * 0.5f);

    // Crosshair dimension
    float CrosshairWidth = CrosshairTexture->GetSurfaceWidth();
    float CrosshairHeight = CrosshairTexture->GetSurfaceHeight();
    float CrosshairScale = 5.0f;
    FVector2D CrosshairHalfSize(CrosshairWidth * 0.5f, CrosshairHeight * 0.5f);

    FVector2D CrosshairDrawPosition(CanvasCenter.X - CrosshairHalfSize.X, CanvasCenter.Y - CrosshairHalfSize.Y);
    FVector2D CrosshairSize(CrosshairWidth * CrosshairScale, CrosshairHeight * CrosshairScale);

    // Draw the crosshair
    FCanvasTileItem CrosshairItem(CrosshairDrawPosition, CrosshairTexture->GetResource(), FLinearColor::White);
    CrosshairItem.BlendMode = SE_BLEND_Translucent;
    Canvas->DrawItem(CrosshairItem);

}
// --- Settings/Pause ---
void AGameHUD::ShowSettingsMenu()
{
    if (!SettingsWidget.IsValid())
    {
        SettingsWidget = SNew(SSettingsWidget).OwningHUD(this).MyInt(221);
    }

    if (!SettingsWidgetContainer.IsValid())
    {
        SettingsWidgetContainer =
            SNew(SWeakWidget)
            .PossiblyNullContent(SettingsWidget.ToSharedRef());

        GEngine->GameViewport->AddViewportWidgetContent(SettingsWidgetContainer.ToSharedRef());
    }

    PlayerOwner->bShowMouseCursor = true;
    PlayerOwner->SetInputMode(FInputModeUIOnly());

    // Hide HUD UI
    if (GameMenuWidgetContainer)
    {
        GameMenuWidgetContainer->SetVisibility(ESlateVisibility::Hidden);
    }

    // Pause Game
    UGameplayStatics::SetGamePaused(GetWorld(), true);
}


void AGameHUD::HideSettingsMenu()
{
    if (SettingsWidgetContainer.IsValid())
    {
        GEngine->GameViewport->RemoveViewportWidgetContent(SettingsWidgetContainer.ToSharedRef());
        SettingsWidgetContainer.Reset();
    }

    SettingsWidget.Reset();

    PlayerOwner->bShowMouseCursor = false;
    PlayerOwner->SetInputMode(FInputModeGameOnly());

    // Show HUD UI
    if (GameMenuWidgetContainer)
    {
        GameMenuWidgetContainer->SetVisibility(ESlateVisibility::Visible);
    }

    // Unpause Game
    UGameplayStatics::SetGamePaused(GetWorld(), false);
}

// --- Main Menu ---
void AGameHUD::ShowMainMenu()
{
    if (!MainMenuWidget.IsValid())
    {
        MainMenuWidget = SNew(SMainMenuWidget)
            .OwningHUD(this);
    }

    if (!MainMenuWidgetContainer.IsValid())
    {
        MainMenuWidgetContainer =
            SNew(SWeakWidget)
            .PossiblyNullContent(MainMenuWidget.ToSharedRef());

        GEngine->GameViewport->AddViewportWidgetContent(MainMenuWidgetContainer.ToSharedRef());
    }

    PlayerOwner->bShowMouseCursor = true;
    PlayerOwner->SetInputMode(FInputModeUIOnly());

    if (GameMenuWidgetContainer)
    {
        GameMenuWidgetContainer->SetVisibility(ESlateVisibility::Hidden);
    }

    // Pause Game
    UGameplayStatics::SetGamePaused(GetWorld(), true);
}


void AGameHUD::HideMainMenu()
{
    if (MainMenuWidgetContainer.IsValid())
    {
        GEngine->GameViewport->RemoveViewportWidgetContent(MainMenuWidgetContainer.ToSharedRef());
        MainMenuWidgetContainer.Reset();
    }

    MainMenuWidget.Reset();

    PlayerOwner->bShowMouseCursor = false;
    PlayerOwner->SetInputMode(FInputModeGameOnly());

    // Show UMG HUD if visible
    if (GameMenuWidgetContainer)
    {
        GameMenuWidgetContainer->SetVisibility(ESlateVisibility::Visible);
    }

    // Unpause game
    UGameplayStatics::SetGamePaused(GetWorld(), false);
}

// --- Game Over ---
void AGameHUD::ShowGameOver()
{
    if (!GameOverWidget.IsValid())
    {
        GameOverWidget = SNew(SGameOverWidget).OwningHUD(this);
    }

    if (!GameOverWidgetContainer.IsValid())
    {
        GameOverWidgetContainer =
            SNew(SWeakWidget)
            .PossiblyNullContent(GameOverWidget.ToSharedRef());

        GEngine->GameViewport->AddViewportWidgetContent(GameOverWidgetContainer.ToSharedRef());
    }

    PlayerOwner->bShowMouseCursor = true;
    PlayerOwner->SetInputMode(FInputModeUIOnly());

    if (GameMenuWidgetContainer)
    {
        GameMenuWidgetContainer->SetVisibility(ESlateVisibility::Hidden);
    }

    UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AGameHUD::HideGameOver()
{
    if (GameOverWidgetContainer.IsValid())
    {
        GEngine->GameViewport->RemoveViewportWidgetContent(GameOverWidgetContainer.ToSharedRef());
        GameOverWidgetContainer.Reset();
    }

    GameOverWidget.Reset();

    PlayerOwner->bShowMouseCursor = false;
    PlayerOwner->SetInputMode(FInputModeGameOnly());

    if (GameMenuWidgetContainer)
    {
        GameMenuWidgetContainer->SetVisibility(ESlateVisibility::Visible);
    }

    UGameplayStatics::SetGamePaused(GetWorld(), false);
}

// --- Game Menu ---
void AGameHUD::SpawnGameMenu(TSubclassOf<UGameMenuWidget> NewGameMenuWidget)
{
    if (GameMenuWidgetContainer) {
        GameMenuWidgetContainer->RemoveFromParent();
        GameMenuWidgetContainer = nullptr;
    }

    GameMenuWidgetContainer = CreateWidget<UGameMenuWidget>(GetWorld(), NewGameMenuWidget);
    GameMenuWidgetContainer->AddToViewport();
}
