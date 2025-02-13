// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBGUIController.h"
#include "IBBSkillEntryController.generated.h"

/**
 *
 */

class UIBBSkillEntryModel;
class UIBBSkillEntryWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSkillEntryController : public UBBGUIController
{
	GENERATED_BODY()

public:
	UIBBSkillEntryController() : Super() { };

	virtual void Initialize(UIBBSkillEntryWidget * SkillEntryView, UIBBSkillEntryModel * SkillEntryModel) PURE_VIRTUAL(UIBBSkillEntryController::Initialize, );

	virtual void Finalize() PURE_VIRTUAL(UIBBSkillEntryController::Finalize, );
};