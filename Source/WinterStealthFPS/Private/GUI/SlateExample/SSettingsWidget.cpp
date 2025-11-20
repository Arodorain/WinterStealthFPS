// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/SlateExample/SSettingsWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSettingsWidget::Construct(const FArguments& InArgs)
{
	OwningHUD = InArgs._OwningHUD;
	MyInt = InArgs._MyInt;

	// Title Config
	const FMargin ContentPadding(800.0f, 300.0f);
	const FText TitleText = FText::FromString("Pause Menu");
	FSlateFontInfo TitleFont = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TitleFont.Size = 60;

	// Button
	const FMargin ButtonPadding(10.0f);
	FSlateFontInfo ButtonFont = TitleFont;
	ButtonFont.Size = 40;

	// Resume Button
	const FText ResumeButtonText = FText::FromString("RESUME");

	// Settings Button
	const FText SettingsButtonText = FText::FromString("SETTINGS");

	// Quit Button
	const FText QuitButtonText = FText::FromString("QUIT");

	ChildSlot
	[
		// Populate the widget
		SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
					.ColorAndOpacity(FColor::Black)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ContentPadding)
			[
				SNew(SVerticalBox)
				// Title Text
				+ SVerticalBox::Slot()
				[
					SNew(STextBlock)
					.Text(TitleText)
					.Font(TitleFont)
					.Justification(ETextJustify::Center)
				]
				// Resume Button
				+ SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SSettingsWidget::OnResumeClicked)
					[
						SNew(STextBlock)
						.Text(ResumeButtonText)
						.Font(ButtonFont)
						.Justification(ETextJustify::Center)
					]
				]
				// Settings Button
				+ SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SSettingsWidget::OnSettingsClicked)
					[
						SNew(STextBlock)
						.Text(SettingsButtonText)
						.Font(ButtonFont)
						.Justification(ETextJustify::Center)
					]
				]
				// Quit Button
				+ SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SSettingsWidget::OnQuitClicked)
					[
						SNew(STextBlock)
						.Text(QuitButtonText)
						.Font(ButtonFont)
						.Justification(ETextJustify::Center)
					]
				]	
			]
	];
}

FReply SSettingsWidget::OnResumeClicked() const
{
	UE_LOG(LogTemp, Warning, TEXT("Resume Button Clicked"));
	if (OwningHUD.IsValid())
	{
		OwningHUD->HideSettingsMenu();
	}
	return FReply::Handled();
}

FReply SSettingsWidget::OnSettingsClicked() const
{
	UE_LOG(LogTemp, Warning, TEXT("Settings Button Clicked"));
	UE_LOG(LogTemp, Warning, TEXT("MyInt: %i"), MyInt);
	return FReply::Handled();
}

FReply SSettingsWidget::OnQuitClicked() const
{
	UE_LOG(LogTemp, Warning, TEXT("Quit Button Clicked"));
	if (OwningHUD.IsValid())
	{
		if(APlayerController* PC = OwningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("quit");
		}
	}
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
