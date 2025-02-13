// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Data/Interfaces/IBBDossierEntry.h"
#include "BBDossierEntryStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBDossierEntryStub : public UIBBDossierEntry
{
	GENERATED_BODY()

	public:
		UBBDossierEntryStub();
		
		virtual void Initialize(FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, FBBUpdate * NewAttributeValueUpdate, FBBUpdate * NewMaxAttributeValueUpdate) override;

		virtual void Finalize() override;
		
		virtual FText GetEntryName() const override;

		void SetEntryName(FText NewName);

		virtual TSoftObjectPtr<UTexture2D> GetIcon() const override;

		void SetIcon(TSoftObjectPtr<UTexture2D> NewIcon);

		virtual float GetValue() const override;

		void SetValue(float NewValue);

		virtual float GetMaxValue() const override;

		void SetMaxValue(const float NewMaxValue);

		FORCEINLINE virtual bool operator==(const UIBBDossierEntry * Other) const override;

	protected:
		UPROPERTY()
		TSoftObjectPtr<UTexture2D> Icon;

		FText Name;

		FBBUpdate * AttributeValueUpdate;

		FBBUpdate * MaxAttributeValueUpdate;

		float Value;

		float MaxValue;

		void UpdateValue(float NewValue);

		void UpdateMaxValue(float NewMaxValue);
};