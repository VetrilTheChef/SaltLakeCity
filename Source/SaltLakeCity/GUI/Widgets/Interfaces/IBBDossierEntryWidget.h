// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBDossierEntryWidget.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDossierEntryWidget : public UIBBWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	public:
		UIBBDossierEntryWidget(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) { };

		virtual EBBWidget GetType() const PURE_VIRTUAL(UIBBDossierEntryWidget::GetType, return EBBWidget::None; );

		virtual void SetEntryName(FText NewName) PURE_VIRTUAL(UIBBDossierEntryWidget::SetEntryName, );

		virtual void SetIcon(UTexture2D * NewIcon) PURE_VIRTUAL(UIBBDossierEntryWidget::SetIcon, );

		virtual void SetValue(float NewValue) PURE_VIRTUAL(UIBBDossierEntryWidget::SetPrice, );

		virtual void SetMaxValue(float NewMaxValue) PURE_VIRTUAL(UIBBDossierEntryWidget::SetTime, );

	protected:
		virtual void NativeOnListItemObjectSet(UObject * ListItemObject) override { IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject); };
};
