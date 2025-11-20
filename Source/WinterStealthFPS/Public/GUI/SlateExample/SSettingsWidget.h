// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/GameHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class WINTERSTEALTHFPS_API SSettingsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSettingsWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AGameHUD>, OwningHUD)
	SLATE_ARGUMENT(int, MyInt);
	SLATE_END_ARGS()

	TWeakObjectPtr<class AGameHUD> OwningHUD;

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	int MyInt;

	FReply OnResumeClicked() const;
	FReply OnSettingsClicked() const;
	FReply OnQuitClicked() const;
	/*
		--- Smart Pointer Cheat Sheet ---

		Unique Pointer: TUninque<T> = TUniquePtr<int> Score;
			- Sole ownership of an object
			- Cannot be copied, only moved
			- Automatically deallocates memory when it goes out of scope
			- Recource management for single ownership scenarios

		Shared Pointer: TSharedPtr<T> = TSharedPtr<int> Score;
			- Multiple ownership of an object
				- Can be copied, increasing reference count
				- Automatically deallocates memory when the last refernce is gone
				- Eg, UI Widget, Game Objects shared across systems

		Weak Pointers: TWeakPtr<T> = TWeakPtr<int> Score;
			- Non-owning refernce to an object managed by TSharedPtr
				- Does not affect reference count
				- Can be converted to TSharedPtr if the object is still valid
				- Pervents circular reference and memory leaks
				- Temporary access to memory

		SoftObjectsPtr<T>: TSoftObjectPtr<UTexture> TextureRef;
			- Reference to an asset that may not be loaded in memory
				- Can be serialized and saved as a reference
				- Loads the assset on demand
				- usefull for large assets or optional content
	*/
};
