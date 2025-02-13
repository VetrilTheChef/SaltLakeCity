// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBProgressModel.h"
#include "BBProgressModelStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBProgressModelStub : public UIBBProgressModel
{
	GENERATED_BODY()

	public:
		UBBProgressModelStub();

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		void SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification);

		virtual void Initialize(UIBBProgressWidget * NewView, UIBBProgressComponent * NewProgressComponent) override;

		virtual void Finalize() override;

		float GetProgress();

		virtual void SetProgress(float NewProgress);

		UIBBProgressComponent * GetComponent() const;

	protected:
		UPROPERTY()
		UIBBProgressWidget * View;

		UPROPERTY()
		UIBBProgressComponent * Component;

		UPROPERTY()
		UIBBWidgetSpecification * WidgetSpecification;

		float Progress;

		UFUNCTION()
		void UpdateProgress(float NewProgress);
};