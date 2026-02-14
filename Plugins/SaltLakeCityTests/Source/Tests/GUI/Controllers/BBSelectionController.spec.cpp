// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBSelectionController.h"
#include "GUI/Models/BBSelectionModelStub.h"
#include "GUI/Models/Interfaces/IBBSelectionModel.h"
#include "GUI/Widgets/BBSelectionWidgetStub.h"
#include "GUI/Widgets/Interfaces/IBBSelectionWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBSelectionControllerSpec,
	"SaltLakeCity.GUI.Controllers.Selection",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBSelectionModelStub * Model = nullptr;

	UPROPERTY()
	UBBSelectionWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	// SUT
	UPROPERTY()
	UBBSelectionController * Controller = nullptr;

END_DEFINE_SPEC(UBBSelectionControllerSpec)

void UBBSelectionControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBSelectionController>(FString(TEXT("/Game/GUI/Controllers")), ControllerClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Model = NewObject<UBBSelectionModelStub>(TestWorld, UBBSelectionModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		View = CreateWidget<UBBSelectionWidgetStub>(TestWorld, UBBSelectionWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;
		View = nullptr;

		Controller = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ControllerClass : ControllerClasses)
	{
		Describe("["+ ControllerClass->GetName()+"]", [this, ControllerClass]()
		{
			It("Given a view to be finalized, expect the controller to destroy the view", [this, ControllerClass]()
			{
				Controller = NewObject<UBBSelectionController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model);

				TEST_TRUE(IsValid(View))

				Controller->Finalize();

				TEST_FALSE(IsValid(View))

				return true;
			});
		});
	}
}