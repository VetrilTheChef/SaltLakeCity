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

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDossierEntry : public UObject
{
	GENERATED_BODY()

	public:
		UIBBDossierEntry() : Super() { };

		using FBBGetAttributeDelegate = UIBBBaseAttributeSet::FBBGetAttributeDelegate;
		using FBBAttributeUpdate = UIBBBaseAttributeSet::FBBAttributeUpdate;

		virtual void Initialize(FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, FBBGetAttributeDelegate NewValueDelegate, FBBGetAttributeDelegate NewMaxValueDelegate, FBBAttributeUpdate * NewAttributeUpdate) PURE_VIRTUAL(UIBBDossierEntry::Initialize, );
		
		virtual void Finalize() PURE_VIRTUAL(UIBBDossierEntry::Finalize, );
		
		virtual FText GetEntryName() const PURE_VIRTUAL(UIBBDossierEntry::GetEntryName, return FText::FromString(""); );

		virtual TSoftObjectPtr<UTexture2D> GetIcon() const PURE_VIRTUAL(UIBBDossierEntry::GetIcon, return TSoftObjectPtr<UTexture2D>(); );

		virtual float GetValue() const PURE_VIRTUAL(UIBBDossierEntry::GetValue, return -1.0f; );

		virtual float GetMaxValue() const PURE_VIRTUAL(UIBBDossierEntry::GetMaxValue, return -1.0f; );
		
		DECLARE_EVENT_TwoParams(UIBBDossierEntry, FBBUpdate, float, float);

		FBBUpdate & OnUpdate() { return Update; };

		FORCEINLINE virtual bool operator==(const UIBBDossierEntry * Other) const
		{
			return (IsValid(Other) &&
				GetEntryName().CompareTo(Other->GetEntryName()) &&
				GetIcon() == Other->GetIcon() &&
				GetValue() == Other->GetValue() &&
				GetMaxValue() == Other->GetMaxValue());
		};

	protected:
		FBBUpdate Update;
};