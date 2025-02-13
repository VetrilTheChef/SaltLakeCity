// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/BBSelectableStub.h"
#include "Actors/Components/BBSelectionComponentStub.h"
#include "Engine/DataTable.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBWidgetTargetStub.h"
#include "GUI/BBHUDStub.h"
#include "GUI/Models/BBSelectionModel.h"
#include "GUI/Widgets/BBSelectionWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBSelectionModelSpec, "SaltLakeCity.GUI.Models.Selection", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBSelectionWidgetStub * View = nullptr;

	UPROPERTY()
	ABBHUDStub * HUD = nullptr;

	UPROPERTY()
	UBBSelectionComponentStub * SelectionComponent = nullptr;

	UPROPERTY()
	UBBSelectableStub * Selectable = nullptr;

	UPROPERTY()
	UBBWidgetTargetStub * WidgetTarget = nullptr;

	UPROPERTY()
	TArray<UClass *> ModelClasses;

	// SUT
	UPROPERTY()
	UBBSelectionModel * Model = nullptr;

	TArray<FText> DisplayNames;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBSelectionModelSpec)

void UBBSelectionModelSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBSelectionModel>(FString(TEXT("/Game/GUI/Models")), ModelClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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

		View = CreateWidget<UBBSelectionWidgetStub>(TestWorld, UBBSelectionWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		HUD = TestWorld->SpawnActor<ABBHUDStub>(ABBHUDStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("HUD is valid", IsValid(HUD))
			
		SelectionComponent = NewObject<UBBSelectionComponentStub>(TestWorld, UBBSelectionComponentStub::StaticClass());

		UTEST_TRUE("Selection Component is valid", IsValid(SelectionComponent))

		Selectable = NewObject<UBBSelectableStub>(TestWorld, UBBSelectableStub::StaticClass());

		UTEST_TRUE("Selectable is valid", IsValid(Selectable))

		SelectionComponent->SetSelectable(TScriptInterface<IBBSelectable>(Selectable));

		WidgetTarget = NewObject<UBBWidgetTargetStub>(TestWorld, UBBWidgetTargetStub::StaticClass());

		UTEST_TRUE("Widget Target is valid", IsValid(WidgetTarget))

		Selectable->SetWidgetTarget(TScriptInterface<IBBWidgetTarget>(WidgetTarget));

		return true;
	});

	AfterEach([this]()
	{
		WidgetTarget = nullptr;

		Selectable = nullptr;

		SelectionComponent = nullptr;

		View = nullptr;

		Model = nullptr;

		TestWorld->DestroyActor(HUD);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ModelClass : ModelClasses)
	{
		Describe("["+ModelClass->GetName()+"]", [this, ModelClass]()
		{
			It("Given a component update from the HUD, expect the model to update the view's selection", [this, ModelClass]()
			{
				Model = NewObject<UBBSelectionModel>(View, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))
				
				Model->Initialize(View, HUD);

				for (FText & DisplayName : DisplayNames)
				{
					WidgetTarget->SetDisplayName(DisplayName);

					View->SetDisplayName(FText::FromString(""));

					TEST_TRUE(View->GetDisplayName().EqualTo(FText::FromString("")))

					HUD->BroadcastSelectionUpdate(SelectionComponent);

					TEST_TRUE(View->GetDisplayName().EqualTo(DisplayName))
				}

				Model->Finalize();

				return true;
			});

			It("Given a component update from the finalized HUD, expect the model not to update the view's selection", [this, ModelClass]()
			{
				TArray<TScriptInterface<IBBSelectable>> Selectables;

				Model = NewObject<UBBSelectionModel>(View, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				Model->Initialize(View, HUD);

				Model->Finalize();

				for (FText & DisplayName : DisplayNames)
				{
					WidgetTarget->SetDisplayName(DisplayName);

					View->SetDisplayName(FText::FromString(""));

					TEST_TRUE(View->GetDisplayName().EqualTo(FText::FromString("")))

					HUD->BroadcastSelectionUpdate(SelectionComponent);

					TEST_TRUE(View->GetDisplayName().EqualTo(FText::FromString("")))
				}

				return true;
			});
		});
	}
}