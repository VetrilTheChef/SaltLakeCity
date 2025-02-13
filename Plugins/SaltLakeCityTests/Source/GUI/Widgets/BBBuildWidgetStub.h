// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBBuildCategoryEnum.h"
#include "GUI/Widgets/Interfaces/IBBBuildWidget.h"
#include "BBBuildWidgetStub.generated.h"

/**
 * 
 */

class UIBBBuildEntry;
class UIBBTitleWidget;

USTRUCT()

struct FBBBuildWidgetStubEntries
{
	GENERATED_BODY()

	public:
		TArray<UIBBBuildEntry *> Entries;

		FBBBuildWidgetStubEntries()
		{
			Entries.Empty();
		}
};

UCLASS(NotBlueprintable)

class UBBBuildWidgetStub : public UIBBBuildWidget
{
	GENERATED_BODY()

	public:
		UBBBuildWidgetStub(const FObjectInitializer & ObjectInitializer);

		virtual void NativeDestruct() override;

		virtual void NativeOnInitialized() override;

		virtual EBBWidget GetType() const override;

		virtual void AddEntry(EBBBuildCategory Category, UIBBBuildEntry * & NewEntry) override;

		virtual void ClearEntries(EBBBuildCategory Category) override;

		int GetNumEntries(EBBBuildCategory Category);

		UIBBBuildEntry * GetEntry(EBBBuildCategory Category, int Index);

	protected:
		friend class UBBBuildControllerSpec;

		UPROPERTY()
		TMap<EBBBuildCategory, FBBBuildWidgetStubEntries> EntriesMap;
};