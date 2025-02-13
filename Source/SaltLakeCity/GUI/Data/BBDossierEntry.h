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

		virtual void Initialize(FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, FBBUpdate * NewAttributeValueUpdate, FBBUpdate * NewMaxAttributeValueUpdate) override;

		virtual void Finalize() override;

		virtual FText GetEntryName() const override;

		virtual TSoftObjectPtr<UTexture2D> GetIcon() const override;

	protected:
		UPROPERTY()
		TSoftObjectPtr<UTexture2D> Icon;

		FText Name;

		FBBUpdate * AttributeValueUpdate;

		FBBUpdate * MaxAttributeValueUpdate;

		void UpdateValue(float NewValue) const;

		void UpdateMaxValue(float NewMaxValue) const;
};