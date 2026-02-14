// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/Interfaces/IBBBuildData.h"
#include "Actors/Buildings/BBBuildingStub.h"
#include "Commands/Controllers/BBOrderBuildCommandStub.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Engine/Texture2D.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBBuildEntryController.h"
#include "GUI/Data/BBBuildEntryStub.h"
#include "GUI/Models/BBBuildEntryModelStub.h"
#include "GUI/Widgets/BBBuildEntryWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBBuildEntryControllerSpec,
	"SaltLakeCity.GUI.Controllers.BuildEntry",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBBuildEntryModelStub * Model = nullptr;

	UPROPERTY()
	UBBBuildEntryWidgetStub * View = nullptr;

	UPROPERTY()
	UBBCommandFactoryStub * CommandFactory = nullptr;

	UPROPERTY()
	UBBOrderBuildCommandStub * OrderBuildCommand = nullptr;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	// SUT
	UPROPERTY()
	UBBBuildEntryController * Controller = nullptr;

END_DEFINE_SPEC(UBBBuildEntryControllerSpec)

void UBBBuildEntryControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBBuildEntryController>(FString(TEXT("/Game/GUI/Controllers")), ControllerClasses);
	
	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Model = NewObject<UBBBuildEntryModelStub>(TestWorld, UBBBuildEntryModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		View = CreateWidget<UBBBuildEntryWidgetStub>(TestWorld, UBBBuildEntryWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		CommandFactory = NewObject<UBBCommandFactoryStub>(TestWorld, UBBCommandFactoryStub::StaticClass());

		UTEST_TRUE("Command Factory is valid", IsValid(CommandFactory))

		OrderBuildCommand = NewObject<UBBOrderBuildCommandStub>(CommandFactory, UBBOrderBuildCommandStub::StaticClass());
		CommandFactory->AddOrderBuildCommand(OrderBuildCommand);

		GameInstance->SetCommandFactory(CommandFactory);

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;
		View = nullptr;
		Controller = nullptr;

		CommandFactory = nullptr;
		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ControllerClass : ControllerClasses)
	{
		Describe("["+ ControllerClass->GetName() +"]", [this, ControllerClass]()
		{
			It("Given a new entry, expect the controller to initialize the view", [this, ControllerClass]()
			{
				TArray<UIBBBuildEntry *> BuildEntries;
				BuildEntries.Empty();
				UBBBuildEntryStub * Entry = nullptr;
				UTexture2D * EntryIcon = nullptr;
				TArray<FBBBuildablePtr> Buildables;
				
				Entry = NewObject<UBBBuildEntryStub>(TestWorld, UBBBuildEntryStub::StaticClass());
				Entry->AddToRoot();
				Entry->SetEntryName(FText::FromString("SOME ENTRY"));
				EntryIcon = NewObject<UTexture2D>(TestWorld, UTexture2D::StaticClass());
				EntryIcon->AddToRoot();
				Entry->SetEntryIcon(TSoftObjectPtr<UTexture2D>(EntryIcon));
				Entry->SetEntryPrice(24.0f);
				Entry->SetEntryTime(3000.0f);
				Buildables.Empty();
				Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				Entry->SetEntryBuildables(Buildables);
				BuildEntries.Emplace(Entry);

				Entry = NewObject<UBBBuildEntryStub>(TestWorld, UBBBuildEntryStub::StaticClass());
				Entry->AddToRoot();
				Entry->SetEntryName(FText::FromString("ANOTHER ENTRY"));
				EntryIcon = NewObject<UTexture2D>(TestWorld, UTexture2D::StaticClass());
				EntryIcon->AddToRoot();
				Entry->SetEntryIcon(TSoftObjectPtr<UTexture2D>(EntryIcon));
				Entry->SetEntryPrice(10.0f);
				Entry->SetEntryTime(-105.0f);
				Buildables.Empty();
				Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				Entry->SetEntryBuildables(Buildables);
				BuildEntries.Emplace(Entry);

				Entry = NewObject<UBBBuildEntryStub>(TestWorld, UBBBuildEntryStub::StaticClass());
				Entry->AddToRoot();
				Entry->SetEntryName(FText::FromString("NUMBERS 1528142"));
				EntryIcon = NewObject<UTexture2D>(TestWorld, UTexture2D::StaticClass());
				EntryIcon->AddToRoot();
				Entry->SetEntryIcon(TSoftObjectPtr<UTexture2D>(EntryIcon));
				Entry->SetEntryPrice(-454.0f);
				Entry->SetEntryTime(523.523f);
				Buildables.Empty();
				Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				Entry->SetEntryBuildables(Buildables);
				BuildEntries.Emplace(Entry);

				Entry = NewObject<UBBBuildEntryStub>(TestWorld, UBBBuildEntryStub::StaticClass());
				Entry->AddToRoot();
				Entry->SetEntryName(FText::FromString("%28t5GB9172f!"));
				EntryIcon = NewObject<UTexture2D>(TestWorld, UTexture2D::StaticClass());
				EntryIcon->AddToRoot();
				Entry->SetEntryIcon(TSoftObjectPtr<UTexture2D>(EntryIcon));
				Entry->SetEntryPrice(12.0f);
				Entry->SetEntryTime(1.5f);
				Buildables.Empty();
				Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				Entry->SetEntryBuildables(Buildables);
				BuildEntries.Emplace(Entry);

				Entry = NewObject<UBBBuildEntryStub>(TestWorld, UBBBuildEntryStub::StaticClass());
				Entry->AddToRoot();
				Entry->SetEntryName(FText::FromString("_-_-_-___--"));
				EntryIcon = NewObject<UTexture2D>(TestWorld, UTexture2D::StaticClass());
				EntryIcon->AddToRoot();
				Entry->SetEntryIcon(TSoftObjectPtr<UTexture2D>(EntryIcon));
				Entry->SetEntryPrice(1621.0f);
				Entry->SetEntryTime(-25.0f);
				Buildables.Empty();
				Buildables.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				Entry->SetEntryBuildables(Buildables);
				BuildEntries.Emplace(Entry);

				for (UIBBBuildEntry * & BuildEntry : BuildEntries)
				{
					Model->Initialize(View, BuildEntry);

					Controller = NewObject<UBBBuildEntryController>(View, ControllerClass);

					UTEST_TRUE("Controller is valid", IsValid(Controller))

					Controller->Initialize(View, Model, CommandFactory);

					TEST_TRUE(View->GetEntryName().EqualTo(Model->GetEntryName()))
					TEST_TRUE(View->GetIcon() == Model->GetEntryIcon().LoadSynchronous())
					TEST_TRUE(View->GetPrice() == Model->GetEntryPrice())
					TEST_TRUE(View->GetTime() == Model->GetEntryTime())

					Controller->Finalize();

					Model->Finalize();
				}

				for (UIBBBuildEntry * & BuildEntry : BuildEntries)
				{
					if (IsValid(BuildEntry))
					{
						BuildEntry->GetEntryIcon().LoadSynchronous()->RemoveFromRoot();
						BuildEntry->GetEntryIcon().LoadSynchronous()->MarkAsGarbage();
						BuildEntry->RemoveFromRoot();
						BuildEntry->MarkAsGarbage();
					}
				}

				return true;
			});

			It("Given a new view, expect the controller to set the view command", [this, ControllerClass]()
			{
				Controller = NewObject<UBBBuildEntryController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, CommandFactory);

				TEST_TRUE(OrderBuildCommand->GetOuter() == View)
				TEST_TRUE(OrderBuildCommand->GetBuildDataClass() == Model->GetEntryBuildDataClass())
				TEST_TRUE(OrderBuildCommand->GetPrice() == Model->GetEntryPrice())
				TEST_TRUE(OrderBuildCommand->GetTime() == Model->GetEntryTime())
				TEST_TRUE(OrderBuildCommand->GetBuildableClasses() == Model->GetEntryBuildableClasses())

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					View->ClickEntryButton();

					TEST_TRUE(OrderBuildCommand->GetNumExecutions() == Clicks)
				}

				Controller->Finalize();

				return true;
			});
		});
	}
}