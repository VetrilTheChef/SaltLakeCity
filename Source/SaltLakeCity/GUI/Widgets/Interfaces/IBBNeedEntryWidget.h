// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBNeedEntryWidget.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBNeedEntryWidget : public UIBBWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	public:
		UIBBNeedEntryWidget(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) { };

		virtual EBBWidget GetType() const PURE_VIRTUAL(UIBBNeedEntryWidget::GetType, return EBBWidget::None; );

		virtual void SetEntryName(FText NewName) PURE_VIRTUAL(UIBBNeedEntryWidget::SetEntryName, );

		virtual void SetIcon(UTexture2D * NewIcon) PURE_VIRTUAL(UIBBNeedEntryWidget::SetIcon, );

		virtual void SetValue(float NewValue) PURE_VIRTUAL(UIBBNeedEntryWidget::SetPrice, );

		virtual void SetMaxValue(float NewMaxValue) PURE_VIRTUAL(UIBBNeedEntryWidget::SetTime, );

	protected:
		virtual void NativeOnListItemObjectSet(UObject * ListItemObject) override { IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject); };
};
