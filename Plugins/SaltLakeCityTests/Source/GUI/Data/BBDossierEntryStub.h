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
		
		virtual void Initialize(FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, FBBGetAttributeDelegate NewValueDelegate, FBBGetAttributeDelegate NewMaxValueDelegate, FBBAttributeUpdate * NewAttributeUpdate) override;

		virtual void Finalize() override;
		
		virtual FText GetEntryName() const override;

		void SetEntryName(FText NewName);

		virtual TSoftObjectPtr<UTexture2D> GetIcon() const override;

		void SetIcon(TSoftObjectPtr<UTexture2D> NewIcon);

		float GetValue() const;

		void SetValue(float NewValue);

		float GetMaxValue() const;

		void SetMaxValue(const float NewMaxValue);

	protected:
		UPROPERTY()
		TSoftObjectPtr<UTexture2D> Icon;

		FText Name;

		FBBGetAttributeDelegate ValueDelegate;

		FBBGetAttributeDelegate MaxValueDelegate;

		FBBAttributeUpdate * AttributeUpdate;

		float Value;

		float MaxValue;

		UFUNCTION()
		void UpdateEntry(float NewValue, float NewMaxValue);
};