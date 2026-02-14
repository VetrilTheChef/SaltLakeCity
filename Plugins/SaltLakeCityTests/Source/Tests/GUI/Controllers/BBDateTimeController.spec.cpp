// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/Controllers/BBPauseCommandStub.h"
#include "Commands/Controllers/BBSpeedCommandStub.h"
#include "Engine/Blueprint.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBDateTimeController.h"
#include "GUI/Models/BBDateTimeModelStub.h"
#include "GUI/Models/Interfaces/IBBDateTimeModel.h"
#include "GUI/Widgets/BBDateTimeWidgetStub.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBDateTimeControllerSpec,
	"SaltLakeCity.GUI.Controllers.DateTime",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBDateTimeModelStub * Model = nullptr;

	UPROPERTY()
	UBBDateTimeWidgetStub * View = nullptr;

	UPROPERTY()
	UBBCommandFactoryStub * CommandFactory = nullptr;

	UPROPERTY()
	UBBPauseCommandStub * PauseCommand = nullptr;

	UPROPERTY()
	UBBSpeedCommandStub * SlowMotionCommand = nullptr;

	UPROPERTY()
	UBBSpeedCommandStub * PlayCommand = nullptr;

	UPROPERTY()
	UBBSpeedCommandStub * FastForwardCommand = nullptr;

	UPROPERTY()
	TArray<FText> Dates;

	UPROPERTY()
	TArray<FText> Times;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	// SUT
	UPROPERTY()
	UBBDateTimeController * Controller = nullptr;

END_DEFINE_SPEC(UBBDateTimeControllerSpec)

void UBBDateTimeControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDateTimeController>(FString(TEXT("/Game/GUI/Controllers")), ControllerClasses);

	Dates.Empty();
	Dates.Emplace(FText::FromString(""));
	Dates.Emplace(FText::FromString("15-01-71"));
	Dates.Emplace(FText::FromString("30-12-20"));
	Dates.Emplace(FText::FromString("00000000"));
	Dates.Emplace(FText::FromString("A(%Y-)(!"));

	Times.Empty();
	Times.Emplace(FText::FromString(""));
	Times.Emplace(FText::FromString("23:59"));
	Times.Emplace(FText::FromString("10:04"));
	Times.Emplace(FText::FromString("-0123"));
	Times.Emplace(FText::FromString("//AC%"));

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Model = NewObject<UBBDateTimeModelStub>(TestWorld, UBBDateTimeModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		View = CreateWidget<UBBDateTimeWidgetStub>(TestWorld, UBBDateTimeWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();
		Model->Initialize(View, nullptr);

		CommandFactory = NewObject<UBBCommandFactoryStub>(TestWorld, UBBCommandFactoryStub::StaticClass());

		UTEST_TRUE("Command Factory is valid", IsValid(CommandFactory))

		PauseCommand = NewObject<UBBPauseCommandStub>(CommandFactory, UBBPauseCommandStub::StaticClass());

		UTEST_TRUE("Pause Command is valid", IsValid(PauseCommand))

		SlowMotionCommand = NewObject<UBBSpeedCommandStub>(CommandFactory, UBBSpeedCommandStub::StaticClass());

		UTEST_TRUE("Slow Motion Command is valid", IsValid(SlowMotionCommand))

		PlayCommand = NewObject<UBBSpeedCommandStub>(CommandFactory, UBBSpeedCommandStub::StaticClass());

		UTEST_TRUE("Play Command is valid", IsValid(PlayCommand))

		FastForwardCommand = NewObject<UBBSpeedCommandStub>(CommandFactory, UBBSpeedCommandStub::StaticClass());

		UTEST_TRUE("Fast Forward Command is valid", IsValid(FastForwardCommand))

		CommandFactory->AddPauseCommand(PauseCommand);
		CommandFactory->AddSpeedCommand(SlowMotionCommand);
		CommandFactory->AddSpeedCommand(PlayCommand);
		CommandFactory->AddSpeedCommand(FastForwardCommand);

		GameInstance->SetCommandFactory(CommandFactory);

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;
		View = nullptr;
		
		PauseCommand = nullptr;
		SlowMotionCommand = nullptr;
		PlayCommand = nullptr;
		FastForwardCommand = nullptr;
		CommandFactory = nullptr;

		Controller = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ControllerClass : ControllerClasses)
	{
		Describe("[" + ControllerClass->GetName() + "]", [this, ControllerClass]()
		{
			It("Given a new view, expect the controller to set the view commands", [this, ControllerClass]()
			{
				Controller = NewObject<UBBDateTimeController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, CommandFactory);

				TEST_TRUE(SlowMotionCommand->GetTimeDilation() == Controller->GetSlowMotionTimeDilation())
				TEST_TRUE(PlayCommand->GetTimeDilation() == Controller->GetPlayTimeDilation())
				TEST_TRUE(FastForwardCommand->GetTimeDilation() == Controller->GetFastForwardTimeDilation())

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					View->ClickPauseButton();

					TEST_TRUE(PauseCommand->GetNumExecutions() == Clicks)

					View->ClickSlowMotionButton();

					TEST_TRUE(SlowMotionCommand->GetNumExecutions() == Clicks)

					View->ClickPlayButton();

					TEST_TRUE(PlayCommand->GetNumExecutions() == Clicks)

					View->ClickFastForwardButton();

					TEST_TRUE(FastForwardCommand->GetNumExecutions() == Clicks)
				}

				Controller->Finalize();

				return true;
			});

			It("Given a view to be finalized, expect the controller to destroy the view", [this, ControllerClass]()
			{
				Controller = NewObject<UBBDateTimeController>(View, ControllerClass);

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