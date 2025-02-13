// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "Commands/Controllers/BBPauseCommandStub.h"
#include "Components/VerticalBox.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBContextControllerStub.h"
#include "GUI/Widgets/BBContextRowWidgetStub.h"
#include "GUI/Widgets/BBContextWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBContextWidgetSpec, "SaltLakeCity.GUI.Widgets.Context", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UBBContextRowWidgetStub *> RowWidgets;

	UPROPERTY()
	UBBContextControllerStub * Controller;

	UPROPERTY()
	TArray<UClass *> ViewClasses;

	// SUT
	UPROPERTY()
	UBBContextWidget * View;

END_DEFINE_SPEC(UBBContextWidgetSpec)

void UBBContextWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBContextWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		RowWidgets.Empty();

		for (int i = 0; i < 5; i++)
		{
			UBBContextRowWidgetStub * RowWidget = CreateWidget<UBBContextRowWidgetStub>(TestWorld, UBBContextRowWidgetStub::StaticClass());

			UTEST_TRUE("Row Widget is valid", IsValid(RowWidget))
				
			RowWidget->NativeOnInitialized();

			UBBPauseCommandStub * RowCommand = NewObject<UBBPauseCommandStub>(RowWidget, UBBPauseCommandStub::StaticClass());

			UTEST_TRUE("Row Command is valid", IsValid(RowCommand))

			RowWidget->SetCommand(RowCommand);

			RowWidgets.Emplace(RowWidget);
		}

		Controller = NewObject<UBBContextControllerStub>(TestWorld, UBBContextControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		return true;
	});

	AfterEach([this]()
	{
		/*for (UBBContextRowWidgetStub * & RowWidget : RowWidgets)
		{
			RowWidget->RemoveFromRoot();
			RowWidget->MarkPendingKill();
			RowWidget = nullptr;
		}*/

		RowWidgets.Empty();

		Controller = nullptr;
		View = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ViewClass : ViewClasses)
	{
		Describe("[" + ViewClass->GetName() + "]", [this, ViewClass]()
		{
			It("Given a new mouse leave event, expect the controller to close the view", [this, ViewClass]()
			{
				View = CreateWidget<UBBContextWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr, nullptr, nullptr);

				FPointerEvent MouseEvent = FPointerEvent();

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					View->OnMouseLeave().Broadcast(MouseEvent);

					TEST_TRUE(Controller->GetNumMouseLeaveExecutions() == Clicks)
				}

				Controller->Finalize();

				return true;
			});

			It("Given a new row click event, expect the controller to close the view", [this, ViewClass]()
			{
				View = CreateWidget<UBBContextWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr, nullptr, nullptr);

				UIBBContextRowWidget * RowWidget = RowWidgets[0];

				Controller->AddRow(RowWidget);

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					RowWidget->OnClicked().Broadcast();

					TEST_TRUE(Controller->GetNumRowClickExecutions() == Clicks)
				}

				Controller->Finalize();

				return true;
			});

			It("Given a new context row widget, expect the view to add it to the view rows", [this, ViewClass]()
			{
				View = CreateWidget<UBBContextWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr, nullptr, nullptr);

				UVerticalBox * ContextBox = Cast<UVerticalBox>(View->WidgetTree->FindWidget(TEXT("ContextBox")));

				UTEST_TRUE("Context Box is valid", IsValid(ContextBox))

				TEST_TRUE(ContextBox->GetChildrenCount() == 0)

				for (int Index = 0; Index < RowWidgets.Num(); Index++)
				{
					UIBBContextRowWidget * RowWidget = RowWidgets[Index];
					Controller->AddRow(RowWidget);

					TEST_TRUE(ContextBox->GetChildrenCount() == Index + 1)
					TEST_TRUE(ContextBox->GetChildAt(Index) == RowWidget)
				}

				Controller->Finalize();

				return true;
			});
		});
	}
}