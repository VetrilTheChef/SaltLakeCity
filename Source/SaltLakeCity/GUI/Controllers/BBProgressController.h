// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBProgressController.h"
#include "BBProgressController.generated.h"

/**
 * 
 */

class UIBBProgressModel;
class UIBBProgressWidget;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBProgressController : public UIBBProgressController
{
	GENERATED_BODY()

	public:
		UBBProgressController();

		virtual void Initialize(UIBBProgressWidget * ProgressView, UIBBProgressModel * ProgressModel) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBProgressModel * Model;

		UPROPERTY()
		UIBBProgressWidget * View;

		void InitializeModel(UIBBProgressModel * ProgressModel);

		void FinalizeModel();

		void InitializeView(UIBBProgressWidget * ProgressView);

		void FinalizeView();
};