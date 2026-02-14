// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBBuildEntryWidget.h"
#include "BBBuildEntryWidgetStub.generated.h"

/**
 * 
 */

class UIBBCommand;
class UTexture2D;

UCLASS(NotBlueprintable)

class UBBBuildEntryWidgetStub : public UIBBBuildEntryWidget
{
	GENERATED_BODY()

	public:
		UBBBuildEntryWidgetStub(const FObjectInitializer& ObjectInitializer);

		virtual EBBWidget GetType() const override;

		virtual void AddToScreen(int32 ZOrder = 0) override;

		FText GetEntryName();

		virtual void SetEntryName(FText NewName) override;

		UTexture2D* GetIcon();

		virtual void SetIcon(UTexture2D* NewImage) override;

		float GetPrice();

		virtual void SetPrice(float NewPrice) override;

		float GetTime();

		virtual void SetTime(float NewTime) override;

		UIBBCommand* GetCommand();

		virtual void SetCommand(UIBBCommand* NewCommand) override;

		void ClickEntryButton();

	protected:
		FText Name;

		UPROPERTY()
		UTexture2D* Icon;

		float Price;

		float Time;

		UPROPERTY()
		UIBBCommand* Command;

		virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};