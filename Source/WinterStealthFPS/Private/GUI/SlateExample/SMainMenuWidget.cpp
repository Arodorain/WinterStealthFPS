// Fill out your copyright notice in the Description page of Project Settings.

#include "GUI/SlateExample/SMainMenuWidget.h"
#include "SlateOptMacros.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainMenuWidget::Construct(const FArguments& InArgs)
{
    OwningHUD = InArgs._OwningHUD;

    // Adjust the top padding to move the menu lower on the screen
    const FMargin ContentPadding(800.f, 300.f); // x = horizontal, y = vertical (top)
    const FMargin ButtonPadding(10.f);

    FSlateFontInfo TitleFont = FCoreStyle::Get().GetFontStyle("NormalText");
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
                    SNew(SImage)
                        .ColorAndOpacity(FLinearColor::Black)
                ]

                + SOverlay::Slot()
                .HAlign(HAlign_Fill)
                .VAlign(VAlign_Fill)
                .Padding(ContentPadding)
                [
                    SNew(SVerticalBox)

                        // Title
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .HAlign(HAlign_Center)
                        [
                            SNew(STextBlock)
                                .Text(FText::FromString("ECLIPSE PROTOCOL"))
                                .Font(TitleFont)
                                .Justification(ETextJustify::Center)
                        ]

                        // Spacer between title and buttons
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .Padding(FMargin(0.f, 50.f))
                        [
                            SNew(SBox)
                        ]

                        // Start Button
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .Padding(ButtonPadding)
                        .HAlign(HAlign_Center)
                        [
                            SNew(SButton)
                                .OnClicked(this, &SMainMenuWidget::OnStartClicked)
                                [
                                    SNew(STextBlock)
                                        .Text(FText::FromString("START"))
                                        .Font(ButtonFont)
                                        .Justification(ETextJustify::Center)
                                ]
                        ]

                    // Spacer between buttons
                    + SVerticalBox::Slot()
                        .AutoHeight()
                        .Padding(FMargin(0.f, 20.f))
                        [
                            SNew(SBox)
                        ]

                        // Quit Button
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .Padding(ButtonPadding)
                        .HAlign(HAlign_Center)
                        [
                            SNew(SButton)
                                .OnClicked(this, &SMainMenuWidget::OnQuitClicked)
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

FReply SMainMenuWidget::OnStartClicked()
{
    if (OwningHUD.IsValid())
    {
        OwningHUD->HideMainMenu();
    }
    return FReply::Handled();
}

FReply SMainMenuWidget::OnQuitClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Quit Button Clicked"));
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
