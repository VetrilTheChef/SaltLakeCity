// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBGUIController.h"
#include "IBBDateTimeController.generated.h"

/**
 * 
 */

class UIBBCommandFactory;
class UIBBDateTimeModel;
class UIBBDateTimeWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDateTimeController : public UBBGUIController
{
	GENERATED_BODY()

	public:
		UIBBDateTimeController() : Super() { };

		virtual void Initialize(UIBBDateTimeWidget * DateTimeView, UIBBDateTimeModel * DateTimeModel, const UIBBCommandFactory * CommandFactory) PURE_VIRTUAL(UIBBDateTimeController::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBDateTimeController::Unbind, );

		virtual float GetSlowMotionTimeDilation() PURE_VIRTUAL(UIBBDateTimeController::GetSlowMotionTimeDilation, return -1.0f; );

		virtual float GetPlayTimeDilation() PURE_VIRTUAL(UIBBDateTimeController::GetPlayTimeDilation, return -1.0f; );

		virtual float GetFastForwardTimeDilation() PURE_VIRTUAL(UIBBDateTimeController::GetFastForwardTimeDilation, return -1.0f; );
};