// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBSelectionControllerStub.h"
#include "GUI/Widgets/BBSelectionWidget.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBSelectionWidgetSpec,
	"SaltLakeCity.GUI.Widgets.Selection",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBSelectionControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<FText> DisplayNames;

	UPROPERTY()
	TArray<float> HealthPercents;

	UPROPERTY()
	TArray<float> StaminaPercents;

	UPROPERTY()
	TArray<UClass *> ViewClasses;

	// SUT
	UPROPERTY()
	UBBSelectionWidget * View = nullptr;

END_DEFINE_SPEC(UBBSelectionWidgetSpec)

void UBBSelectionWidgetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBSelectionWidget>(FString(TEXT("/Game/GUI/Widgets")), ViewClasses);

	DisplayNames.Empty();
	DisplayNames.Emplace(FText::FromString("A Building"));
	DisplayNames.Emplace(FText::FromString("SeLeCtAbLe!4"));
	DisplayNames.Emplace(FText::FromString("%RY(\"QYG(/"));
	DisplayNames.Emplace(FText::FromString("_%_____-"));
	DisplayNames.Emplace(FText::FromString("ANOTHER ONE"));

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Controller = NewObject<UBBSelectionControllerStub>(TestWorld, UBBSelectionControllerStub::StaticClass());

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

	for (UClass * & ViewClass : ViewClasses)
	{
		Describe("[" + ViewClass->GetName() + "]", [this, ViewClass]()
		{
			It("Given a new display name, expect the view to update the display name", [this, ViewClass]()
			{
				View = CreateWidget<UBBSelectionWidget>(TestWorld, ViewClass);

				UTEST_TRUE("View is valid", IsValid(View))
				
				Controller->Initialize(View, nullptr);

				UTextBlock * DisplayNameText = Cast<UTextBlock>(View->WidgetTree->FindWidget(TEXT("DisplayNameText")));

				UTEST_TRUE("Display Name Text is valid", IsValid(DisplayNameText))

				for (auto& DisplayName : DisplayNames)
				{
					View->SetDisplayName(DisplayName);

					TEST_TRUE(DisplayNameText->Text.EqualTo(DisplayName))
				}

				Controller->Finalize();

				return true;
			});
		});
	}
}