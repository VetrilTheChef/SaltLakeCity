// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBProgressController.h"
#include "BBProgressControllerStub.generated.h"

/**
 * 
 */

class UIBBProgressModel;
class UIBBProgressWidget;
class UIBBWidgetComponent;

UCLASS(NotBlueprintable)

class UBBProgressControllerStub : public UIBBProgressController
{
	GENERATED_BODY()

	public:
		UBBProgressControllerStub();

		virtual void Initialize(UIBBProgressWidget * ProgressView, UIBBProgressModel * ProgressModel) override;

		virtual void Finalize() override;

		virtual float GetProgress() override;

		virtual void SetProgress(float NewProgress) override;

	protected:
		UPROPERTY()
		UIBBProgressWidget * View;

		UPROPERTY()
		UIBBProgressModel * Model;

		void InitializeView(UIBBProgressWidget * ProgressView);

		void FinalizeView();

		void InitializeModel(UIBBProgressModel * ProgressModel);

		void FinalizeModel();
};