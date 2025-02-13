// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBSkillEntryWidget.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSkillEntryWidget : public UIBBWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	public:
		UIBBSkillEntryWidget(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) { };

		virtual EBBWidget GetType() const PURE_VIRTUAL(UIBBSkillEntryWidget::GetType, return EBBWidget::None; );

		virtual void SetEntryName(FText NewName) PURE_VIRTUAL(UIBBSkillEntryWidget::SetEntryName, );

		virtual void SetIcon(UTexture2D * NewIcon) PURE_VIRTUAL(UIBBSkillEntryWidget::SetIcon, );

		virtual void SetValue(float NewValue) PURE_VIRTUAL(UIBBSkillEntryWidget::SetPrice, );

		virtual void SetMaxValue(float NewMaxValue) PURE_VIRTUAL(UIBBSkillEntryWidget::SetTime, );

	protected:
		virtual void NativeOnListItemObjectSet(UObject * ListItemObject) override { IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject); };
};
