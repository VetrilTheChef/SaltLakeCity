// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBBuildEntryWidget.h"
#include "BBBuildEntryWidget.generated.h"

/**
 * 
 */

class UBorder;
class UIBBButton;
class UTextBlock;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBBuildEntryWidget : public UIBBBuildEntryWidget
{
	GENERATED_BODY()

	public:
		UBBBuildEntryWidget(const FObjectInitializer& ObjectInitializer);

		virtual EBBWidget GetType() const override;

		virtual void AddToScreen(int32 ZOrder = 0) override;

		virtual void SetEntryName(FText NewName) override;

		virtual void SetIcon(UTexture2D* NewIcon) override;

		virtual void SetPrice(float NewPrice) override;

		virtual void SetTime(float NewTime) override;

		virtual void SetCommand(UIBBCommand* NewCommand) override;

	protected:
		UPROPERTY(meta = (BindWidget))
		UIBBButton* EntryButton;

		UPROPERTY(meta = (BindWidget))
		UBorder* EntryIcon;

		UPROPERTY(meta = (BindWidget))
		UTextBlock* EntryPrice;

		UPROPERTY(meta = (BindWidget))
		UTextBlock* EntryTime;

		virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
