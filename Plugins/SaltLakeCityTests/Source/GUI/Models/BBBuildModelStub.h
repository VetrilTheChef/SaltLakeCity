// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "GUI/Models/Interfaces/IBBBuildModel.h"
#include "BBBuildModelStub.generated.h"

/**
 * 
 */

class UDataTable;
class UIBBBuildEntry;
class UIBBBuildWidget;
class UIBBWidget;

USTRUCT()

struct FBBBuildModelStubEntries
{
	GENERATED_BODY()

	public:
		TArray<UIBBBuildEntry *> Entries;

		FBBBuildModelStubEntries()
		{
			Entries.Empty();
		}
};

UCLASS(NotBlueprintable)

class UBBBuildModelStub : public UIBBBuildModel
{
	GENERATED_BODY()

	public:
		UBBBuildModelStub();

		virtual void PostInitProperties() override;

		virtual UIBBWidget * GetWidget() const override;

		virtual UDataTable * GetDataTable() override;

		virtual TSoftClassPtr<UIBBBuildEntry> GetEntryClass() override;

		virtual void Initialize(UIBBBuildWidget * NewView, UDataTable * Table, TSoftClassPtr<UIBBBuildEntry> NewBuildEntryClass) override;

		virtual void Finalize() override;

		virtual int GetNumEntries(EBBBuildCategory Category) override;
		
		int AddEntry(EBBBuildCategory Category, FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, float NewPrice, float NewTime, TArray<FBBBuildablePtr> NewBuildables);

		virtual UIBBBuildEntry * GetEntry(EBBBuildCategory Category, int Index) override;

	protected:
		UPROPERTY()
		UIBBBuildWidget * View;

		UPROPERTY()
		TMap<EBBBuildCategory, FBBBuildModelStubEntries> EntriesMap;
};