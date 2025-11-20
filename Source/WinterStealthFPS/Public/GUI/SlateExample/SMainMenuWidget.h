// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/GameHUD.h"
#include "Widgets/SCompoundWidget.h"

class AGameHUD;

/**
 * Simple Main Menu Widget
 */
class WINTERSTEALTHFPS_API SMainMenuWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SMainMenuWidget) {}
        SLATE_ARGUMENT(TWeakObjectPtr<AGameHUD>, OwningHUD)
    SLATE_END_ARGS()

    /** Owning HUD pointer */
    TWeakObjectPtr<AGameHUD> OwningHUD;

    /** Constructs this widget with InArgs */
    void Construct(const FArguments& InArgs);

    /** Button callbacks */
    FReply OnStartClicked();
    FReply OnQuitClicked();
};
