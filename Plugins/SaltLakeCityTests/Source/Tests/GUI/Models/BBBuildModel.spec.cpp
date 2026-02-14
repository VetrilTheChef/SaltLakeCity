// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBBuildControllerStub.h"
#include "GUI/Data/BBBuildRow.h"
#include "GUI/Data/BBBuildEntryStub.h"
#include "GUI/Data/Interfaces/IBBBuildEntry.h"
#include "GUI/Includes/BBBuildCategoryEnum.h"
#include "GUI/Models/BBBuildModel.h"
#include "GUI/Widgets/BBBuildWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBBuildModelSpec,
	"SaltLakeCity.GUI.Models.Build",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBBuildControllerStub * Controller = nullptr;

	UPROPERTY()
	UBBBuildWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<UDataTable *> DataTables;

	UPROPERTY()
	TSoftClassPtr<UIBBBuildEntry> BuildEntryClass;

	UPROPERTY()
	TArray<UClass *> ModelClasses;

	// SUT
	UPROPERTY()
	UBBBuildModel * Model = nullptr;

	void TestCategoryInitialize(EBBBuildCategory Category, UBBBuildModel * BuildModel, UDataTable * DataTable);

	void TestCategoryFinalize(EBBBuildCategory Category, UBBBuildModel * BuildModel);

END_DEFINE_SPEC(UBBBuildModelSpec)

void UBBBuildModelSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBBuildModel>(FString(TEXT("/Game/GUI/Models")), ModelClasses);

	UBBTestUtil::GetTestAssets<UDataTable>(FString(TEXT("/SaltLakeCityTests/GUI/Data/BuildMenu")), DataTables);

	BuildEntryClass = TSoftClassPtr<UIBBBuildEntry>(UBBBuildEntryStub::StaticClass());

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		View = CreateWidget<UBBBuildWidgetStub>(TestWorld, UBBBuildWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		Controller = NewObject<UBBBuildControllerStub>(TestWorld, UBBBuildControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;
		View = nullptr;
		Controller = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ModelClass : ModelClasses)
	{
		Describe("["+ ModelClass->GetName()+"]", [this, ModelClass]()
		{
			It("Given a new data table, expect the model to load data from the data table", [this, ModelClass]()
			{
				for (UDataTable * & DataTable : DataTables)
				{
					Model = NewObject<UBBBuildModel>(Controller, ModelClass);
					
					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, DataTable, BuildEntryClass);

					#define EBBBUILDCATEGORY_OPERATION(Value) TestCategoryInitialize(Value, Model, DataTable);

						FOREACH_ENUM_EBBBUILDCATEGORY(EBBBUILDCATEGORY_OPERATION)

					#undef EBBBUILDCATEGORY_OPERATION
				
					Model->Finalize();
				}

				return true;
			});

			It("Given a data table to be finalized, expect the model to unload all data", [this, ModelClass]()
			{
				for (UDataTable * & DataTable : DataTables)
				{
					Model = NewObject<UBBBuildModel>(Controller, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, DataTable, BuildEntryClass);
					Model->Finalize();

					#define EBBBUILDCATEGORY_OPERATION(Value) TestCategoryFinalize(Value, Model);

						FOREACH_ENUM_EBBBUILDCATEGORY(EBBBUILDCATEGORY_OPERATION)

					#undef EBBBUILDCATEGORY_OPERATION
				}

				return true;
			});
		});
	}
}

void UBBBuildModelSpec::TestCategoryInitialize(EBBBuildCategory Category, UBBBuildModel * BuildModel, UDataTable * DataTable)
{
	int Entries = BuildModel->GetNumEntries(Category);

	TArray<FBBBuildRow *> CategoryRows;

	CategoryRows.Empty();

	for (auto& Iterator : DataTable->GetRowMap())
	{
		FBBBuildRow * Row = (FBBBuildRow *) Iterator.Value;

		if (Row)
		{
			if (Row->Category == Category)
			{
				CategoryRows.Emplace(Row);
			}
		}
	}

	TEST_TRUE(Entries == CategoryRows.Num());

	if (CategoryRows.Num() > 0)
	{
		int Index = 0;

		for (auto& Row : CategoryRows)
		{
			if (Row)
			{
				UIBBBuildEntry * BuildEntry = BuildModel->GetEntry(Category, Index);

				TEST_TRUE(IsValid(BuildEntry));

				if (IsValid(BuildEntry))
				{
					TEST_TRUE(BuildEntry->GetEntryName().EqualTo(Row->Name))
					TEST_TRUE(BuildEntry->GetEntryIcon() == Row->Icon)
					TEST_TRUE(BuildEntry->GetEntryPrice() == Row->Price)
					TEST_TRUE(BuildEntry->GetEntryTime() == Row->Time)
					TEST_TRUE(BuildEntry->GetEntryBuildables() == Row->GetBuildables())
				}
			}

			Index++;
		}
	}
}

void UBBBuildModelSpec::TestCategoryFinalize(EBBBuildCategory Category, UBBBuildModel * BuildModel)
{
	TEST_TRUE(BuildModel->GetNumEntries(Category) == 0)
}