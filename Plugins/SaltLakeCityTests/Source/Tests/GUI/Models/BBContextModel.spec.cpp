// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBHUDStub.h"
#include "GUI/Controllers/BBContextControllerStub.h"
#include "GUI/Data/BBContextRow.h"
#include "GUI/Models/BBContextModel.h"
#include "GUI/Widgets/BBContextWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBContextModelSpec,
	"SaltLakeCity.GUI.Models.Context",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBHUDStub * HUD = nullptr;

	UPROPERTY()
	UBBContextControllerStub * Controller = nullptr;

	UPROPERTY()
	UBBContextWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<UDataTable *> DataTables;

	UPROPERTY()
	TArray<UClass *> ModelClasses;

	// SUT
	UPROPERTY()
	UBBContextModel * Model = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBContextModelSpec)

void UBBContextModelSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBContextModel>(FString(TEXT("/Game/GUI/Models")), ModelClasses);

	UBBTestUtil::GetTestAssets<UDataTable>(FString(TEXT("/SaltLakeCityTests/GUI/Data/ContextMenu")), DataTables);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		HUD = TestWorld->SpawnActor<ABBHUDStub>(ABBHUDStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("HUD is valid", IsValid(HUD))

		GameInstance->SetHUD(HUD);

		View = CreateWidget<UBBContextWidgetStub>(TestWorld, UBBContextWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		Controller = NewObject<UBBContextControllerStub>(TestWorld, UBBContextControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;
		View = nullptr;
		Controller = nullptr;

		GameInstance = nullptr;

		TestWorld->DestroyActor(HUD);

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ModelClass : ModelClasses)
	{
		Describe("["+ModelClass->GetName()+"]", [this, ModelClass]()
		{
			It("Given a new data table, expect the model to load data from the data table", [this, ModelClass]()
			{
				for (UDataTable * & DataTable : DataTables)
				{
					Model = NewObject<UBBContextModel>(Controller, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, HUD, DataTable);

					TEST_TRUE(Model->GetNumRows() == DataTable->GetRowNames().Num())

					int Index = 0;

					for (auto & Iterator : DataTable->GetRowMap())
					{
						FBBContextRow * Row = (FBBContextRow *)Iterator.Value;

						UTEST_TRUE("Row is not null", Row != nullptr)

						FBBContextRowData RowData = Model->GetRowData(Index);

						TEST_TRUE(RowData.Specification == Row->Specification.LoadSynchronous())
						TEST_TRUE(RowData.Name.EqualTo(Row->Name))
						TEST_TRUE(RowData.Icon == Row->Icon.LoadSynchronous())
						TEST_TRUE(RowData.Tooltip.EqualTo(Row->Tooltip))
						TEST_TRUE(RowData.ContextType == Row->ContextType)
						TEST_TRUE(RowData.WidgetToOpen == Row->WidgetToOpen)

						Index++;
					}

					Model->Finalize();
				}

				return true;
			});

			It("Given a data table to be unbound, expect the model to unload all data", [this, ModelClass]()
			{
				for (UDataTable * & DataTable : DataTables)
				{
					Model = NewObject<UBBContextModel>(Controller, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, HUD, DataTable);
					Model->Finalize();

					TEST_TRUE(Model->GetNumRows() == 0)
				}

				return true;
			});
		});
	}
}