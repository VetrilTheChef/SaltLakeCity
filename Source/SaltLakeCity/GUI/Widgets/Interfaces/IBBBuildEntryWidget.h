// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBBuildEntryWidget.generated.h"

/**
 * 
 */

class UIBBCommand;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBuildEntryWidget : public UIBBWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	public:
		UIBBBuildEntryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { };

		virtual EBBWidget GetType() const
			PURE_VIRTUAL(UIBBBuildEntryWidget::GetType, return EBBWidget::None; );

		virtual void AddToScreen(int32 ZOrder = 0)
			PURE_VIRTUAL(UIBBBuildEntryWidget::AddToScreen, );

		virtual void SetEntryName(FText NewName)
			PURE_VIRTUAL(UIBBBuildEntryWidget::SetEntryName, );

		virtual void SetIcon(UTexture2D* NewIcon)
			PURE_VIRTUAL(UIBBBuildEntryWidget::SetIcon, );

		virtual void SetPrice(float NewPrice)
			PURE_VIRTUAL(UIBBBuildEntryWidget::SetPrice, );

		virtual void SetTime(float NewTime)
			PURE_VIRTUAL(UIBBBuildEntryWidget::SetTime, );

		virtual void SetCommand(UIBBCommand* NewCommand)
			PURE_VIRTUAL(UIBBBuildEntryWidget::SetCommand, );

	protected:
		virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override
			{ IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject); };
};
