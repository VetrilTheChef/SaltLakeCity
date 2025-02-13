// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Commands/GameModes/BBGameModeCommandStub.h"
#include "GUI/Components/Interfaces/IBBRadioBox.h"
#include "GUI/Controllers/BBModesControllerStub.h"
#include "GUI/Models/BBModesModelStub.h"
#include "GUI/Widgets/BBModesWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBModesWidgetSpec, "SaltLakeCity.GUI.Widgets.Modes", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBModesModelStub * Model = nullptr;

	UPROPERTY()
	UBBModesControllerStub * Controller = nullptr;

	UPROPERTY()
	UBBGameModeCommandStub * BuildModeCommand = nullptr;

	UPROPERTY()
	UBBGameModeCommandStub * PlayModeCommand = nullptr;

	UPROPERTY()
	TArray<UClass *> ViewClasses;

	// SUT
	UPROPERTY()
	UBBModesWidget * View = nullptr;

END_DEFINE_SPEC(UBBModesWidgetSpec)

void UBBModesWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBModesWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		Model = NewObject<UBBModesModelStub>(TestWorld, UBBModesModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		Controller = NewObject<UBBModesControllerStub>(TestWorld, UBBModesControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		BuildModeCommand = NewObject<UBBGameModeCommandStub>(Controller, UBBGameModeCommandStub::StaticClass());

		UTEST_TRUE("Build Mode Command is valid", IsValid(BuildModeCommand))

		PlayModeCommand = NewObject<UBBGameModeCommandStub>(Controller, UBBGameModeCommandStub::StaticClass());

		UTEST_TRUE("Play Mode Command is valid", IsValid(PlayModeCommand))

		Controller->SetViewCommands(BuildModeCommand, PlayModeCommand);

		return true;
	});

	AfterEach([this]()
	{
		PlayModeCommand = nullptr;
		BuildModeCommand = nullptr;

		Controller = nullptr;
		Model = nullptr;

		View = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ViewClass : ViewClasses)
	{
		Describe("[" + ViewClass->GetName() + "]", [this, ViewClass]()
		{
			It("Given a new play mode command, expect the view to execute it when the play mode button is clicked", [this, ViewClass]()
			{
				View = CreateWidget<UBBModesWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, Model, nullptr);

				UIBBRadioBox * PlayModeButton = Cast<UIBBRadioBox>(View->WidgetTree->FindWidget(TEXT("PlayButton")));

				UTEST_TRUE("Play Mode Button is valid", IsValid(PlayModeButton))

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					PlayModeButton->OnCheckStateChanged.Broadcast(true);

					TEST_TRUE(PlayModeCommand->GetNumExecutions() == Clicks)
				}

				Controller->Finalize();

				return true;
			});

			It("Given a new build mode command, expect the view to execute it when the build mode button is clicked", [this, ViewClass]()
			{
				View = CreateWidget<UBBModesWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))

				Controller->Initialize(View, Model, nullptr);

				UIBBRadioBox * BuildModeButton = Cast<UIBBRadioBox>(View->WidgetTree->FindWidget(TEXT("BuildButton")));

				UTEST_TRUE("Build Button is valid", IsValid(BuildModeButton))

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					BuildModeButton->OnCheckStateChanged.Broadcast(true);

					TEST_TRUE(BuildModeCommand->GetNumExecutions() == Clicks)
				}

				Controller->Finalize();

				return true;
			});
		});
	}
}