// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"
#include "BBDossierEntryWidgetStub.generated.h"

/**
 * 
 */

class UBorder;
class UProgressBar;
class UTextBlock;

UCLASS(NotBlueprintable)

class UBBDossierEntryWidgetStub : public UIBBDossierEntryWidget
{
	GENERATED_BODY()

	public:
		UBBDossierEntryWidgetStub(const FObjectInitializer & ObjectInitializer);

		virtual EBBWidget GetType() const override;

		FText GetEntryName() const;

		virtual void SetEntryName(FText NewName) override;

		UTexture2D * GetIcon() const;

		virtual void SetIcon(UTexture2D * NewIcon) override;

		float GetValue() const;

		virtual void SetValue(float NewValue) override;

		float GetMaxValue() const;

		virtual void SetMaxValue(float NewMaxValue) override;

	protected:
		FText Name;

		UPROPERTY()
		UTexture2D * Icon;

		float Value;

		float MaxValue;

		virtual void NativeOnListItemObjectSet(UObject * ListItemObject) override;
};