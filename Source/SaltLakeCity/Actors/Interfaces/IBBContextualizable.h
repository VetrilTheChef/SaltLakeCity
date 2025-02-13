// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GUI/Includes/BBContextEnum.h"
#include "GUI/Interfaces/IBBWidgetTarget.h"
#include "IBBContextualizable.generated.h"

class UIBBContextComponent;

UINTERFACE(MinimalAPI)

class UBBContextualizable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class SALTLAKECITY_API IBBContextualizable
{
	GENERATED_BODY()

	public:
		virtual void UpdateContext(bool Contextualized) PURE_VIRTUAL(IBBContextualizable::UpdateContext, );

		virtual bool IsContextOption(EBBContext ContextOption) const PURE_VIRTUAL(IBBContextualizable::IsContextOption, return false; );

		virtual UIBBContextComponent * GetContextComponent() const PURE_VIRTUAL(IBBContextualizable::GetContextComponent, return nullptr; );

		virtual AActor * ToActor() PURE_VIRTUAL(IBBContextualizable::ToActor, return nullptr; );

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() PURE_VIRTUAL(IBBContextualizable::ToWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );

		DECLARE_EVENT_OneParam(IBBContextualizable, FBBContextUpdate, bool);

		virtual FBBContextUpdate & OnContextUpdate() = 0;
};