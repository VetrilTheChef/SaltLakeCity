// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "Actors/Components/BBSelectionComponent.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/GameStates/BBSelectCommandStub.h"
#include "Commands/GUI/BBAttachWidgetCommandStub.h"
#include "Commands/GUI/BBDetachWidgetCommandStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBWidgetManagerStub.h"
#include "GUI/Widgets/BBSelectionWidgetStub.h"
#include "Specifications/GUI/BBWidgetSpecificationStub.h"
#include "Specifications/GUI/Factories/BBWidgetSpecificationFactoryStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBSelectionComponentSpec,
	"SaltLakeCity.Actors.Components.SelectionComponent",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld* TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub* GameInstance = nullptr;

	UPROPERTY()
	UBBWidgetManagerStub* WidgetManager = nullptr;

	UPROPERTY()
	ABBCharacterStub* Character;

	UPROPERTY()
	UBBCommandFactoryStub* CommandFactory = nullptr;

	UPROPERTY()
	UBBSelectCommandStub* SelectCommand = nullptr;

	UPROPERTY()
	UBBAttachWidgetCommandStub* AttachCommand = nullptr;

	UPROPERTY()
	UBBDetachWidgetCommandStub* DetachCommand = nullptr;

	UPROPERTY()
	UBBWidgetSpecificationFactoryStub* WidgetSpecificationFactory = nullptr;

	UPROPERTY()
	UBBWidgetSpecificationStub* WidgetSpecification = nullptr;

	UPROPERTY()
	UBBSelectionWidgetStub* SelectionWidget = nullptr;

	UPROPERTY()
	TArray<UClass*> ComponentClasses;

	// SUT
	UPROPERTY()
	UBBSelectionComponent* SelectionComponent = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBSelectionComponentSpec)

void UBBSelectionComponentSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBSelectionComponent>(FString(TEXT("/Game/Actors/Components")), ComponentClasses);
	
	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		WidgetManager = NewObject<UBBWidgetManagerStub>(
			GameInstance,
			UBBWidgetManagerStub::StaticClass()
		);

		UTEST_TRUE("Widget Manager is valid", IsValid(WidgetManager))

		GameInstance->SetWidgetManager(WidgetManager);

		Character = TestWorld->SpawnActor<ABBCharacterStub>(
			ABBCharacterStub::StaticClass(),
			SpawnParameters
		);

		UTEST_TRUE("Character is valid", IsValid(Character))

		SelectionWidget = CreateWidget<UBBSelectionWidgetStub>(
			TestWorld,
			UBBSelectionWidgetStub::StaticClass()
		);

		UTEST_TRUE("Selection Widget is valid", IsValid(SelectionWidget))

		SelectionWidget->NativeOnInitialized();

		CommandFactory = NewObject<UBBCommandFactoryStub>(
			GameInstance,
			UBBCommandFactoryStub::StaticClass()
		);

		UTEST_TRUE("Command Factory is valid", IsValid(CommandFactory))

		SelectCommand = NewObject<UBBSelectCommandStub>(
			CommandFactory,
			UBBSelectCommandStub::StaticClass()
		);

		UTEST_TRUE("Select Command is valid", IsValid(SelectCommand))

		CommandFactory->AddSelectCommand(SelectCommand);

		AttachCommand = NewObject<UBBAttachWidgetCommandStub>(
			CommandFactory,
			UBBAttachWidgetCommandStub::StaticClass()
		);

		UTEST_TRUE("Attach Command is valid", IsValid(AttachCommand))

		AttachCommand->SetWidget(SelectionWidget);

		DetachCommand = NewObject<UBBDetachWidgetCommandStub>(
			CommandFactory,
			UBBDetachWidgetCommandStub::StaticClass()
		);

		UTEST_TRUE("Detach Command is valid", IsValid(DetachCommand))

		CommandFactory->AddSelectCommand(SelectCommand);
		CommandFactory->AddAttachWidgetCommand(AttachCommand);
		CommandFactory->AddDetachWidgetCommand(DetachCommand);

		WidgetSpecificationFactory = NewObject<UBBWidgetSpecificationFactoryStub>(
			WidgetManager,
			UBBWidgetSpecificationFactoryStub::StaticClass()
		);

		UTEST_TRUE("Widget Specification Factory is valid", IsValid(WidgetSpecificationFactory))

		WidgetSpecification = NewObject<UBBWidgetSpecificationStub>(
			WidgetSpecificationFactory,
			UBBWidgetSpecificationStub::StaticClass()
		);

		UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecification))

		WidgetSpecificationFactory->AddWidgetSpecification(WidgetSpecification);

		GameInstance->SetCommandFactory(CommandFactory);
		WidgetManager->SetWidgetSpecificationFactory(WidgetSpecificationFactory);

		return true;
	});

	AfterEach([this]()
	{
		SelectionWidget = nullptr;

		SelectionComponent = nullptr;

		TestWorld->DestroyActor(Character);

		WidgetSpecification = nullptr;
		WidgetSpecificationFactory = nullptr;

		DetachCommand = nullptr;
		AttachCommand = nullptr;
		SelectCommand = nullptr;
		CommandFactory = nullptr;

		WidgetManager = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ComponentClass : ComponentClasses)
	{
		Describe("[" + ComponentClass->GetName() + "]", [this, ComponentClass]()
		{
			It(
				"Given initialization, expect the selection component to attach a new selection widget",
				[this, ComponentClass]()
			{
				SelectionComponent = NewObject<UBBSelectionComponent>(Character, ComponentClass);

				UTEST_TRUE("Selection Component is valid", IsValid(SelectionComponent))

				Character->AddOwnedComponent(SelectionComponent);
				SelectionComponent->RegisterComponent();

				SelectionComponent->Initialize(Character);

				TEST_TRUE(SelectionComponent->GetWidget() == nullptr)

				Character->UpdateSelection(true);

				TEST_TRUE(SelectionComponent->GetWidget() == SelectionWidget)

				Character->UpdateSelection(false);

				SelectionComponent->Finalize();

				return true;
			});

			It(
				"Given finalization, expect the selection component to detach its selection widget",
				[this, ComponentClass]()
			{
				SelectionComponent = NewObject<UBBSelectionComponent>(Character, ComponentClass);

				UTEST_TRUE("Selection Component is valid", IsValid(SelectionComponent))

				Character->AddOwnedComponent(SelectionComponent);
				SelectionComponent->RegisterComponent();

				SelectionComponent->Initialize(Character);

				Character->UpdateSelection(true);

				TEST_TRUE(SelectionComponent->GetWidget() != nullptr)

				Character->UpdateSelection(false);

				TEST_TRUE(SelectionComponent->GetWidget() == nullptr)

				SelectionComponent->Finalize();

				return true;
			});

			It(
				"Given a new selectable, expect the selection component to set its command's selectable",
				[this, ComponentClass]()
			{
				SelectionComponent = NewObject<UBBSelectionComponent>(Character, ComponentClass);

				UTEST_TRUE("Selection Component is valid", IsValid(SelectionComponent))

				Character->AddOwnedComponent(SelectionComponent);
				SelectionComponent->RegisterComponent();

				SelectionComponent->Initialize(Character);

				TArray<ABBCharacterStub *> Selectables;

				for (int i = 0; i < 5; i++)
				{
					ABBCharacterStub * Selectable = TestWorld->SpawnActor<ABBCharacterStub>(
						ABBCharacterStub::StaticClass(),
						SpawnParameters
					);

					UTEST_TRUE("Selectable is valid", IsValid(Selectable))

					Selectables.Emplace(Selectable);
				}

				for (ABBCharacterStub * & Selectable : Selectables)
				{
					SelectionComponent->SetSelectable(TScriptInterface<IBBSelectable>(Selectable));

					TEST_TRUE(SelectCommand->GetSelectable()->ToActor() == Selectable)
				}

				SelectionComponent->Finalize();

				for (ABBCharacterStub * & Selectable : Selectables)
				{
					TestWorld->DestroyActor(Selectable);
				}

				return true;
			});

			It(
				"Given a left click on a subscribed selectable, expect the selection component to execute its command",
				[this, ComponentClass]()
			{
				SelectionComponent = NewObject<UBBSelectionComponent>(Character, ComponentClass);

				UTEST_TRUE("Selection Component is valid", IsValid(SelectionComponent))

				Character->AddOwnedComponent(SelectionComponent);
				SelectionComponent->RegisterComponent();

				SelectionComponent->Initialize(Character);

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					Character->LeftClick();

					TEST_TRUE(SelectCommand->GetNumExecutions() == Clicks)
				}

				SelectionComponent->Finalize();

				return true;
			});

			It(
				"Given a left click on an unsubscribed selectable, expect the selection component not to execute its \
				command",
				[this, ComponentClass]()
			{
				SelectionComponent = NewObject<UBBSelectionComponent>(Character, ComponentClass);

				UTEST_TRUE("Selection Component is valid", IsValid(SelectionComponent))

				Character->AddOwnedComponent(SelectionComponent);
				SelectionComponent->RegisterComponent();

				SelectionComponent->Initialize(Character);

				SelectionComponent->Finalize();

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					Character->LeftClick();

					TEST_TRUE(SelectCommand->GetNumExecutions() == 0)
				}

				return true;
			});
		});
	}
}