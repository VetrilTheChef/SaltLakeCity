// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBSkillEntryModel.h"
#include "BBSkillEntryModelStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBSkillEntryModelStub : public UIBBSkillEntryModel
{
	GENERATED_BODY()

	public:
		UBBSkillEntryModelStub();
		
		virtual UIBBWidget * GetWidget() const;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual void Initialize(UIBBSkillEntryWidget * NewView, const UIBBSkillEntry * NewEntry) override;

		virtual void Finalize() override;

		virtual const FText GetEntryName() const override;

		void SetEntryName(const FText NewName);

		virtual const TSoftObjectPtr<UTexture2D> GetEntryIcon() const override;

		void SetEntryIcon(const TSoftObjectPtr<UTexture2D> NewIcon);

		virtual const float GetEntryValue() const override;

		void SetEntryValue(const float NewValue);

		virtual const float GetEntryMaxValue() const override;

		void SetEntryMaxValue(const float NewMaxValue);

	protected:
		UPROPERTY()
		UIBBSkillEntryWidget * View;

		UPROPERTY()
		TSoftObjectPtr<UTexture2D> EntryIcon;

		FText EntryName;

		float EntryValue;

		float EntryMaxValue;
};