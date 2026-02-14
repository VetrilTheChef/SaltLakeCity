// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/BBBuildDataStub.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBBuildEntryControllerStub.h"
#include "GUI/Data/BBBuildEntryStub.h"
#include "GUI/Data/Interfaces/IBBBuildEntry.h"
#include "GUI/Models/BBBuildEntryModel.h"
#include "GUI/Widgets/BBBuildEntryWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBBuildEntryModelSpec,
	"SaltLakeCity.GUI.Models.BuildEntry",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBBuildEntryControllerStub * Controller = nullptr;

	UPROPERTY()
	UBBBuildEntryWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<FText> Names;

	UPROPERTY()
	TArray<TSoftObjectPtr<UTexture2D>> Images;

	UPROPERTY()
	TArray<float> Prices;

	UPROPERTY()
	TArray<float> Times;

	UPROPERTY()
	TArray<UBBBuildEntryStub *> BuildEntries;

	UPROPERTY()
	TArray<UClass *> ModelClasses;

	// SUT
	UPROPERTY()
	UBBBuildEntryModel * Model = nullptr;

END_DEFINE_SPEC(UBBBuildEntryModelSpec)

void UBBBuildEntryModelSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBBuildEntryModel>(FString(TEXT("/Game/GUI/Models")), ModelClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Controller = NewObject<UBBBuildEntryControllerStub>(TestWorld, UBBBuildEntryControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		View = CreateWidget<UBBBuildEntryWidgetStub>(TestWorld, UBBBuildEntryWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		BuildEntries.Empty();

		UBBBuildEntryStub * Entry = nullptr;
		UTexture2D * EntryIcon = nullptr;

		TArray<FText> Names;
		Names.Empty();
		Names.Emplace(FText::FromString("SOME ENTRY"));
		Names.Emplace(FText::FromString("ANOTHER ENTRY"));
		Names.Emplace(FText::FromString("NUMBERS 1528142"));
		Names.Emplace(FText::FromString("%28t5GB9172f!"));
		Names.Emplace(FText::FromString("_-_-_-___--"));

		TArray<float> Prices;
		Prices.Empty();
		Prices.Emplace(24.0f);
		Prices.Emplace(10.0f);
		Prices.Emplace(-454.0f);
		Prices.Emplace(12.0f);
		Prices.Emplace(1621.0f);

		TArray<float> Times;
		Times.Empty();
		Times.Emplace(3000.0f);
		Times.Emplace(-105.0f);
		Times.Emplace(523.523f);
		Times.Emplace(1.5f);
		Times.Emplace(-25.0f);
		
		for (int i = 0; i < 5; i++)
		{
			Entry = NewObject<UBBBuildEntryStub>(TestWorld, UBBBuildEntryStub::StaticClass());

			UTEST_TRUE("Entry is valid", IsValid(Entry))

			Entry->AddToRoot();
			Entry->SetEntryName(Names[i]);
			EntryIcon = NewObject<UTexture2D>(TestWorld, UTexture2D::StaticClass());
			EntryIcon->AddToRoot();
			Entry->SetEntryIcon(EntryIcon);
			Entry->SetEntryPrice(Prices[i]);
			Entry->SetEntryTime(Times[i]);
			Entry->SetEntryBuildDataClass(TSoftClassPtr<UIBBBuildData>(NewObject<UBBBuildDataStub>(TestWorld, UBBBuildDataStub::StaticClass())));
			BuildEntries.Emplace(Entry);
		}

		return true;
	});

	AfterEach([this]()
	{
		for (UBBBuildEntryStub * & BuildEntry : BuildEntries)
		{
			if (IsValid(BuildEntry))
			{
				BuildEntry->GetEntryIcon().LoadSynchronous()->RemoveFromRoot();
				BuildEntry->GetEntryIcon().LoadSynchronous()->MarkAsGarbage();
				BuildEntry->RemoveFromRoot();
				BuildEntry->MarkAsGarbage();
			}

			BuildEntry = nullptr;
		}

		BuildEntries.Empty();

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
			It("Given a new build entry, expect the model to load data from it", [this, ModelClass]()
			{
				for (UBBBuildEntryStub * & BuildEntry : BuildEntries)
				{
					Model = NewObject<UBBBuildEntryModel>(Controller, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, BuildEntry);

					TEST_TRUE(Model->GetEntryName().EqualTo(BuildEntry->GetEntryName()))
					TEST_TRUE(Model->GetEntryIcon() == BuildEntry->GetEntryIcon())
					TEST_TRUE(Model->GetEntryPrice() == BuildEntry->GetEntryPrice())
					TEST_TRUE(Model->GetEntryTime() == BuildEntry->GetEntryTime())
					TEST_TRUE(Model->GetEntryBuildDataClass() == BuildEntry->GetEntryBuildDataClass())

					Model->Finalize();
				}

				return true;
			});

			It("Given a new view, expect the model to initialize it", [this, ModelClass]()
			{
				for (UBBBuildEntryStub * & BuildEntry : BuildEntries)
				{
					Model = NewObject<UBBBuildEntryModel>(Controller, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, BuildEntry);

					TEST_TRUE(Model->GetEntryName().EqualTo(BuildEntry->GetEntryName()))
					TEST_TRUE(Model->GetEntryIcon() == BuildEntry->GetEntryIcon())
					TEST_TRUE(Model->GetEntryPrice() == BuildEntry->GetEntryPrice())
					TEST_TRUE(Model->GetEntryTime() == BuildEntry->GetEntryTime())
					TEST_TRUE(Model->GetEntryBuildDataClass() == BuildEntry->GetEntryBuildDataClass())

					Model->Finalize();
				}

				return true;
			});

			It("Given a build entry to be unbound, expect the model to unload all data", [this, ModelClass]()
			{
				for (UBBBuildEntryStub * & BuildEntry : BuildEntries)
				{
					Model = NewObject<UBBBuildEntryModel>(Controller, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, BuildEntry);
					Model->Finalize();

					TEST_TRUE(Model->GetEntryName().EqualTo(FText::FromString("")))
					TEST_TRUE(Model->GetEntryIcon().LoadSynchronous() == nullptr)
					TEST_TRUE(Model->GetEntryPrice() == -1.0f)
					TEST_TRUE(Model->GetEntryTime() == -1.0f)
					TEST_TRUE(Model->GetEntryBuildDataClass().LoadSynchronous() == nullptr)
				}

				return true;
			});
		});
	}
}