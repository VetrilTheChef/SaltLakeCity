// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/BBWorkComponentStub.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/GUI/BBCloseWidgetCommandStub.h"
#include "Commands/Metacommands/BBCompositeCommandStub.h"
#include "Commands/Jobs/BBSetJobCommandStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBWidgetTargetStub.h"
#include "GUI/Controllers/BBJobController.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Factories/BBWidgetFactoryStub.h"
#include "GUI/Models/BBJobModelStub.h"
#include "GUI/Widgets/BBJobWidgetStub.h"
#include "GUI/Widgets/BBTitleWidgetStub.h"
#include "Specifications/GUI/BBTargetedWidgetSpecificationStub.h"
#include "Specifications/GUI/Factories/BBWidgetSpecificationFactoryStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBJobControllerSpec, "SaltLakeCity.GUI.Controllers.Job", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBJobModelStub * Model = nullptr;

	UPROPERTY()
	UBBJobWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<EBBJob> Jobs;

	UPROPERTY()
	TArray<FText> DisplayNames;

	UPROPERTY()
	UBBCommandFactoryStub * CommandFactory = nullptr;

	UPROPERTY()
	UBBCompositeCommandStub * AcceptCommand = nullptr;

	UPROPERTY()
	UBBSetJobCommandStub * SetJobCommand = nullptr;

	UPROPERTY()
	UBBCloseWidgetCommandStub * CloseCommand = nullptr;

	UPROPERTY()
	UBBWidgetSpecificationFactoryStub * WidgetSpecificationFactory = nullptr;

	UPROPERTY()
	UBBWidgetFactoryStub * WidgetFactory = nullptr;

	UPROPERTY()
	UBBTitleWidgetStub * TitleWidget = nullptr;

	UPROPERTY()
	UBBWorkComponentStub * WorkComponent = nullptr;

	UPROPERTY()
	UBBWidgetTargetStub * WidgetTarget = nullptr;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	// SUT
	UPROPERTY()
	UBBJobController * Controller = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBJobControllerSpec)

void UBBJobControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBJobController>(FString(TEXT("/Game/GUI/Controllers")), ControllerClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Jobs.Empty();
	Jobs.Emplace(EBBJob::None);
	Jobs.Emplace(EBBJob::Builder);
	Jobs.Emplace(EBBJob::None);
	Jobs.Emplace(EBBJob::Idle);
	Jobs.Emplace(EBBJob::Builder);

	DisplayNames.Empty();
	DisplayNames.Emplace(FText::FromString("THIS IS A NAME"));
	DisplayNames.Emplace(FText::FromString("ANOTHER NAME"));
	DisplayNames.Emplace(FText::FromString("COULD BE ANYTHING"));
	DisplayNames.Emplace(FText::FromString("TAR29q5Y!g!"));
	DisplayNames.Emplace(FText::FromString("\"\"\"\"\"\"\"\"\"\"\"\""));

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Model = NewObject<UBBJobModelStub>(TestWorld, UBBJobModelStub::StaticClass());

		UTEST_TRUE("Model is valid", IsValid(Model))

		Model->AddJob(FText::FromString("GRUNT"), FText::FromString("Grunt grunt."), EBBJob::None);
		Model->AddJob(FText::FromString("PUNCHING BAG"), FText::FromString("Try it."), EBBJob::Idle);
		Model->AddJob(FText::FromString("SECRET AGENT"), FText::FromString("Name's Bond."), EBBJob::Builder);

		View = CreateWidget<UBBJobWidgetStub>(TestWorld, UBBJobWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		WorkComponent = NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass());
		
		UTEST_TRUE("Work Component is valid", IsValid(WorkComponent))

		WidgetTarget = NewObject<UBBWidgetTargetStub>(TestWorld, UBBWidgetTargetStub::StaticClass());

		UTEST_TRUE("Widget Target is valid", IsValid(WidgetTarget))

		WorkComponent->SetWidgetTarget(TScriptInterface<IBBWidgetTarget>(WidgetTarget));

		CommandFactory = NewObject<UBBCommandFactoryStub>(TestWorld, UBBCommandFactoryStub::StaticClass());

		UTEST_TRUE("Command Factory is valid", IsValid(CommandFactory))

		AcceptCommand = NewObject<UBBCompositeCommandStub>(CommandFactory, UBBCompositeCommandStub::StaticClass());

		UTEST_TRUE("Accept Command is valid", IsValid(AcceptCommand))

		SetJobCommand = NewObject<UBBSetJobCommandStub>(CommandFactory, UBBSetJobCommandStub::StaticClass());

		UTEST_TRUE("Set Job Command is valid", IsValid(SetJobCommand))

		CloseCommand = NewObject<UBBCloseWidgetCommandStub>(CommandFactory, UBBCloseWidgetCommandStub::StaticClass());

		UTEST_TRUE("Close Command is valid", IsValid(CloseCommand))

		CommandFactory->AddCompositeCommand(AcceptCommand);
		CommandFactory->AddSetJobCommand(SetJobCommand);
		CommandFactory->AddCloseWidgetCommand(CloseCommand);

		WidgetSpecificationFactory = NewObject<UBBWidgetSpecificationFactoryStub>(TestWorld, UBBWidgetSpecificationFactoryStub::StaticClass());

		UTEST_TRUE("Widget Specification Factory is valid", IsValid(WidgetSpecificationFactory))

		WidgetFactory = NewObject<UBBWidgetFactoryStub>(TestWorld, UBBWidgetFactoryStub::StaticClass());

		UTEST_TRUE("Widget Factory is valid", IsValid(WidgetFactory))

		TitleWidget = NewObject<UBBTitleWidgetStub>(WidgetFactory, UBBTitleWidgetStub::StaticClass());

		UTEST_TRUE("Title Widget is valid", IsValid(TitleWidget))

		WidgetFactory->AddWidget(TitleWidget);

		Model->Initialize(View, nullptr, nullptr);
		Model->SetWidgetSpecification(NewObject<UBBTargetedWidgetSpecificationStub>(WidgetSpecificationFactory, UBBTargetedWidgetSpecificationStub::StaticClass()));

		GameInstance->SetCommandFactory(CommandFactory);

		return true;
	});

	AfterEach([this]()
	{
		Model->Finalize();
		Model = nullptr;
		View = nullptr;

		WidgetTarget = nullptr;
		WorkComponent = nullptr;
		
		AcceptCommand = nullptr;
		SetJobCommand = nullptr;
		CloseCommand = nullptr;
		CommandFactory = nullptr;

		WidgetSpecificationFactory = nullptr;

		TitleWidget = nullptr;
		WidgetFactory = nullptr;

		Controller = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ControllerClass : ControllerClasses)
	{
		Describe("[" + ControllerClass->GetName() + "]", [this, ControllerClass]()
		{
			It("Given a new view, expect the controller to set the view's jobs", [this, ControllerClass]()
			{
				Controller = NewObject<UBBJobController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, WidgetSpecificationFactory, CommandFactory);

				TEST_TRUE(View->GetNumJobs() == Model->GetNumJobs())

				for (int Index = 0; Index < Model->GetNumJobs(); Index++)
				{
					TEST_TRUE(View->GetJob(Index) == Model->GetJob(Index))
					TEST_TRUE(View->GetJobName(Index).EqualTo(Model->GetJobName(Index)))
					TEST_TRUE(View->GetJobTooltip(Index).EqualTo(Model->GetJobTooltip(Index)))
				}

				Controller->Finalize();

				return true;
			});

			It("Given a new view, expect the controller to set the view's commands", [this, ControllerClass]()
			{
				Controller = NewObject<UBBJobController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, WidgetSpecificationFactory, CommandFactory);

				TEST_TRUE(IsValid(View->GetAcceptCommand()))
				TEST_TRUE(View->GetAcceptCommand() == AcceptCommand)

				TEST_TRUE(IsValid(View->GetCancelCommand()))
				TEST_TRUE(View->GetCancelCommand() == CloseCommand)

				Controller->Finalize();

				return true;
			});

			It("Given a job update from the model, expect the controller to update the view's job", [this, ControllerClass]()
			{
				Controller = NewObject<UBBJobController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, WidgetSpecificationFactory, CommandFactory);

				for (EBBJob & Job : Jobs)
				{
					Model->SetCurrentJob(Job);
					Model->BroadcastConsumerUpdate(WorkComponent);

					TEST_TRUE(View->GetJob() == Job)
					TEST_TRUE(View->GetSelectedJobName().EqualTo(Model->FindJobName(Job)))
				}

				Controller->Finalize();

				return true;
			});

			It("Given a component update from the model, expect the controller to update the view's name", [this, ControllerClass]()
			{
				Controller = NewObject<UBBJobController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, WidgetSpecificationFactory, CommandFactory);

				for (FText & DisplayName : DisplayNames)
				{
					Model->SetDisplayName(DisplayName);
					Model->BroadcastConsumerUpdate(WorkComponent);

					TEST_TRUE(View->GetDisplayName().EqualTo(DisplayName))
				}

				Controller->Finalize();

				return true;
			});

			It("Given a job update from the view, expect the controller to update the view's command", [this, ControllerClass]()
			{
				Controller = NewObject<UBBJobController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, WidgetSpecificationFactory, CommandFactory);

				for (EBBJob & Job : Jobs)
				{
					View->SetJob(Job);

					TEST_TRUE(SetJobCommand->GetJob() == Job)
				}

				Controller->Finalize();

				return true;
			});

			It("Given a component update from the model, expect the controller to update the view's command", [this, ControllerClass]()
			{
				Controller = NewObject<UBBJobController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, WidgetSpecificationFactory, CommandFactory);

				for (EBBJob & Job : Jobs)
				{
					Model->SetCurrentJob(Job);
					Model->BroadcastConsumerUpdate(WorkComponent);

					TEST_TRUE(SetJobCommand->GetJob() == Job)
				}

				Controller->Finalize();

				return true;
			});

			It("Given a new view, expect the controller to set the view's title", [this, ControllerClass]()
			{
				Controller = NewObject<UBBJobController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, WidgetSpecificationFactory, CommandFactory);
				
				TEST_TRUE(View->GetTitle() == TitleWidget)

				Controller->Finalize();

				return true;
			});

			It("Given a view to be unbound, expect the controller to destroy the view", [this, ControllerClass]()
			{
				Controller = NewObject<UBBJobController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, WidgetSpecificationFactory, CommandFactory);

				TEST_TRUE(IsValid(View))

				Controller->Finalize();

				TEST_FALSE(IsValid(View))

				return true;
			});

			It("Given a view to be unbound, expect the controller to destroy the view's title", [this, ControllerClass]()
			{
				Controller = NewObject<UBBJobController>(View, ControllerClass);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				Controller->Initialize(View, Model, WidgetFactory, WidgetSpecificationFactory, CommandFactory);

				TEST_TRUE(View->GetTitle() == TitleWidget)

				Controller->Finalize();

				TEST_FALSE(IsValid(TitleWidget))

				return true;
			});
		});
	}
}