// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/GameModes/BBGameModeCommandStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBModesController.h"
#include "GUI/Models/BBModesModelStub.h"
#include "GUI/Widgets/BBModesWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBModesControllerSpec, "SaltLakeCity.GUI.Controllers.Modes", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBCommandFactoryStub * CommandFactory = nullptr;

	UPROPERTY()
	UBBGameModeCommandStub * PlayModeCommand = nullptr;

	UPROPERTY()
	UBBGameModeCommandStub * BuildModeCommand = nullptr;

	UPROPERTY()
	UBBModesModelStub * Model = nullptr;

	UPROPERTY()
	UBBModesWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	// SUT
	UPROPERTY()
	UBBModesController * Controller = nullptr;

END_DEFINE_SPEC(UBBModesControllerSpec)

void UBBModesControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBModesController>(FString(TEXT("/Game/GUI/Controllers")), ControllerClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid.", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid.", IsValid(GameInstance))

		Model = NewObject<UBBModesModelStub>(TestWorld, UBBModesModelStub::StaticClass());

		UTEST_TRUE("Model is valid.", IsValid(Model))

		View = CreateWidget<UBBModesWidgetStub>(TestWorld, UBBModesWidgetStub::StaticClass());

		UTEST_TRUE("View is valid.", IsValid(View))

		View->NativeOnInitialized();

		CommandFactory = NewObject<UBBCommandFactoryStub>(TestWorld, UBBCommandFactoryStub::StaticClass());
		
		UTEST_TRUE("Command Factory is valid.", IsValid(CommandFactory))

		PlayModeCommand = NewObject<UBBGameModeCommandStub>(CommandFactory, UBBGameModeCommandStub::StaticClass());

		UTEST_TRUE("Play Mode Command is valid.", IsValid(PlayModeCommand))

		BuildModeCommand = NewObject<UBBGameModeCommandStub>(CommandFactory, UBBGameModeCommandStub::StaticClass());

		UTEST_TRUE("Build Mode Command is valid.", IsValid(BuildModeCommand))

		CommandFactory->AddGameModeCommand(PlayModeCommand);
		CommandFactory->AddGameModeCommand(BuildModeCommand);

		GameInstance->SetCommandFactory(CommandFactory);

		return true;
	});

	AfterEach([this]()
	{
		BuildModeCommand = nullptr;
		PlayModeCommand = nullptr;

		CommandFactory = nullptr;

		Model = nullptr;
		View = nullptr;
		Controller = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ControllerClass : ControllerClasses)
	{
		Describe("["+ControllerClass->GetName()+"]", [this, ControllerClass]()
		{
			It("Given a view to be initialized, expect the controller to set the view's commands", [this, ControllerClass]()
			{
				Controller = NewObject<UBBModesController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, CommandFactory);

				TEST_TRUE(View->GetPlayModeCommand() == PlayModeCommand)
				TEST_TRUE(View->GetBuildModeCommand() == BuildModeCommand)

				Controller->Finalize();

				return true;
			});

			It("Given a mode update from the model, expect the controller to update the view's active mode", [this, ControllerClass]()
			{
				Controller = NewObject<UBBModesController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				TArray<EBBGameMode> ActiveGameModes;
				ActiveGameModes.Emplace(EBBGameMode::Build);
				ActiveGameModes.Emplace(EBBGameMode::Play);
				ActiveGameModes.Emplace(EBBGameMode::None);
				ActiveGameModes.Emplace(EBBGameMode::Build);
				ActiveGameModes.Emplace(EBBGameMode::Play);

				Controller->Initialize(View, Model, CommandFactory);

				for (EBBGameMode & ActiveGameMode : ActiveGameModes)
				{
					Model->UpdateActiveGameMode(ActiveGameMode);

					TEST_TRUE(View->GetActiveMode() == ActiveGameMode)
				}

				Controller->Finalize();

				return true;
			});

			It("Given a view to be finalized, expect the controller to destroy the view", [this, ControllerClass]()
			{
				Controller = NewObject<UBBModesController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, CommandFactory);

				TEST_TRUE(IsValid(View))

				Controller->Finalize();

				TEST_FALSE(IsValid(View))

				return true;
			});
		});
	}
}