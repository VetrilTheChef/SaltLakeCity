// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBGUIController.h"
#include "IBBProgressController.generated.h"

/**
 * 
 */

class UIBBProgressModel;
class UIBBProgressWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBProgressController : public UBBGUIController
{
	GENERATED_BODY()

	public:
		UIBBProgressController() : Super() { };

		virtual void Initialize(UIBBProgressWidget * ProgressView, UIBBProgressModel * ProgressModel) PURE_VIRTUAL(UIBBProgressController::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBProgressController::Finalize, );

		virtual float GetProgress() PURE_VIRTUAL(UIBBProgressController::GetProgress, return -1.0f; );

		virtual void SetProgress(float NewProgress) PURE_VIRTUAL(UIBBProgressController::SetProgress, );
};