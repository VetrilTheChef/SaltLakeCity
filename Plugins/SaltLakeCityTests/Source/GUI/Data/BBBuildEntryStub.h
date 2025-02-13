// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Includes/BBBuildCategoryEnum.h"
#include "GUI/Data/Interfaces/IBBBuildEntry.h"
#include "BBBuildEntryStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBBuildEntryStub : public UIBBBuildEntry
{
	GENERATED_BODY()

	public:
		UBBBuildEntryStub();

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

		const EBBBuildCategory GetEntryCategory() const;

		void SetEntryCategory(const EBBBuildCategory NewCategory);

	protected:
		UPROPERTY()
		FText Name;

		UPROPERTY()
		TSoftObjectPtr<UTexture2D> Icon;

		UPROPERTY()
		TArray<FBBBuildablePtr> Buildables;

		UPROPERTY()
		TSoftClassPtr<UIBBBuildData> BuildDataClass;

		float Price;

		float Time;

		EBBBuildCategory Category;
};