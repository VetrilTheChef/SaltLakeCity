// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBSkillEntryController.h"
#include "BBSkillEntryControllerStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBSkillEntryControllerStub : public UIBBSkillEntryController
{
	GENERATED_BODY()

	public:
		UBBSkillEntryControllerStub();

		virtual void Initialize(UIBBSkillEntryWidget * SkillEntryView, UIBBSkillEntryModel * SkillEntryModel) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBSkillEntryModel * Model;

		UPROPERTY()
		UIBBSkillEntryWidget * View;

		void InitializeModel(UIBBSkillEntryModel * SkillEntryModel);
		
		void FinalizeModel();

		void InitializeView(UIBBSkillEntryWidget * SkillEntryView, UIBBSkillEntryModel * SkillEntryModel);

		void FinalizeView();
};