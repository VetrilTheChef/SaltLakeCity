// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBBSelectable.generated.h"

UINTERFACE(MinimalAPI)

class UBBSelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class IBBWidgetTarget;
class UIBBSelectionComponent;

class SALTLAKECITY_API IBBSelectable
{
	GENERATED_BODY()

	public:
		virtual void UpdateSelection(bool Selected) PURE_VIRTUAL(IBBSelectable::UpdateSelection, );

		virtual UIBBSelectionComponent * GetSelectionComponent() const PURE_VIRTUAL(IBBSelectable::GetSelectionComponent, return nullptr; );

		virtual AActor * ToActor() PURE_VIRTUAL(IBBSelectable::ToActor, return nullptr; );

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() PURE_VIRTUAL(IBBSelectable::ToWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );

		DECLARE_EVENT_OneParam(IBBSelectable, FBBSelectionUpdate, bool);

		virtual FBBSelectionUpdate & OnSelectionUpdate() = 0;
};