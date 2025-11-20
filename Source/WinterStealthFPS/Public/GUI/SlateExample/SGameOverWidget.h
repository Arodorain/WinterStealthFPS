#pragma once

#include "CoreMinimal.h"
#include "HUD/GameHUD.h"
#include "Widgets/SCompoundWidget.h"

class AGameHUD;

class WINTERSTEALTHFPS_API SGameOverWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SGameOverWidget) {}
        SLATE_ARGUMENT(TWeakObjectPtr<AGameHUD>, OwningHUD)
    SLATE_END_ARGS()

    TWeakObjectPtr<AGameHUD> OwningHUD;

    void Construct(const FArguments& InArgs);

    FReply OnRetryClicked();
    FReply OnQuitClicked();
};
