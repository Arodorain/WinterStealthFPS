// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/GameMenuWidget.h"

void UGameMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UpdateHealthBar(1.0f);
	SetBulletText(0);
	SetTimerText(60);

	// Example of spawning user widgets dynamically
	for (int i = 0; i < 4; i++) {
		UUserWidget* Widget = CreateWidget(this, ButtonWidgetClass);
		ButtonContainer->AddChild(Widget);

		UButtonWidget* Button = Cast<UButtonWidget>(Widget);
		Button->SetText(i);
	}
}

void UGameMenuWidget::UpdateHealthBar(float HealthPercent)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(HealthPercent);
}

void UGameMenuWidget::SetBulletText(int amount)
{
	if (!BulletText) return;

	UIBullet += amount;
	// Whatever way you prefer to format strings
	//BulletText->SetText(FText::FromString("Bullet: " + FString::FromInt(UIBullet)));
	BulletText->SetText(FText::FromString(FString::Printf(TEXT("12/36"), UIBullet)));
}

void UGameMenuWidget::SetTimerText(int timer)
{
	if (!TimerText) return;

	TimerText->SetText(FText::FromString(FString::Printf(TEXT("Timer: %d"), timer)));
}

