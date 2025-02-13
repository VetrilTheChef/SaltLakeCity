// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "UObject/NoExportTypes.h"
#include "IBBBuildEntry.generated.h"

/**
 * 
 */

class UIBBBuildData;
class UTexture2D;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBuildEntry : public UObject
{
	GENERATED_BODY()

	public:
		UIBBBuildEntry() : Super() { };

		virtual const FText GetEntryName() const PURE_VIRTUAL(UIBBBuildEntry::GetEntryName, return FText::FromString(""); );

		virtual void SetEntryName(const FText NewName) PURE_VIRTUAL(UIBBBuildEntry::SetEntryName, );

		virtual const TSoftObjectPtr<UTexture2D> GetEntryIcon() const PURE_VIRTUAL(UIBBBuildEntry::GetEntryIcon, return TSoftObjectPtr<UTexture2D>(); );

		virtual void SetEntryIcon(const TSoftObjectPtr<UTexture2D> NewIcon) PURE_VIRTUAL(UIBBBuildEntry::SetEntryIcon, );

		virtual const float GetEntryPrice() const PURE_VIRTUAL(UIBBBuildEntry::GetEntryPrice, return -1.0f; );

		virtual void SetEntryPrice(const float NewPrice) PURE_VIRTUAL(UIBBBuildEntry::SetEntryPrice, );

		virtual const float GetEntryTime() const PURE_VIRTUAL(UIBBBuildEntry::GetEntryTime, return -1.0f; );

		virtual void SetEntryTime(const float NewTime) PURE_VIRTUAL(UIBBBuildEntry::SetEntryTime, );

		virtual const TArray<FBBBuildablePtr> GetEntryBuildables() const PURE_VIRTUAL(UIBBBuildEntry::GetEntryBuildables, return TArray<FBBBuildablePtr>(); );

		virtual void SetEntryBuildables(const TArray<FBBBuildablePtr> NewBuildables) PURE_VIRTUAL(UIBBBuildEntry::SetEntryBuildables, );

		virtual const TSoftClassPtr<UIBBBuildData> GetEntryBuildDataClass() const PURE_VIRTUAL(UIBBBuildEntry::GetEntryBuildDataClass, return TSoftClassPtr<UIBBBuildData>(); );

		virtual void SetEntryBuildDataClass(const TSoftClassPtr<UIBBBuildData> NewBuildDataClass) PURE_VIRTUAL(UIBBBuildEntry::SetEntryBuildDataClass, );
};