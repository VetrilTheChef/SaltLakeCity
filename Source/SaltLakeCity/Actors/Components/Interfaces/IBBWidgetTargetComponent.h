// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "IBBWidgetTargetComponent.generated.h"

UINTERFACE(MinimalAPI)

class UBBWidgetTargetComponent : public UInterface
{
	GENERATED_BODY()
};

class IBBWidgetTarget;

/**
 *
 */

class SALTLAKECITY_API IBBWidgetTargetComponent
{
	GENERATED_BODY()

	public:
		virtual const TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const
			PURE_VIRTUAL(IBBWidgetTargetComponent::GetWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );

		DECLARE_EVENT_OneParam(
			IBBWidgetTargetComponent,
			FBBWidgetTargetUpdate,
			const TScriptInterface<IBBWidgetTarget>
		);

		virtual FBBWidgetTargetUpdate& OnWidgetTargetUpdate() = 0;
};