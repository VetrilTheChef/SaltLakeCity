// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/GUI/BBCloseWidgetCommandStub.h"
#include "Components/ProgressBar.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Components/Interfaces/IBBButton.h"
#include "GUI/Controllers/BBTitleControllerStub.h"
#include "GUI/Models/BBTitleModelStub.h"
#include "GUI/Widgets/BBTitleWidget.h"
#include "GUI/Widgets/BBWidgetStub.h"
#include "Specifications/GUI/BBWidgetSpecificationStub.h"
#include "Specifications/GUI/Factories/BBWidgetSpecificationFactoryStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBTitleWidgetSpec, "SaltLakeCity.GUI.Widgets.Title", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBCloseWidgetCommandStub * CloseCommand = nullptr;

	UPROPERTY()
	UBBTitleModelStub * Model = nullptr;

	UPROPERTY()
	UBBTitleControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<UClass *> ViewClasses;

	// SUT
	UPROPERTY()
	UBBTitleWidget * View = nullptr;

END_DEFINE_SPEC(UBBTitleWidgetSpec)

void UBBTitleWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBTitleWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		Model = NewObject<UBBTitleModelStub>(TestWorld, UBBTitleModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		UBBWidgetStub * ParentWidget = CreateWidget<UBBWidgetStub>(TestWorld, UBBWidgetStub::StaticClass());

		UTEST_TRUE("Parent Widget is valid", IsValid(ParentWidget))

		Model->SetParentWidget(ParentWidget);

		Controller = NewObject<UBBTitleControllerStub>(TestWorld, UBBTitleControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		CloseCommand = NewObject<UBBCloseWidgetCommandStub>(Controller, UBBCloseWidgetCommandStub::StaticClass());

		UTEST_TRUE("Close Command is valid", IsValid(CloseCommand))

		Controller->SetViewCommands(CloseCommand);

		return true;
	});

	AfterEach([this]()
	{
		CloseCommand = nullptr;

		Controller = nullptr;
		Model = nullptr;

		View = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ViewClass : ViewClasses)
	{
		Describe("[" + ViewClass->GetName() + "]", [this, ViewClass]()
		{
			It("Given a new close command, expect the view to execute it when the close button is clicked", [this, ViewClass]()
			{
				View = CreateWidget<UBBTitleWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, Model, nullptr, nullptr);

				UIBBButton * CloseButton = Cast<UIBBButton>(View->WidgetTree->FindWidget(TEXT("CloseButton")));

				UTEST_TRUE("Close Button is valid", IsValid(CloseButton))

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					CloseButton->OnClicked.Broadcast();

					TEST_TRUE(CloseCommand->GetNumExecutions() == Clicks)
				}

				return true;
			});
		});
	}
}