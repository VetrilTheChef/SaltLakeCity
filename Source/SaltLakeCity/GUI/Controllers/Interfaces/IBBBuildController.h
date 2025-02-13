// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBBuildCategoryEnum.h"
#include "GUI/Controllers/BBGUIController.h"
#include "IBBBuildController.generated.h"

/**
 * 
 */

class UIBBBuildModel;
class UIBBBuildWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBuildController : public UBBGUIController
{
	GENERATED_BODY()

	public:
		UIBBBuildController() : Super() { };

		virtual void Initialize(UIBBBuildWidget * BuildView, UIBBBuildModel * BuildModel) PURE_VIRTUAL(UIBBBuildController::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(&UIBBBuildController::Finalize, );
};