// SaltLakeCity 5.7

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
		UIBBDossierEntryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { };

		virtual EBBWidget GetType() const
			PURE_VIRTUAL(UIBBDossierEntryWidget::GetType, return EBBWidget::None; );

		virtual void AddToScreen(int32 ZOrder = 0)
			PURE_VIRTUAL(UIBBDossierEntryWidget::AddToScreen, );

		virtual void SetEntryName(FText NewName)
			PURE_VIRTUAL(UIBBDossierEntryWidget::SetEntryName, );

		virtual void SetIcon(UTexture2D* NewIcon)
			PURE_VIRTUAL(UIBBDossierEntryWidget::SetIcon, );

		virtual void SetValue(FText NewValue)
			PURE_VIRTUAL(UIBBDossierEntryWidget::SetValue, );

		virtual void SetProgress(float NewProgress)
			PURE_VIRTUAL(UIBBDossierEntryWidget::SetProgress, );

	protected:
		virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override
			{ IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject); };
};
