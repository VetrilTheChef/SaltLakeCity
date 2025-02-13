// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBContextRowWidget.h"
#include "BBContextRowWidget.generated.h"

/**
 * 
 */

class UIBBButton;
class UIBBCommand;
class UImage;
class UTextBlock;
class UTexture2D;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBContextRowWidget : public UIBBContextRowWidget
{
	GENERATED_BODY()

	public:
		UBBContextRowWidget(const FObjectInitializer & ObjectInitializer);

		virtual void NativeOnInitialized() override;

		virtual void NativeDestruct() override;

		virtual EBBWidget GetType() const override;

		virtual void SetRowName(FText NewName) override;

		virtual void SetRowIcon(UTexture2D * NewIcon) override;

		virtual void SetRowTooltip(FText NewTooltip) override;
		
		virtual void SetCommand(UIBBCommand * Command) override;
	
	protected:
		UPROPERTY(meta = (BindWidget))
		UIBBButton * RowButton;

		UPROPERTY(meta = (BindWidget))
		UImage * RowIcon;

		UPROPERTY(meta = (BindWidget))
		UTextBlock * RowText;

		UFUNCTION()
		void Click();
};