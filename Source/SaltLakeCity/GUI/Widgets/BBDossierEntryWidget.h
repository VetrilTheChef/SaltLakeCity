// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"
#include "BBDossierEntryWidget.generated.h"

/**
 * 
 */

class UBorder;
class UProgressBar;
class UTextBlock;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBDossierEntryWidget : public UIBBDossierEntryWidget
{
	GENERATED_BODY()

	public:
		UBBDossierEntryWidget(const FObjectInitializer & ObjectInitializer);

		virtual EBBWidget GetType() const override;

		virtual void SetEntryName(FText NewName) override;

		virtual void SetIcon(UTexture2D * NewIcon) override;

		virtual void SetValue(float NewValue) override;

		virtual void SetMaxValue(float NewMaxValue) override;

	protected:
		UPROPERTY(meta = (BindWidget))
		UTextBlock * EntryName;

		UPROPERTY(meta = (BindWidget))
		UBorder * EntryIcon;

		UPROPERTY(meta = (BindWidget))
		UTextBlock * EntryValue;

		UPROPERTY(meta = (BindWidget))
		UTextBlock * EntryMaxValue;

		UPROPERTY(meta = (BindWidget))
		UProgressBar * EntryProgressBar;

		virtual void NativeOnListItemObjectSet(UObject * ListItemObject) override;

		void UpdateProgressBar();
};
