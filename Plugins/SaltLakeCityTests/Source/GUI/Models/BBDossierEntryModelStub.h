// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBDossierEntryModel.h"
#include "BBDossierEntryModelStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBDossierEntryModelStub : public UIBBDossierEntryModel
{
	GENERATED_BODY()

	public:
		UBBDossierEntryModelStub();
		
		virtual UIBBWidget * GetWidget() const;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual void Initialize(UIBBDossierEntryWidget * NewView, UIBBDossierEntry * NewDossierEntry) override;

		virtual void Finalize() override;

		virtual FText GetEntryName() const override;

		void SetEntryName(FText NewName);

		virtual TSoftObjectPtr<UTexture2D> GetIcon() const override;

		void SetIcon(TSoftObjectPtr<UTexture2D> NewIcon);

		UIBBDossierEntry * GetEntry() const;

		void SetEntry(UIBBDossierEntry * NewDossierEntry);

		virtual float GetValue() const override;

		void SetValue(float NewValue);

		virtual float GetMaxValue() const override;

		void SetMaxValue(float NewMaxValue);

	protected:
		UPROPERTY()
		UIBBDossierEntryWidget * View;

		UPROPERTY()
		UIBBDossierEntry * DossierEntry;

		UPROPERTY()
		TSoftObjectPtr<UTexture2D> Icon;

		FText Name;

		float Value;

		float MaxValue;
};