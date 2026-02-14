// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBProgressController.h"
#include "GUI/Models/BBProgressModelStub.h"
#include "GUI/Models/Interfaces/IBBProgressModel.h"
#include "GUI/Widgets/BBProgressWidgetStub.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBProgressControllerSpec,
	"SaltLakeCity.GUI.Controllers.Progress",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBProgressModelStub * Model = nullptr;

	UPROPERTY()
	UBBProgressWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	// SUT
	UPROPERTY()
	UBBProgressController * Controller = nullptr;

END_DEFINE_SPEC(UBBProgressControllerSpec)

void UBBProgressControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBProgressController>(FString(TEXT("/Game/GUI/Controllers")), ControllerClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Model = NewObject<UBBProgressModelStub>(TestWorld, UBBProgressModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		View = CreateWidget<UBBProgressWidgetStub>(TestWorld, UBBProgressWidgetStub::StaticClass());

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
				Controller = NewObject<UBBProgressController>(View, ControllerClass);

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