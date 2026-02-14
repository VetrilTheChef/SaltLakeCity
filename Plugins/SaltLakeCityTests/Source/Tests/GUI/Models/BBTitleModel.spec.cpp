// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBHUDStub.h"
#include "GUI/Controllers/BBTitleControllerStub.h"
#include "GUI/Models/BBGUIModelStub.h"
#include "GUI/Models/BBTitleModel.h"
#include "GUI/Widgets/BBTitleWidgetStub.h"
#include "GUI/Widgets/BBWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBTitleModelSpec,
	"SaltLakeCity.GUI.Models.Title",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld* TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub* GameInstance = nullptr;

	UPROPERTY()
	UBBGUIModelStub* ParentModel = nullptr;

	UPROPERTY()
	UBBWidgetStub* ParentWidget = nullptr;

	UPROPERTY()
	ABBHUDStub* HUD = nullptr;

	UPROPERTY()
	UBBTitleControllerStub* Controller = nullptr;

	UPROPERTY()
	UBBTitleWidgetStub* View = nullptr;

	UPROPERTY()
	TArray<UClass*> ModelClasses;

	// SUT
	UPROPERTY()
	UBBTitleModel* Model = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBTitleModelSpec)

void UBBTitleModelSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBTitleModel>(FString(TEXT("/Game/GUI/Models")), ModelClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		HUD = TestWorld->SpawnActor<ABBHUDStub>(ABBHUDStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("HUD is valid", IsValid(HUD))

		GameInstance->SetHUD(HUD);

		View = CreateWidget<UBBTitleWidgetStub>(TestWorld, UBBTitleWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		Controller = NewObject<UBBTitleControllerStub>(TestWorld, UBBTitleControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		ParentModel = NewObject<UBBGUIModelStub>(TestWorld, UBBGUIModelStub::StaticClass());

		UTEST_TRUE("Parent Model is valid", IsValid(ParentModel))
		
		ParentWidget = CreateWidget<UBBWidgetStub>(TestWorld, UBBWidgetStub::StaticClass());

		UTEST_TRUE("Parent Widget is valid", IsValid(ParentWidget))

		ParentWidget->NativeOnInitialized();

		ParentModel->SetWidget(ParentWidget);

		return true;
	});

	AfterEach([this]()
	{
		ParentModel = nullptr;
		ParentWidget = nullptr;

		View = nullptr;

		Controller = nullptr;

		Model = nullptr;

		TestWorld->DestroyActor(HUD);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass* & ModelClass : ModelClasses)
	{
		Describe("[" + ModelClass->GetName() + "]", [this, ModelClass]()
		{
			It("Given a new position, expect the model to set the position of the parent widget", [this, ModelClass]()
			{
				Model = NewObject<UBBTitleModel>(Controller, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				TArray<FVector2D> Positions;
				Positions.Empty();
				Positions.Emplace(FVector2D(3.0, 40.0));
				Positions.Emplace(FVector2D(185.0, 1025.0));
				Positions.Emplace(FVector2D(0.0, 1722.0));
				Positions.Emplace(FVector2D(4906.0, 0.0));
				Positions.Emplace(FVector2D(524.0, 1131.0));

				ParentWidget->AddToScreen();

				Model->Initialize(View, ParentModel);

				for (FVector2D& Position : Positions)
				{
					Model->SetPosition(Position);

					FVector2D ParentPosition = ParentWidget->GetPositionInViewport(true);

					TEST_TRUE((ParentPosition - Position).IsNearlyZero())
				}

				ParentWidget->RemoveFromParent();

				Model->Finalize();

				return true;
			});
		});
	}
}