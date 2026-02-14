// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBContextRowWidget.h"
#include "BBContextRowWidgetStub.generated.h"

/**
 * 
 */

class UIBBContextWidget;

UCLASS(NotBlueprintable)

class UBBContextRowWidgetStub : public UIBBContextRowWidget
{
	GENERATED_BODY()
	
	public:
		UBBContextRowWidgetStub(const FObjectInitializer & ObjectInitializer);

		virtual EBBWidget GetType() const override;

		void AddToScreen(int32 ZOrder = 0) override;

		FText GetRowName() const;

		virtual void SetRowName(FText NewName) override;

		UTexture2D * GetRowIcon() const;

		virtual void SetRowIcon(UTexture2D * NewIcon) override;

		FText GetRowTooltip() const;

		virtual void SetRowTooltip(FText NewTooltip) override;

		UIBBCommand * GetCommand();

		virtual void SetCommand(UIBBCommand * NewCommand) override;

		ESlateVisibility GetTestVisibility();

		virtual void SetVisibility(ESlateVisibility InVisibility) override;

		void ClickRowButton();

	protected:
		UPROPERTY()
		FText Name;

		UPROPERTY()
		FText Tooltip;

		UPROPERTY()
		UTexture2D * Icon;

		UPROPERTY()
		UIBBCommand * Command;

		UPROPERTY()
		ESlateVisibility TestVisibility;
};