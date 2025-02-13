// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "Actors/Components/BBAIAbilityComponentStub.h"
#include "Actors/Components/BBWorkComponentStub.h"
#include "Engine/DataTable.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBHUDStub.h"
#include "GUI/Controllers/BBJobControllerStub.h"
#include "GUI/Data/BBJobRow.h"
#include "GUI/Models/BBJobModel.h"
#include "GUI/Widgets/BBJobWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBJobModelSpec, "SaltLakeCity.GUI.Models.Job", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBJobControllerStub * Controller = nullptr;

	UPROPERTY()
	UBBJobWidgetStub * View = nullptr;

	UPROPERTY()
	ABBHUDStub * HUD = nullptr;

	UPROPERTY()
	TArray<UDataTable *> DataTables;

	UPROPERTY()
	TArray<UClass *> ModelClasses;

	// SUT
	UPROPERTY()
	UBBJobModel * Model = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBJobModelSpec)

void UBBJobModelSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBJobModel>(FString(TEXT("/Game/GUI/Models")), ModelClasses);

	UBBTestUtil::GetTestAssets<UDataTable>(FString(TEXT("/SaltLakeCityTests/GUI/Data/JobMenu")), DataTables);

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

		View = CreateWidget<UBBJobWidgetStub>(TestWorld, UBBJobWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		Controller = NewObject<UBBJobControllerStub>(TestWorld, UBBJobControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;
		View = nullptr;
		Controller = nullptr;

		TestWorld->DestroyActor(HUD);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ModelClass : ModelClasses)
	{
		Describe("[" + ModelClass->GetName() + "]", [this, ModelClass]()
		{
			It("Given a new datatable, expect the model to load data from the datatable", [this, ModelClass]()
			{
				for (UDataTable * & DataTable : DataTables)
				{
					Model = NewObject<UBBJobModel>(Controller, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, HUD, DataTable);

					TEST_TRUE(Model->GetNumJobs() == DataTable->GetRowNames().Num())

					int Index = 0;

					for (auto & Iterator : DataTable->GetRowMap())
					{
						FBBJobRow * Row = (FBBJobRow *)Iterator.Value;

						UTEST_TRUE("Row is not null", Row != nullptr)

						TEST_TRUE(Model->GetJobName(Index).EqualTo(Row->Name))
						TEST_TRUE(Model->GetJob(Index) == Row->Job)
						TEST_TRUE(Model->GetJobTooltip(Index).EqualTo(Row->Tooltip))

						Index++;
					}

					Model->Finalize();
				}

				return true;
			});

			It("Given a datatable to be unbound, expect the model to unload all data", [this, ModelClass]()
			{
				for (UDataTable * & DataTable : DataTables)
				{
					Model = NewObject<UBBJobModel>(Controller, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, HUD, DataTable);
					Model->Finalize();

					TEST_TRUE(Model->GetNumJobs() == 0)
				}

				return true;
			});
			
			It("Given a consumer update from the HUD, expect the model to update the controller", [this, ModelClass]()
			{
				TArray<UBBWorkComponentStub *> WorkComponents;
				WorkComponents.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				WorkComponents.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				WorkComponents.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				WorkComponents.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				WorkComponents.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));

				for (UDataTable * & DataTable : DataTables)
				{
					Model = NewObject<UBBJobModel>(Controller, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, HUD, DataTable);
					Controller->Initialize(View, Model, nullptr, nullptr, nullptr);

					for (UBBWorkComponentStub * & WorkComponent : WorkComponents)
					{
						UTEST_TRUE("Work Component is valid", IsValid(WorkComponent))

						Controller->SetWorkComponent(nullptr);

						TEST_TRUE(Controller->GetWorkComponent() == nullptr)

						HUD->BroadcastConsumerUpdate(WorkComponent);

						TEST_TRUE(Controller->GetWorkComponent() == WorkComponent)
					}

					Controller->Finalize();
					Model->Finalize();
				}

				return true;
			});

			It("Given a consumer update from the unbound HUD, expect the model not to update the controller", [this, ModelClass]()
			{
				TArray<UBBWorkComponentStub *> WorkComponents;
				WorkComponents.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				WorkComponents.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				WorkComponents.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				WorkComponents.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				WorkComponents.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));

				for (UDataTable * & DataTable : DataTables)
				{
					Model = NewObject<UBBJobModel>(Controller, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, HUD, DataTable);
					Controller->Initialize(View, Model, nullptr, nullptr, nullptr);
					Model->Finalize();

					for (UBBWorkComponentStub * & WorkComponent : WorkComponents)
					{
						UTEST_TRUE("Work Component is valid", IsValid(WorkComponent))

						Controller->SetWorkComponent(nullptr);

						TEST_TRUE(Controller->GetWorkComponent() == nullptr)

						HUD->BroadcastConsumerUpdate(WorkComponent);

						TEST_TRUE(Controller->GetWorkComponent() == nullptr)
					}

					Controller->Finalize();
				}

				return true;
			});
		});
	}
}