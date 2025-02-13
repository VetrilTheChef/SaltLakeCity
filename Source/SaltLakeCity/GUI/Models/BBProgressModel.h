// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBProgressModel.h"
#include "BBProgressModel.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBProgressModel : public UIBBProgressModel
{
	GENERATED_BODY()

	public:
		UBBProgressModel();

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual void Initialize(UIBBProgressWidget * NewView, UIBBProgressComponent * NewProgressComponent) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBProgressWidget * View;

		UPROPERTY()
		UIBBProgressComponent * Component;

		void InitializeView(UIBBProgressWidget * NewView);

		void InitializeComponent(UIBBProgressComponent * NewProgressComponent);

		void FinalizeView();

		void FinalizeComponent();

		UFUNCTION()
		void UpdateProgress(float NewProgress);
};