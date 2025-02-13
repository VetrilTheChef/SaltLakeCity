// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Attributes/Interfaces/IBBBaseAttributeSet.h"
#include "IBBDossierEntry.generated.h"

/**
 * 
 */

class UTexture2D;

using FBBUpdate = UIBBBaseAttributeSet::FBBUpdate;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDossierEntry : public UObject
{
	GENERATED_BODY()

	public:
		UIBBDossierEntry() : Super() { };

		virtual void Initialize(FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, FBBUpdate * NewAttributeValueUpdate, FBBUpdate * NewMaxAttributeValueUpdate) PURE_VIRTUAL(UIBBDossierEntry::Initialize, );
		
		virtual void Finalize() PURE_VIRTUAL(UIBBDossierEntry::Finalize, );
		
		virtual FText GetEntryName() const PURE_VIRTUAL(UIBBDossierEntry::GetEntryName, return FText::FromString(""); );

		virtual TSoftObjectPtr<UTexture2D> GetIcon() const PURE_VIRTUAL(UIBBDossierEntry::GetIcon, return TSoftObjectPtr<UTexture2D>(); );

		virtual float GetValue() const PURE_VIRTUAL(UIBBDossierEntry::GetValue, return -1.0f; );
		
		virtual float GetMaxValue() const PURE_VIRTUAL(UIBBDossierEntry::GetMaxValue, return -1.0f; );

		DECLARE_EVENT_OneParam(UIBBDossierEntry, FBBValueUpdate, float);

		FBBValueUpdate & OnValueUpdate() { return ValueUpdate; };

		DECLARE_EVENT_OneParam(UIBBDossierEntry, FBBMaxValueUpdate, float);

		FBBMaxValueUpdate & OnMaxValueUpdate() { return MaxValueUpdate; };

		FORCEINLINE virtual bool operator==(const UIBBDossierEntry * Other) const PURE_VIRTUAL(UIBBDossierEntry::operator==, return false; );

	protected:
		FBBValueUpdate ValueUpdate;

		FBBMaxValueUpdate MaxValueUpdate;
};