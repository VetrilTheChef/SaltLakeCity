// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBBuildEntryController.h"
#include "BBBuildEntryController.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBBuildEntryController : public UIBBBuildEntryController
{
	GENERATED_BODY()

	public:
		UBBBuildEntryController();

		virtual void Initialize(UIBBBuildEntryWidget * BuildEntryView, UIBBBuildEntryModel * BuildEntryModel, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;

	protected:
		void InitializeView(UIBBBuildEntryWidget & BuildEntryView, UIBBBuildEntryModel & BuildEntryModel, const UIBBCommandFactory & CommandFactory) const;

		void CreateCommands(UIBBBuildEntryWidget & BuildEntryView, UIBBBuildEntryModel & BuildEntryModel, const UIBBCommandFactory & CommandFactory) const;
};