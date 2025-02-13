// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/GUI/BBCloseWidgetCommandStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Controllers/BBTitleController.h"
#include "GUI/Models/BBTitleModelStub.h"
#include "GUI/Widgets/BBTitleWidgetStub.h"
#include "GUI/Widgets/BBWidgetStub.h"
#include "Specifications/GUI/BBWidgetSpecificationStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBTitleControllerSpec, "SaltLakeCity.GUI.Controllers.Title", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<FVector2D> Positions;

	UPROPERTY()
	UBBCommandFactoryStub * CommandFactory = nullptr;

	UPROPERTY()
	UBBTitleModelStub * Model = nullptr;

	UPROPERTY()
	UBBTitleWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	// SUT
	UPROPERTY()
	UBBTitleController * Controller = nullptr;

END_DEFINE_SPEC(UBBTitleControllerSpec)

void UBBTitleControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBTitleController>(FString(TEXT("/Game/GUI/Controllers")), ControllerClasses);

	Positions.Empty();
	Positions.Emplace(FVector2D(253.0f, 146.0f));
	Positions.Emplace(FVector2D(184.7f, -0.5f));
	Positions.Emplace(FVector2D(-81.9f, 180.1f));
	Positions.Emplace(FVector2D(-172.4f, -217.3f));
	Positions.Emplace(FVector2D(-2.6f, 0.0f));

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Model = NewObject<UBBTitleModelStub>(TestWorld, UBBTitleModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		UIBBWidget * ParentWidget = CreateWidget<UBBWidgetStub>(TestWorld, UBBWidgetStub::StaticClass());

		UTEST_TRUE("Parent Widget is valid", IsValid(ParentWidget))

		ParentWidget->NativeOnInitialized();

		Model->SetParentWidget(ParentWidget);
		Model->SetParentWidgetSpecification(NewObject<UBBWidgetSpecificationStub>(Model, UBBWidgetSpecificationStub::StaticClass()));

		View = CreateWidget<UBBTitleWidgetStub>(TestWorld, UBBTitleWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		CommandFactory = NewObject<UBBCommandFactoryStub>(TestWorld, UBBCommandFactoryStub::StaticClass());
		
		UTEST_TRUE("Command Factory is valid", IsValid(CommandFactory))

		CommandFactory->AddCloseWidgetCommand(NewObject<UBBCloseWidgetCommandStub>(CommandFactory, UBBCloseWidgetCommandStub::StaticClass()));

		GameInstance->SetCommandFactory(CommandFactory);

		return true;
	});

	AfterEach([this]()
	{
		CommandFactory = nullptr;

		Model = nullptr;
		View = nullptr;
		Controller = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ControllerClass : ControllerClasses)
	{
		Describe("["+ControllerClass->GetName()+"]", [this, ControllerClass]()
		{
			It("Given a position update from the view, expect the controller to update the model", [this, ControllerClass]()
			{
				Controller = NewObject<UBBTitleController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, nullptr, CommandFactory);

				for (FVector2D & Position : Positions)
				{
					View->Drag(Position);

					TEST_TRUE(Model->GetPosition() == Position)
				}

				Controller->Finalize();

				return true;
			});
		});
	}
}