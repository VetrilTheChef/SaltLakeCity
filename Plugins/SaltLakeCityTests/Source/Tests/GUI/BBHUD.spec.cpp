// SaltLakeCity 4.27

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
#include "GUI/BBHUD.h"
#include "GUI/Components/BBModelPoolStub.h"
#include "GUI/Factories/BBWidgetFactoryStub.h"
#include "GUI/Models/BBGUIModelStub.h"
#include "GUI/Models/BBContextModelStub.h"
#include "GUI/Models/BBJobModelStub.h"
#include "GUI/Models/BBSelectionModelStub.h"
#include "GUI/Widgets/BBWidgetStub.h"
#include "Specifications/GUI/BBWidgetSpecificationStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(ABBHUDSpec, "SaltLakeCity.GUI.HUD", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBGameModeStub * GameMode = nullptr;

	UPROPERTY()
	ABBGameStateStub * GameState = nullptr;

	UPROPERTY()
	ABBPlayerControllerStub * PlayerController = nullptr;

	UPROPERTY()
	UBBCommandFactoryStub * CommandFactory = nullptr;

	UPROPERTY()
	UBBModelPoolStub * ModelPool = nullptr;

	UPROPERTY()
	UBBWidgetFactoryStub * WidgetFactory = nullptr;

	UPROPERTY()
	TArray<UClass *> HUDClasses;

	// SUT
	UPROPERTY()
	ABBHUD * HUD = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(ABBHUDSpec)

void ABBHUDSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBHUD>(FString(TEXT("/Game/GUI")), HUDClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		//GameMode = TestWorld->GetAuthGameMode<ABBGameModeStub>();
		GameMode = TestWorld->SpawnActor<ABBGameModeStub>(ABBGameModeStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Game Mode is valid", IsValid(GameMode))

		//GameState = TestWorld->GetGameState<ABBGameStateStub>();
		GameState = TestWorld->SpawnActor<ABBGameStateStub>(ABBGameStateStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Game State is valid", IsValid(GameState))

		GameState->SetGameClock(NewObject<UBBGameClockStub>(GameState, UBBGameClockStub::StaticClass()));

		//TestWorld->GetFirstPlayerController<ABBPlayerControllerStub>();
		PlayerController = TestWorld->SpawnActor<ABBPlayerControllerStub>(ABBPlayerControllerStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Player Controller is valid", IsValid(PlayerController))

		PlayerController->SetPlayer(GameInstance->GetFirstGamePlayer());

		CommandFactory = NewObject<UBBCommandFactoryStub>(GameInstance, UBBCommandFactoryStub::StaticClass());

		UTEST_TRUE("Command Factory is valid", IsValid(CommandFactory))

		CommandFactory->AddPauseCommand(NewObject<UBBPauseCommandStub>(CommandFactory, UBBPauseCommandStub::StaticClass()));
		CommandFactory->AddSpeedCommand(NewObject<UBBSpeedCommandStub>(CommandFactory, UBBSpeedCommandStub::StaticClass()));
		CommandFactory->AddSpeedCommand(NewObject<UBBSpeedCommandStub>(CommandFactory, UBBSpeedCommandStub::StaticClass()));
		CommandFactory->AddSpeedCommand(NewObject<UBBSpeedCommandStub>(CommandFactory, UBBSpeedCommandStub::StaticClass()));
		CommandFactory->AddCompositeCommand(NewObject<UBBCompositeCommandStub>(CommandFactory, UBBCompositeCommandStub::StaticClass()));
		CommandFactory->AddSetJobCommand(NewObject<UBBSetJobCommandStub>(CommandFactory, UBBSetJobCommandStub::StaticClass()));
		CommandFactory->AddCloseWidgetCommand(NewObject<UBBCloseWidgetCommandStub>(CommandFactory, UBBCloseWidgetCommandStub::StaticClass()));
		CommandFactory->AddCloseWidgetCommand(NewObject<UBBCloseWidgetCommandStub>(CommandFactory, UBBCloseWidgetCommandStub::StaticClass()));
		CommandFactory->AddOpenWidgetCommand(NewObject<UBBOpenWidgetCommandStub>(CommandFactory, UBBOpenWidgetCommandStub::StaticClass()));
		CommandFactory->AddOpenWidgetCommand(NewObject<UBBOpenWidgetCommandStub>(CommandFactory, UBBOpenWidgetCommandStub::StaticClass()));
		CommandFactory->AddOpenWidgetCommand(NewObject<UBBOpenWidgetCommandStub>(CommandFactory, UBBOpenWidgetCommandStub::StaticClass()));
		CommandFactory->AddOpenWidgetCommand(NewObject<UBBOpenWidgetCommandStub>(CommandFactory, UBBOpenWidgetCommandStub::StaticClass()));

		ModelPool = NewObject<UBBModelPoolStub>(TestWorld, UBBModelPoolStub::StaticClass());

		UTEST_TRUE("Model Pool is valid", IsValid(ModelPool))

		WidgetFactory = NewObject<UBBWidgetFactoryStub>(TestWorld, UBBWidgetFactoryStub::StaticClass());

		UTEST_TRUE("Widget Factory is valid", IsValid(WidgetFactory))

		GameInstance->SetCommandFactory(CommandFactory);

		return true;
	});

	AfterEach([this]()
	{
		ModelPool = nullptr;
		WidgetFactory = nullptr;

		PlayerController = nullptr;
		//GameState = nullptr;
		GameMode = nullptr;

		//TestWorld->DestroyActor(PlayerController);
		TestWorld->DestroyActor(GameState);
		//TestWorld->DestroyActor(GameMode);

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & HUDClass : HUDClasses)
	{
		Describe("[" + HUDClass->GetName() + "]", [this, HUDClass]()
		{
			It("Given an open widget request for a widget that exists, expect the HUD to open it", [this, HUDClass]()
			{
				HUD = TestWorld->SpawnActor<ABBHUD>(HUDClass, SpawnParameters);

				UTEST_TRUE("HUD is valid", IsValid(HUD))

				HUD->Initialize(GameInstance, GameMode, GameState, PlayerController);

				UBBWidgetSpecificationStub * WidgetSpecification = NewObject<UBBWidgetSpecificationStub>(TestWorld, UBBWidgetSpecificationStub::StaticClass());

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				TArray<UBBWidgetStub *> Widgets;
				Widgets.Empty();
				UBBWidgetStub * Widget = nullptr;

				for (int Index = 0; Index < 5; Index++)
				{
					Widget = NewObject<UBBWidgetStub>(TestWorld, UBBWidgetStub::StaticClass());

					UTEST_TRUE("Widget is valid", IsValid(Widget))

					Widget->NativeOnInitialized();
					Widgets.Emplace(Widget);
				}

				UBBGUIModelStub * Model = NewObject<UBBGUIModelStub>(ModelPool, UBBGUIModelStub::StaticClass());

				UTEST_TRUE("Model is valid", IsValid(Model))

				ModelPool->SetModel(Model);

				HUD->SetModelPool(ModelPool);
				HUD->SetWidgetFactory(WidgetFactory);

				for (int Index = 0; Index < 5; Index++)
				{
					Model->SetWidget(Widgets[Index]);

					TEST_FALSE(Widgets[Index]->IsInViewport())

					HUD->OpenWidget(WidgetSpecification, false);

					TEST_TRUE(Widgets[Index]->IsInViewport())
				}

				HUD->Finalize();

				TestWorld->DestroyActor(HUD);

				return true;
			});

			It("Given an open widget request for a widget that does not exist, expect the HUD to create it and open it", [this, HUDClass]()
			{
				HUD = TestWorld->SpawnActor<ABBHUD>(HUDClass, SpawnParameters);

				UTEST_TRUE("HUD is valid", IsValid(HUD))

				HUD->Initialize(GameInstance, GameMode, GameState, PlayerController);

				UBBWidgetSpecificationStub * WidgetSpecification = NewObject<UBBWidgetSpecificationStub>(TestWorld, UBBWidgetSpecificationStub::StaticClass());

				UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

				ModelPool->SetModel(nullptr);

				HUD->SetModelPool(ModelPool);
				HUD->SetWidgetFactory(WidgetFactory);

				for (int Requests = 0; Requests < 5; Requests++)
				{
					UBBWidgetStub * NewWidget = NewObject<UBBWidgetStub>(WidgetFactory, UBBWidgetStub::StaticClass());

					WidgetSpecification->SetWidget(NewWidget);

					TEST_FALSE(NewWidget->IsInViewport())

					HUD->OpenWidget(WidgetSpecification, false);

					TEST_TRUE(NewWidget->IsInViewport())

					NewWidget->SetIsInViewport(false);
				}

				HUD->Finalize();

				TestWorld->DestroyActor(HUD);

				return true;
			});

			It("Given a new contextualizable, expect the HUD to broadcast its context component", [this, HUDClass]()
			{
				HUD = TestWorld->SpawnActor<ABBHUD>(HUDClass, SpawnParameters);

				UTEST_TRUE("HUD is valid", IsValid(HUD))

				HUD->Initialize(GameInstance, GameMode, GameState, PlayerController);

				UBBContextModelStub * ContextModel = NewObject<UBBContextModelStub>(HUD, UBBContextModelStub::StaticClass());

				UTEST_TRUE("Context Model is valid", IsValid(ContextModel))

				ContextModel->Initialize(nullptr, HUD, nullptr);

				UTEST_TRUE("Context Component is null", ContextModel->GetComponent() == nullptr)

				for (int Index = 0; Index < 5; Index++)
				{
					ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters);

					UTEST_TRUE("Character is valid", IsValid(Character))

					UIBBContextComponent * ContextComponent = NewObject<UIBBContextComponent>(Character, UBBContextComponentStub::StaticClass());

					UTEST_TRUE("Context Component is valid", IsValid(ContextComponent))

					Character->SetContextComponent(ContextComponent);

					ContextComponent->Initialize(TScriptInterface<IBBContextualizable>(Character));

					GameState->SetContext(TScriptInterface<IBBContextualizable>(Character));

					TEST_TRUE(ContextModel->GetComponent() == ContextComponent)

					ContextComponent->Finalize();
					TestWorld->DestroyActor(Character);
				}

				ContextModel->Finalize();

				HUD->Finalize();

				TestWorld->DestroyActor(HUD);

				return true;
			});

			It("Given a new selectable, expect the HUD to broadcast its selection component", [this, HUDClass]()
			{
				HUD = TestWorld->SpawnActor<ABBHUD>(HUDClass, SpawnParameters);

				UTEST_TRUE("HUD is valid", IsValid(HUD))

				HUD->Initialize(GameInstance, GameMode, GameState, PlayerController);

				UBBSelectionModelStub * SelectionModel = NewObject<UBBSelectionModelStub>(HUD, UBBSelectionModelStub::StaticClass());

				UTEST_TRUE("Selection Model is valid", IsValid(SelectionModel))

				SelectionModel->Initialize(nullptr, HUD);

				UTEST_TRUE("Selection Component is null", SelectionModel->GetComponent() == nullptr)

				for (int Index = 0; Index < 5; Index++)
				{
					ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters);

					UTEST_TRUE("Character is valid", IsValid(Character))

					UIBBSelectionComponent * SelectionComponent = NewObject<UIBBSelectionComponent>(Character, UBBSelectionComponentStub::StaticClass());

					UTEST_TRUE("Selection Component is valid", IsValid(SelectionComponent))

					Character->SetSelectionComponent(SelectionComponent);

					SelectionComponent->Initialize(TScriptInterface<IBBSelectable>(Character));

					GameState->SetSelection(TScriptInterface<IBBSelectable>(Character));

					TEST_TRUE(SelectionModel->GetComponent() == SelectionComponent)

					SelectionComponent->Finalize();
					TestWorld->DestroyActor(Character);
				}

				SelectionModel->Finalize();

				HUD->Finalize();

				TestWorld->DestroyActor(HUD);

				return true;
			});
		});
	}
}