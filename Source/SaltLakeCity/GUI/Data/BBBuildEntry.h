// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Data/Interfaces/IBBBuildEntry.h"
#include "BBBuildEntry.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBBuildEntry : public UIBBBuildEntry
{
	GENERATED_BODY()

	public:
		UBBBuildEntry();

		virtual const FText GetEntryName() const override;

		virtual void SetEntryName(const FText NewName) override;

		virtual const TSoftObjectPtr<UTexture2D> GetEntryIcon() const override;

		virtual void SetEntryIcon(const TSoftObjectPtr<UTexture2D> NewIcon) override;

		virtual const float GetEntryPrice() const override;

		virtual void SetEntryPrice(const float NewPrice) override;

		virtual const float GetEntryTime() const override;

		virtual void SetEntryTime(const float NewTime) override;

		virtual const TArray<FBBBuildablePtr> GetEntryBuildables() const override;

		virtual void SetEntryBuildables(const TArray<FBBBuildablePtr> NewBuildables) override;

		virtual const TSoftClassPtr<UIBBBuildData> GetEntryBuildDataClass() const override;

		virtual void SetEntryBuildDataClass(const TSoftClassPtr<UIBBBuildData> NewBuildDataClass) override;

	protected:
		UPROPERTY(Category = "Build Data", EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TSoftClassPtr<UIBBBuildData> BuildDataClass;

		UPROPERTY()
		TSoftObjectPtr<UTexture2D> Icon;

		UPROPERTY()
		TArray<FBBBuildablePtr> Buildables;

		FText Name;

		float Price;

		float Time;
};