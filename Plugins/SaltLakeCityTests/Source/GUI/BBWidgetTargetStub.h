// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Interfaces/IBBWidgetTarget.h"
#include "BBWidgetTargetStub.generated.h"

/**
*
*/

UCLASS(NotBlueprintable)

class UBBWidgetTargetStub : public UObject, public IBBWidgetTarget
{
	GENERATED_BODY()

	public:
		UBBWidgetTargetStub();

		virtual FText GetDisplayName(EBBDisplayName Mode) const override;

		void SetDisplayName(FText NewDisplayName);

		DECLARE_DERIVED_EVENT(UBBWidgetTargetStub, IBBWidgetTarget::FBBWidgetTargetUpdate, FBBWidgetTargetUpdate);

		virtual FBBWidgetTargetUpdate & OnWidgetTargetUpdate() final override { return WidgetTargetUpdate; };

	protected:
		FText DisplayName;

		FBBWidgetTargetUpdate WidgetTargetUpdate;
};