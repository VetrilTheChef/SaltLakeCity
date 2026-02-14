// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/Controllers/BBPauseCommandStub.h"
#include "Commands/Controllers/BBSpeedCommandStub.h"
#include "Components/TextBlock.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Components/Interfaces/IBBButton.h"
#include "GUI/Controllers/BBDateTimeControllerStub.h"
#include "GUI/Widgets/BBDateTimeWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBDateTimeWidgetSpec,
	"SaltLakeCity.GUI.Widgets.DateTime",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<FText> Dates;

	UPROPERTY()
	TArray<FText> Times;

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
	UBBDateTimeControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<UClass *> ViewClasses;

	// SUT
	UPROPERTY()
	UBBDateTimeWidget * View = nullptr;

END_DEFINE_SPEC(UBBDateTimeWidgetSpec)

void UBBDateTimeWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDateTimeWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);

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

		Controller = NewObject<UBBDateTimeControllerStub>(TestWorld, UBBDateTimeControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		GameInstance->SetCommandFactory(CommandFactory);

		return true;
	});

	AfterEach([this]()
	{
		CommandFactory = nullptr;
		PauseCommand = nullptr;
		SlowMotionCommand = nullptr;
		PlayCommand = nullptr;
		FastForwardCommand = nullptr;

		Controller = nullptr;
		View = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ViewClass : ViewClasses)
	{
		Describe("[" + ViewClass->GetName() + "]", [this, ViewClass]()
		{
			It("Given a date update from the controller, expect the view to update the date", [this, ViewClass]()
			{
				View = CreateWidget<UBBDateTimeWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr, CommandFactory);

				UTextBlock * DateText = Cast<UTextBlock>(View->WidgetTree->FindWidget(TEXT("DateText")));

				UTEST_TRUE("Date Text is valid", IsValid(DateText))

				for (FText & Date : Dates)
				{
					View->SetDate(Date);

					TEST_TRUE(DateText->GetText().EqualTo(Date))
				}

				Controller->Finalize();

				return true;
			});

			It("Given a time update from the controller, expect the view to update the time", [this, ViewClass]()
			{
				View = CreateWidget<UBBDateTimeWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr, CommandFactory);

				UTextBlock * TimeText = Cast<UTextBlock>(View->WidgetTree->FindWidget(TEXT("TimeText")));

				UTEST_TRUE("Time Text is valid", IsValid(TimeText))

				for (auto& Time : Times)
				{
					View->SetTime(Time);

					TEST_TRUE(TimeText->GetText().EqualTo(Time))
				}

				Controller->Finalize();

				return true;
			});
		});

		It("Given a new pause command, expect the view to execute it when the pause button is clicked", [this, ViewClass]()
		{
			View = CreateWidget<UBBDateTimeWidget>(TestWorld, ViewClass);

			UTEST_TRUE("View is valid", IsValid(View))
			
			Controller->Initialize(View, nullptr, CommandFactory);

			UIBBButton * PauseButton = Cast<UIBBButton>(View->WidgetTree->FindWidget(TEXT("PauseButton")));

			UTEST_TRUE("Pause Button is valid", IsValid(PauseButton))

			for (int Clicks = 1; Clicks < 6; Clicks++)
			{
				PauseButton->OnClicked.Broadcast();

				TEST_TRUE(PauseCommand->GetNumExecutions() == Clicks)
			}

			Controller->Finalize();

			return true;
		});

		It("Given a new slow motion command, expect the view to execute it when the slow motion button is clicked", [this, ViewClass]()
		{
			View = CreateWidget<UBBDateTimeWidget>(TestWorld, ViewClass);

			UTEST_TRUE("View is valid", IsValid(View))
			
			Controller->Initialize(View, nullptr, CommandFactory);

			UIBBButton * SlowMotionButton = Cast<UIBBButton>(View->WidgetTree->FindWidget(TEXT("SlowMotionButton")));

			UTEST_TRUE("Slow Motion Button is valid", IsValid(SlowMotionButton))

			for (int Clicks = 1; Clicks < 6; Clicks++)
			{
				SlowMotionButton->OnClicked.Broadcast();

				TEST_TRUE(SlowMotionCommand->GetNumExecutions() == Clicks)
			}

			Controller->Finalize();

			return true;
		});

		It("Given a new play command, expect the view to execute it when the play button is clicked", [this, ViewClass]()
		{
			View = CreateWidget<UBBDateTimeWidget>(TestWorld, ViewClass);

			UTEST_TRUE("View is valid", IsValid(View))
			
			Controller->Initialize(View, nullptr, CommandFactory);

			UIBBButton * PlayButton = Cast<UIBBButton>(View->WidgetTree->FindWidget(TEXT("PlayButton")));

			UTEST_TRUE("Play Button is valid", IsValid(PlayButton))

			for (int Clicks = 1; Clicks < 6; Clicks++)
			{
				PlayButton->OnClicked.Broadcast();

				TEST_TRUE(PlayCommand->GetNumExecutions() == Clicks)
			}

			Controller->Finalize();

			return true;
		});

		It("Given a new fast forward command, expect the view to execute it when the fast forward button is clicked", [this, ViewClass]()
		{
			View = CreateWidget<UBBDateTimeWidget>(TestWorld, ViewClass);

			UTEST_TRUE("View is valid", IsValid(View))
			
			Controller->Initialize(View, nullptr, CommandFactory);

			UIBBButton * FastForwardButton = Cast<UIBBButton>(View->WidgetTree->FindWidget(TEXT("FastForwardButton")));

			UTEST_TRUE("Fast Forward Button is valid", IsValid(FastForwardButton))

			for (int Clicks = 1; Clicks < 6; Clicks++)
			{
				FastForwardButton->OnClicked.Broadcast();

				TEST_TRUE(FastForwardCommand->GetNumExecutions() == Clicks)
			}

			Controller->Finalize();

			return true;
		});
	}
}