// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBBuildController.h"
#include "BBBuildControllerStub.generated.h"

/**
 * 
 */

class UIBBBuildModel;
class UIBBBuildWidget;

UCLASS(NotBlueprintable)

class UBBBuildControllerStub : public UIBBBuildController
{
	GENERATED_BODY()

	public:
		UBBBuildControllerStub();

		virtual void Initialize(UIBBBuildWidget * BuildWiew, UIBBBuildModel * BuildModel) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBBuildModel * Model;

		UPROPERTY()
		UIBBBuildWidget * View;

		void InitializeModel(UIBBBuildModel * BuildModel);

		void FinalizeModel();

		void InitializeView(UIBBBuildWidget * BuildView);

		void FinalizeView();

		void AddEntries(UIBBBuildWidget & BuildView, UIBBBuildModel & BuildModel);

		void AddEntriesOfCategory(EBBBuildCategory Category, UIBBBuildWidget & BuildView, UIBBBuildModel & BuildModel);

		void ClearEntries(UIBBBuildWidget & BuildView);

		void ClearEntriesOfCategory(EBBBuildCategory Category, UIBBBuildWidget & BuildView);
};