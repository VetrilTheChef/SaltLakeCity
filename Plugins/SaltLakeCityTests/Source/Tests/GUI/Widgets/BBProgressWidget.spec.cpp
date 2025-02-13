// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBProgressControllerStub.h"
#include "GUI/Widgets/BBProgressWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBProgressWidgetSpec, "SaltLakeCity.GUI.Widgets.Progress", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<float> Progresses;

	UPROPERTY()
	UBBProgressControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<UClass *> ViewClasses;

	// SUT
	UPROPERTY()
	UBBProgressWidget * View = nullptr;

END_DEFINE_SPEC(UBBProgressWidgetSpec)

void UBBProgressWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBProgressWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);

	Progresses.Empty();
	Progresses.Emplace(0.0f);
	Progresses.Emplace(100.0f);
	Progresses.Emplace(26.3f);
	Progresses.Emplace(-102.1f);
	Progresses.Emplace(1753.0f);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Controller = NewObject<UBBProgressControllerStub>(TestWorld, UBBProgressControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		return true;
	});

	AfterEach([this]()
	{
		Controller = nullptr;
		View = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (auto& ViewClass : ViewClasses)
	{
		Describe("[" + ViewClass->GetName() + "]", [this, ViewClass]()
		{
			It("Given a new progress, expect the view to update the progress bar", [this, ViewClass]()
			{
				View = CreateWidget<UBBProgressWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr);

				UProgressBar * ProgressBar = Cast<UProgressBar>(View->WidgetTree->FindWidget(TEXT("ProgressBar")));

				UTEST_TRUE("Progress Bar is valid", IsValid(ProgressBar))

				for (auto& Progress : Progresses)
				{
					View->SetProgress(Progress);

					TEST_TRUE(ProgressBar->Percent == Progress)
				}

				Controller->Finalize();

				return true;
			});
		});
	}
}