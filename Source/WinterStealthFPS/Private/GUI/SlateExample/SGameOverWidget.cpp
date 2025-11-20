#include "GUI/SlateExample/SGameOverWidget.h"
#include "SlateOptMacros.h"
#include "Kismet/GameplayStatics.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SGameOverWidget::Construct(const FArguments& InArgs)
{
    OwningHUD = InArgs._OwningHUD;

    const FMargin ContentPadding(800.f, 300.f);
    const FMargin ButtonPadding(10.f);

    FSlateFontInfo TitleFont = FCoreStyle::Get().GetFontStyle("EmbossedText");
    TitleFont.Size = 60;

    FSlateFontInfo ButtonFont = TitleFont;
    ButtonFont.Size = 40;

    ChildSlot
        [
            SNew(SOverlay)

                + SOverlay::Slot()
                .HAlign(HAlign_Fill)
                .VAlign(VAlign_Fill)
                [
                    SNew(SImage).ColorAndOpacity(FLinearColor::Black)
                ]

                + SOverlay::Slot()
                .HAlign(HAlign_Fill)
                .VAlign(VAlign_Fill)
                .Padding(ContentPadding)
                [
                    SNew(SVerticalBox)

                        + SVerticalBox::Slot()
                        .AutoHeight()
                        [
                            SNew(STextBlock)
                                .Text(FText::FromString("GAME OVER"))
                                .Font(TitleFont)
                                .Justification(ETextJustify::Center)
                        ]

                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .Padding(ButtonPadding)
                        [
                            SNew(SButton)
                                .OnClicked(this, &SGameOverWidget::OnRetryClicked)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("RETRY"))
                                        .Font(ButtonFont)
                                        .Justification(ETextJustify::Center)
                                ]
                        ]

                    + SVerticalBox::Slot()
                        .AutoHeight()
                        .Padding(ButtonPadding)
                        [
                            SNew(SButton)
                                .OnClicked(this, &SGameOverWidget::OnQuitClicked)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("QUIT"))
                                        .Font(ButtonFont)
                                        .Justification(ETextJustify::Center)
                                ]
                        ]
                ]
        ];
}

FReply SGameOverWidget::OnRetryClicked()
{
    if (OwningHUD.IsValid())
    {
        // Hide the Game Over menu
        OwningHUD->HideGameOver();

        // Show the main menu
        OwningHUD->ShowMainMenu();
    }
    return FReply::Handled();
}

FReply SGameOverWidget::OnQuitClicked()
{
    if (OwningHUD.IsValid())
    {
        if (APlayerController* PC = OwningHUD->PlayerOwner)
        {
            PC->ConsoleCommand("quit");
        }
    }
    return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
