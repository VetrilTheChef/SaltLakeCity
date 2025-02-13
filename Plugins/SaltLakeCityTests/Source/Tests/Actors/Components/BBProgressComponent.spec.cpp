// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/BBActor.h"
#include "Actors/BBProgressableStub.h"
#include "Actors/Components/BBProgressComponent.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/GUI/BBAttachWidgetCommandStub.h"
#include "Commands/GUI/BBDetachWidgetCommandStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBHUDStub.h"
#include "GUI/Models/BBProgressModelStub.h"
#include "GUI/Widgets/BBProgressWidgetStub.h"
#include "Specifications/GUI/BBWidgetSpecificationStub.h"
#include "Specifications/GUI/Factories/BBWidgetSpecificationFactoryStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBProgressComponentSpec, "SaltLakeCity.Actors.Components.ProgressComponent", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBHUDStub * HUD = nullptr;

	UPROPERTY()
	UBBProgressableStub * Progressable = nullptr;

	UPROPERTY()
	ABBActor * Actor = nullptr;

	UPROPERTY()
	UBBCommandFactoryStub * CommandFactory = nullptr;

	UPROPERTY()
	UBBAttachWidgetCommandStub * AttachCommand = nullptr;

	UPROPERTY()
	UBBDetachWidgetCommandStub * DetachCommand = nullptr;

	UPROPERTY()
	UBBWidgetSpecificationFactoryStub * WidgetSpecificationFactory = nullptr;

	UPROPERTY()
	UBBWidgetSpecificationStub * WidgetSpecification = nullptr;

	UPROPERTY()
	UBBProgressWidgetStub * ProgressWidget = nullptr;

	UPROPERTY()
	TArray<UClass *> ComponentClasses;

	// SUT
	UPROPERTY()
	UBBProgressComponent * ProgressComponent = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBProgressComponentSpec)

void UBBProgressComponentSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBProgressComponent>(FString(TEXT("/Game/Actors/Components")), ComponentClasses);
	
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

		Progressable = NewObject<UBBProgressableStub>(TestWorld, UBBProgressableStub::StaticClass());

		UTEST_TRUE("Progressable is valid", IsValid(Progressable))

		Actor = TestWorld->SpawnActor<ABBActor>(ABBActor::StaticClass(), SpawnParameters);

		UTEST_TRUE("Actor is valid", IsValid(Actor))

		Progressable->SetActor(Actor);

		ProgressWidget = CreateWidget<UBBProgressWidgetStub>(TestWorld, UBBProgressWidgetStub::StaticClass());

		UTEST_TRUE("Progress Widget is valid", IsValid(ProgressWidget))

		ProgressWidget->NativeOnInitialized();

		CommandFactory = NewObject<UBBCommandFactoryStub>(GameInstance, UBBCommandFactoryStub::StaticClass());

		UTEST_TRUE("Command Factory is valid", IsValid(CommandFactory))

		AttachCommand = NewObject<UBBAttachWidgetCommandStub>(CommandFactory, UBBAttachWidgetCommandStub::StaticClass());

		UTEST_TRUE("Attach Command is valid", IsValid(AttachCommand))

		AttachCommand->SetWidget(ProgressWidget);

		DetachCommand = NewObject<UBBDetachWidgetCommandStub>(CommandFactory, UBBDetachWidgetCommandStub::StaticClass());

		UTEST_TRUE("Detach Command is valid", IsValid(DetachCommand))

		CommandFactory->AddAttachWidgetCommand(AttachCommand);
		CommandFactory->AddDetachWidgetCommand(DetachCommand);

		WidgetSpecificationFactory = NewObject<UBBWidgetSpecificationFactoryStub>(HUD, UBBWidgetSpecificationFactoryStub::StaticClass());

		UTEST_TRUE("Widget Specification Factory is valid", IsValid(WidgetSpecificationFactory))

		WidgetSpecification = NewObject<UBBWidgetSpecificationStub>(WidgetSpecificationFactory, UBBWidgetSpecificationStub::StaticClass());

		UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

		WidgetSpecificationFactory->AddWidgetSpecification(WidgetSpecification);

		GameInstance->SetCommandFactory(CommandFactory);
		HUD->SetWidgetSpecificationFactory(WidgetSpecificationFactory);

		return true;
	});

	AfterEach([this]()
	{
		ProgressWidget = nullptr;

		ProgressComponent = nullptr;

		TestWorld->DestroyActor(Actor);
		Progressable = nullptr;

		WidgetSpecification = nullptr;
		WidgetSpecificationFactory = nullptr;

		DetachCommand = nullptr;
		AttachCommand = nullptr;
		CommandFactory = nullptr;

		TestWorld->DestroyActor(HUD);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ComponentClass : ComponentClasses)
	{
		Describe("[" + ComponentClass->GetName() + "]", [this, ComponentClass]()
		{
			It("Given a progressable initiation event, expect the progress component to attach a new progress widget", [this, ComponentClass]()
			{
				ProgressComponent = NewObject<UBBProgressComponent>(Actor, ComponentClass);

				UTEST_TRUE("Progress Component is valid", IsValid(ProgressComponent))

				Actor->AddOwnedComponent(ProgressComponent);
				ProgressComponent->RegisterComponent();

				ProgressComponent->Initialize(TScriptInterface<IBBProgressable>(Progressable));

				TEST_TRUE(ProgressComponent->GetWidget() == nullptr)

				Progressable->BroadcastProgressInitiation();

				TEST_TRUE(ProgressComponent->GetWidget() == ProgressWidget)

				Progressable->BroadcastProgressCompletion();

				ProgressComponent->Finalize();

				return true;
			});

			It("Given a progressable completion event, expect the progress component to detach its progress widget", [this, ComponentClass]()
			{
				ProgressComponent = NewObject<UBBProgressComponent>(Actor, ComponentClass);

				UTEST_TRUE("Progress Component is valid", IsValid(ProgressComponent))

				Actor->AddOwnedComponent(ProgressComponent);
				ProgressComponent->RegisterComponent();

				ProgressComponent->Initialize(TScriptInterface<IBBProgressable>(Progressable));

				Progressable->BroadcastProgressInitiation();

				TEST_TRUE(ProgressComponent->GetWidget() != nullptr)

				Progressable->BroadcastProgressCompletion();

				TEST_TRUE(ProgressComponent->GetWidget() == nullptr)

				ProgressComponent->Finalize();

				return true;
			});

			It("Given a new progress update, expect the progress component to update its widget model's progress value", [this, ComponentClass]()
			{
				ProgressComponent = NewObject<UBBProgressComponent>(Actor, ComponentClass);

				UTEST_TRUE("Progress Component is valid", IsValid(ProgressComponent))

				Actor->AddOwnedComponent(ProgressComponent);
				ProgressComponent->RegisterComponent();

				ProgressComponent->Initialize(TScriptInterface<IBBProgressable>(Progressable));

				UBBProgressModelStub * ProgressModel = NewObject<UBBProgressModelStub>(HUD, UBBProgressModelStub::StaticClass());

				UTEST_TRUE("Progress Model is valid", IsValid(ProgressModel))

				ProgressModel->Initialize(nullptr, ProgressComponent);

				TArray<float> Progresses;
				Progresses.Emplace(0.52f);
				Progresses.Emplace(5.25f);
				Progresses.Emplace(-3.04f);
				Progresses.Emplace(0.71f);
				Progresses.Emplace(-0.28f);

				Progressable->BroadcastProgressInitiation();

				for (float & Progress : Progresses)
				{
					Progressable->SetProgress(Progress);
					Progressable->BroadcastProgressUpdate();

					TEST_TRUE(ProgressModel->GetProgress() == Progress)
				}

				Progressable->BroadcastProgressCompletion();

				ProgressModel->Finalize();

				ProgressComponent->Finalize();

				return true;
			});
		});
	}
}