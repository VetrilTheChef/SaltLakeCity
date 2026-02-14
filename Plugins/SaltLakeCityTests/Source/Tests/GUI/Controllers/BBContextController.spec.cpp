// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/GUI/BBOpenWidgetCommandStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBWidgetManagerStub.h"
#include "GUI/Controllers/BBContextController.h"
#include "GUI/Models/BBContextModelStub.h"
#include "GUI/Widgets/BBContextRowWidgetStub.h"
#include "GUI/Widgets/BBContextWidgetStub.h"
#include "LevelEditor.h"
#include "Specifications/GUI/BBWidgetSpecificationStub.h"
#include "Specifications/GUI/Factories/BBWidgetSpecificationFactoryStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBContextControllerSpec,
	"SaltLakeCity.GUI.Controllers.Context",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld* TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub* GameInstance = nullptr;

	UPROPERTY()
	UBBWidgetManagerStub* WidgetManager = nullptr;

	UPROPERTY()
	UBBContextModelStub* Model = nullptr;

	UPROPERTY()
	UBBContextWidgetStub* View = nullptr;

	UPROPERTY()
	UBBWidgetSpecificationFactoryStub* WidgetSpecificationFactory = nullptr;

	UPROPERTY()
	UBBCommandFactoryStub* CommandFactory = nullptr;

	UPROPERTY()
	TArray<UClass*> ControllerClasses;

	// SUT
	UPROPERTY()
	UBBContextController* Controller = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBContextControllerSpec)

void UBBContextControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBContextController>(FString(TEXT("/Game/GUI/Controllers")), ControllerClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		WidgetManager = NewObject<UBBWidgetManagerStub>(GameInstance, UBBWidgetManagerStub::StaticClass());

		UTEST_TRUE("Widget Manager is valid", IsValid(WidgetManager))

		GameInstance->SetWidgetManager(WidgetManager);

		Model = NewObject<UBBContextModelStub>(TestWorld, UBBContextModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		Model->AddRow(
			FText::FromString("SOME ROW"),
			nullptr,
			nullptr,
			FText::FromString("It's nice"),
			EBBContext::Build,
			EBBWidget::Build
		);
		Model->AddRow(
			FText::FromString("OTHER ROW"),
			nullptr,
			nullptr,
			FText::FromString("Not so nice"),
			EBBContext::Dossier,
			EBBWidget::Progress
		);
		Model->AddRow(
			FText::FromString("NICE ROW"),
			nullptr,
			nullptr,
			FText::FromString("Actually horrible"),
			EBBContext::Job,
			EBBWidget::Dossier
		);
		Model->AddRow(
			FText::FromString("LAST ROW"),
			nullptr,
			nullptr,
			FText::FromString("None after her"),
			EBBContext::Build,
			EBBWidget::DateTime
		);

		View = CreateWidget<UBBContextWidgetStub>(TestWorld, UBBContextWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();
		View->SetRowWidgetClass(TSoftClassPtr<UIBBContextRowWidget>(UBBContextRowWidgetStub::StaticClass()));

		WidgetSpecificationFactory = NewObject<UBBWidgetSpecificationFactoryStub>(
			WidgetManager,
			UBBWidgetSpecificationFactoryStub::StaticClass()
		);

		UTEST_TRUE("Widget Specification Factory is valid", IsValid(WidgetSpecificationFactory))

		WidgetManager->SetWidgetSpecificationFactory(WidgetSpecificationFactory);

		CommandFactory = NewObject<UBBCommandFactoryStub>(GameInstance, UBBCommandFactoryStub::StaticClass());

		UTEST_TRUE("Command Factory is valid", IsValid(CommandFactory))

		GameInstance->SetCommandFactory(CommandFactory);

		for (int Index = 0; Index < Model->GetNumRows(); Index++)
		{
			WidgetSpecificationFactory->AddWidgetSpecification(
				NewObject<UBBWidgetSpecificationStub>(
					WidgetSpecificationFactory,
					UBBWidgetSpecificationStub::StaticClass()
				)
			);

			CommandFactory->AddOpenWidgetCommand(
				NewObject<UBBOpenWidgetCommandStub>(
					CommandFactory,
					UBBOpenWidgetCommandStub::StaticClass()
				)
			);
		}

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;
		View = nullptr;
		
		CommandFactory = nullptr;
		WidgetSpecificationFactory = nullptr;

		WidgetManager = nullptr;
		GameInstance = nullptr;

		Controller = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass*& ControllerClass : ControllerClasses)
	{
		Describe("[" + ControllerClass->GetName() + "]", [this, ControllerClass]()
		{
			It(
				"Given a new view, expect the controller to set the view's rows",
				[this, ControllerClass]()
			{
				Controller = NewObject<UBBContextController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetSpecificationFactory, CommandFactory);

				TEST_TRUE(View->GetNumRows() == Model->GetNumRows())

				for (int Index = 0; Index < Model->GetNumRows(); Index++)
				{
					UBBContextRowWidgetStub* RowWidget = Cast<UBBContextRowWidgetStub>(View->GetRowWidget(Index));

					UTEST_TRUE("Row Widget is valid", IsValid(RowWidget))

					FBBContextRowData RowData = Model->GetRowData(Index);
					
					TEST_TRUE(RowWidget->GetRowName().EqualTo(RowData.Name))
					TEST_TRUE(RowWidget->GetRowIcon() == RowData.Icon)
					TEST_TRUE(RowWidget->GetRowTooltip().EqualTo(RowData.Tooltip))
					TEST_TRUE(IsValid(RowWidget->GetCommand()))
				}

				return true;
			});

			It(
				"Given a cursor leaving update from the view, expect the controller to remove the view from the screen",
				[this, ControllerClass]()
			{
				Controller = NewObject<UBBContextController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetSpecificationFactory, CommandFactory);

				View->AddToScreen(0);

				TEST_TRUE(View->IsInViewport())

				FPointerEvent MouseEvent = FPointerEvent();
				View->BroadcastOnMouseLeave(MouseEvent);

				TEST_FALSE(View->IsInViewport())

				Controller->Finalize();

				return true;
			});

			It(
				"Given a clicked row update from the view, expect the controller to remove the view from the screen",
				[this, ControllerClass]()
			{
				Controller = NewObject<UBBContextController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetSpecificationFactory, CommandFactory);

				UBBContextRowWidgetStub* RowWidget = Cast<UBBContextRowWidgetStub>(View->GetRowWidget(0));

				UTEST_TRUE("Row Widget is valid", IsValid(RowWidget))

				View->AddToScreen(0);

				TEST_TRUE(View->IsInViewport())

				RowWidget->ClickRowButton();

				TEST_FALSE(View->IsInViewport())

				Controller->Finalize();

				return true;
			});

			It(
				"Given a view to be finalized, expect the controller to destroy the view",
				[this, ControllerClass]()
			{
				Controller = NewObject<UBBContextController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetSpecificationFactory, CommandFactory);

				TEST_TRUE(IsValid(View))

				Controller->Finalize();

				TEST_FALSE(IsValid(View))

				return true;
			});
		});
	}
}