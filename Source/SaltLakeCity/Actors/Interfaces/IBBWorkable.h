// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "GUI/Interfaces/IBBWidgetTarget.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "IBBWorkable.generated.h"

class UIBBAbilityTask;
class UIBBWorkComponent;

UINTERFACE(MinimalAPI)

class UBBWorkable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class SALTLAKECITY_API IBBWorkable
{
	GENERATED_BODY()

	public:
		virtual UIBBWorkComponent * GetWorkComponent() const PURE_VIRTUAL(IBBWorkable::GetWorkComponent, return nullptr; );

		virtual AActor * ToActor() PURE_VIRTUAL(IBBWorkable::ToActor, return nullptr; );

		virtual TScriptInterface<IBBWidgetTarget> ToWidgetTarget() PURE_VIRTUAL(IBBWorkable::ToWidgetTarget, return TScriptInterface<IBBWidgetTarget>(); );
};