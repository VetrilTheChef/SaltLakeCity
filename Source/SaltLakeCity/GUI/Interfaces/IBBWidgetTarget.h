// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GUI/Includes/BBDisplayNameEnum.h"
#include "IBBWidgetTarget.generated.h"

// This class does not need to be modified.

UINTERFACE(MinimalAPI)

class UBBWidgetTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class SALTLAKECITY_API IBBWidgetTarget
{
	GENERATED_BODY()

	public:
		virtual FText GetDisplayName(EBBDisplayName Mode) const PURE_VIRTUAL(IBBWidgetTarget::GetDisplayName, return FText::FromString(""); );

		DECLARE_EVENT(IBBWidgetTarget, FBBWidgetTargetUpdate);

		virtual FBBWidgetTargetUpdate & OnWidgetTargetUpdate() = 0;
};
