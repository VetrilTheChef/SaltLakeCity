// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Data/Interfaces/IBBDossierEntry.h"
#include "BBDossierEntry.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBDossierEntry : public UIBBDossierEntry
{
	GENERATED_BODY()

	public:
		UBBDossierEntry();

		virtual void Initialize(FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, FBBGetAttributeDelegate NewValueDelegate, FBBGetAttributeDelegate NewMaxValueDelegate, FBBAttributeUpdate * NewAttributeUpdate) override;

		virtual void Finalize() override;

		virtual FText GetEntryName() const override;

		virtual TSoftObjectPtr<UTexture2D> GetIcon() const override;

		virtual float GetValue() const override;

		virtual float GetMaxValue() const override;

	protected:
		UPROPERTY()
		TSoftObjectPtr<UTexture2D> Icon;

		FText Name;

		FBBGetAttributeDelegate ValueDelegate;
		
		FBBGetAttributeDelegate MaxValueDelegate;

		FBBAttributeUpdate * AttributeUpdate;

		UFUNCTION()
		void UpdateEntry(float NewValue, float NewMaxValue) const;
};