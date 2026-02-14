// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Actors/Buildings/BBBuildingStub.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "Actors/Components/BBContextComponentStub.h"
#include "Actors/Components/BBProgressComponentStub.h"
#include "Actors/Components/BBSelectionComponentStub.h"
#include "Actors/Components/BBWorkComponentStub.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/Controllers/BBPauseCommandStub.h"
#include "Commands/Controllers/BBSpeedCommandStub.h"
#include "Commands/GUI/BBCloseWidgetCommandStub.h"
#include "Commands/GUI/BBOpenWidgetCommandStub.h"
#include "Commands/Jobs/BBSetJobCommandStub.h"
#include "Commands/Metacommands/BBCompositeCommandStub.h"
#include "Controllers/BBPlayerControllerStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameModes/BBGameModeStub.h"
#include "GameStates/BBGameStateStub.h"
#include "GameStates/Components/BBGameClockStub.h"
#include "GUI/BBHUDStub.h"
#include "GUI/BBWidgetManager.h"
#include "GUI/Components/BBModelPoolStub.h"
#include "GUI/Factories/BBWidgetFactoryStub.h"
#include "GUI/Models/BBGUIModelStub.h"
#include "GUI/Models/BBContextModelStub.h"
#include "GUI/Models/BBJobModelStub.h"
#include "GUI/Models/BBSelectionModelStub.h"
#include "GUI/Widgets/BBWidgetStub.h"
#include "Specifications/GUI/BBWidgetSpecificationStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBWidgetManagerSpec,
	"SaltLakeCity.GUI.WidgetManager",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld* TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub* GameInstance = nullptr;

	UPROPERTY()
	ABBGameModeStub* GameMode = nullptr;

	UPROPERTY()
	ABBGameStateStub* GameState = nullptr;

	UPROPERTY()
	ABBHUDStub* HUD = nullptr;

	UPROPERTY()
	ABBPlayerControllerStub* PlayerController = nullptr;

	UPROPERTY()
	UBBModelPoolStub* ModelPool = nullptr;

	UPROPERTY()
	UBBGUIModelStub* Model = nullptr;

	UPROPERTY()
	UBBWidgetFactoryStub* WidgetFactory = nullptr;

	UPROPERTY()
	TArray<UClass*> WidgetManagerClasses;

	// SUT
	UPROPERTY()
	UBBWidgetManager* WidgetManager = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBWidgetManagerSpec)

void UBBWidgetManagerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBWidgetManager>(FString(TEXT("/Game/GUI")), WidgetManagerClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		GameMode = TestWorld->SpawnActor<ABBGameModeStub>(
			ABBGameModeStub::StaticClass(),
			SpawnParameters
		);

		UTEST_TRUE("Game Mode is valid", IsValid(GameMode))

		GameState = TestWorld->SpawnActor<ABBGameStateStub>(
			ABBGameStateStub::StaticClass(),
			SpawnParameters
		);

		UTEST_TRUE("Game State is valid", IsValid(GameState))

		GameState->SetGameClock(NewObject<UBBGameClockStub>(
			GameState,
			UBBGameClockStub::StaticClass()
		));

		PlayerController = TestWorld->SpawnActor<ABBPlayerControllerStub>(
			ABBPlayerControllerStub::StaticClass(),
			SpawnParameters
		);

		UTEST_TRUE("Player Controller is valid", IsValid(PlayerController))

		PlayerController->SetPlayer(GameInstance->GetFirstGamePlayer());

		ModelPool = NewObject<UBBModelPoolStub>(
			TestWorld, UBBModelPoolStub::StaticClass()
		);

		UTEST_TRUE("Model Pool is valid", IsValid(ModelPool))

		UBBGUIModelStub* Model = NewObject<UBBGUIModelStub>(
			ModelPool,
			UBBGUIModelStub::StaticClass()
		);

		UTEST_TRUE("Model is valid", IsValid(Model))

		ModelPool->SetModel(Model);
			
		WidgetFactory = NewObject<UBBWidgetFactoryStub>(
			TestWorld,
			UBBWidgetFactoryStub::StaticClass()
		);

		UTEST_TRUE("Widget Factory is valid", IsValid(WidgetFactory))

		HUD = TestWorld->SpawnActor<ABBHUDStub>(
			ABBHUDStub::StaticClass(),
			SpawnParameters
		);

		UTEST_TRUE("HUD is valid", IsValid(HUD))

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;

		WidgetFactory = nullptr;
		ModelPool = nullptr;

		PlayerController = nullptr;
		GameMode = nullptr;

		TestWorld->DestroyActor(HUD);
		TestWorld->DestroyActor(GameState);

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & WidgetManagerClass : WidgetManagerClasses)
	{
		Describe("[" + WidgetManagerClass->GetName() + "]", [this, WidgetManagerClass]()
		{
			It(
				"Given a request for an available widget, expect the widget manager to return it",
				[this, WidgetManagerClass]()
			{
				WidgetManager = NewObject<UBBWidgetManager>(GameInstance, WidgetManagerClass);

				UTEST_TRUE("Widget Manager is valid", IsValid(WidgetManager))

				WidgetManager->SetModelPool(ModelPool);
				WidgetManager->SetWidgetFactory(WidgetFactory);

				WidgetManager->Initialize(GameInstance, GameState, GameMode, HUD, PlayerController);

				UBBWidgetSpecificationStub* WidgetSpecification = NewObject<UBBWidgetSpecificationStub>(
					TestWorld,
					UBBWidgetSpecificationStub::StaticClass()
				);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				TArray<UBBWidgetStub*> Widgets;
				Widgets.Empty();
				UBBWidgetStub* NewWidget = nullptr;

				for (int Index = 0; Index < 5; Index++)
				{
					NewWidget = NewObject<UBBWidgetStub>(TestWorld, UBBWidgetStub::StaticClass());

					UTEST_TRUE("New Widget is valid", IsValid(NewWidget))

					NewWidget->NativeOnInitialized();
					Widgets.Emplace(NewWidget);
				}

				for (int Index = 0; Index < 5; Index++)
				{
					Model->SetWidget(Widgets[Index]);

					UIBBWidget* Widget = WidgetManager->GetWidget(WidgetSpecification);

					TEST_TRUE(IsValid(Widget))
					TEST_TRUE(Widget == Widgets[Index])
				}

				WidgetManager->Finalize();

				return true;
			});

			It(
				"Given a request for an unavailable widget, expect the widget manager to return a new one",
				[this, WidgetManagerClass]()
			{
				WidgetManager = NewObject<UBBWidgetManager>(GameInstance, WidgetManagerClass);

				UTEST_TRUE("Widget Manager is valid", IsValid(WidgetManager))

				WidgetManager->SetModelPool(ModelPool);
				WidgetManager->SetWidgetFactory(WidgetFactory);

				WidgetManager->Initialize(GameInstance, GameState, GameMode, HUD, PlayerController);

				UBBWidgetSpecificationStub* WidgetSpecification = NewObject<UBBWidgetSpecificationStub>(
					TestWorld,
					UBBWidgetSpecificationStub::StaticClass()
				);

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				for (int Index = 0; Index < 5; Index++)
				{
					UIBBWidget* Widget = NewObject<UBBWidgetStub>(TestWorld, UBBWidgetStub::StaticClass());

					UTEST_TRUE("Widget is valid", IsValid(Widget))

					Widget->NativeOnInitialized();

					WidgetFactory->AddWidget(Widget);

					Model->SetWidget(nullptr);

					UIBBWidget* ReturnedWidget = WidgetManager->GetWidget(WidgetSpecification);

					TEST_TRUE(IsValid(ReturnedWidget))
					TEST_TRUE(ReturnedWidget == Widget)
				}

				WidgetManager->Finalize();

				return true;
			});
		});
	}
}