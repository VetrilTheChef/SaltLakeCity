// SaltLakeCity 5.7

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
		UBBDossierEntryWidgetStub(const FObjectInitializer& ObjectInitializer);

		virtual EBBWidget GetType() const override;

		virtual void AddToScreen(int32 ZOrder = 0) override;

		FText GetEntryName() const;

		virtual void SetEntryName(FText NewName) override;

		UTexture2D* GetIcon() const;

		virtual void SetIcon(UTexture2D* NewIcon) override;

		FText GetValue() const;

		virtual void SetValue(FText NewValue) override;

		float GetProgress() const;

		virtual void SetProgress(float NewProgress) override;

	protected:
		TSoftObjectPtr<UTexture2D> Icon;

		FText Name;

		FText Value;

		float Progress;

		virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};