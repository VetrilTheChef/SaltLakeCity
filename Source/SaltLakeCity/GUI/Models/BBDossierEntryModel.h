// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBDossierEntryModel.h"
#include "BBDossierEntryModel.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBDossierEntryModel : public UIBBDossierEntryModel
{
	GENERATED_BODY()

	public:
		UBBDossierEntryModel();

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual void Initialize(UIBBDossierEntryWidget * NewView, UIBBDossierEntry * Entry) override;

		virtual void Finalize() override;

		virtual FText GetEntryName() const override;

		virtual TSoftObjectPtr<UTexture2D> GetIcon() const override;

		virtual float GetValue() const;

		virtual float GetMaxValue() const;

	protected:
		UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		float MinAttribute;

		UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		float MaxAttribute;

		UPROPERTY()
		UIBBDossierEntryWidget * View;

		UPROPERTY()
		UIBBDossierEntry * DossierEntry;

		void InitializeView(UIBBDossierEntryWidget * NewView);

		void InitializeEntry(UIBBDossierEntry * NewDossierEntry);

		void FinalizeView();

		void FinalizeEntry();

		void UpdateValues(float NewValue, float NewMaxValue);
};