// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Data/BBBuildRow.h"
#include "GUI/Controllers/Interfaces/IBBBuildController.h"
#include "BBBuildController.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBBuildController : public UIBBBuildController
{
	GENERATED_BODY()

	public:
		UBBBuildController();

		virtual void Initialize(UIBBBuildWidget * BuildView, UIBBBuildModel * BuildModel) override;

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