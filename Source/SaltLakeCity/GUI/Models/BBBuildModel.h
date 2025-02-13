// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Data/BBBuildRow.h"
#include "GUI/Models/Interfaces/IBBBuildModel.h"
#include "BBBuildModel.generated.h"

/**
 * 
 */

class UDataTable;

USTRUCT(BlueprintType)

struct FBBBuildModelEntries
{
	GENERATED_BODY()

	public:
		TArray<UIBBBuildEntry *> Entries;

		FBBBuildModelEntries()
		{
			Entries.Empty();
		}
};

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBBuildModel : public UIBBBuildModel
{
	GENERATED_BODY()

	public:
		UBBBuildModel();

		virtual void PostInitProperties() override;

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual UDataTable * GetDataTable() override;

		virtual TSoftClassPtr<UIBBBuildEntry> GetEntryClass() override;

		virtual void Initialize(UIBBBuildWidget * NewView, UDataTable * Table, TSoftClassPtr<UIBBBuildEntry> NewBuildEntryClass) override;

		virtual void Finalize() override;

		virtual int GetNumEntries(EBBBuildCategory Category) override;

		virtual UIBBBuildEntry * GetEntry(EBBBuildCategory Category, int Index) override;

	protected:
		UPROPERTY(Category = "Data Table", EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UDataTable> TableAsset;

		UPROPERTY(Category = "Classes", EditAnywhere, BlueprintReadWrite)
		TSoftClassPtr<UIBBBuildEntry> BuildEntryClass;

		UPROPERTY()
		UIBBBuildWidget * View;

		UPROPERTY()
		TMap<EBBBuildCategory, FBBBuildModelEntries> EntriesMap;

		void InitializeEntries(UDataTable * Table, TSoftClassPtr<UIBBBuildEntry> NewBuildEntryClass);

		void InitializeView(UIBBBuildWidget * NewView);

		void FinalizeEntries();

		void FinalizeView();
};