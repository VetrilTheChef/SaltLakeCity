// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "Actors/Components/BBContextComponent.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/GameStates/BBSetContextCommandStub.h"
#include "Commands/GUI/BBCloseWidgetCommandStub.h"
#include "Commands/GUI/BBOpenWidgetCommandStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBHUDStub.h"
#include "Specifications/GUI/Factories/BBWidgetSpecificationFactoryStub.h"
#include "Specifications/GUI/BBWidgetSpecificationStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBContextComponentSpec, "SaltLakeCity.Actors.Components.ContextComponent", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBHUDStub * HUD = nullptr;

	UPROPERTY()
	ABBCharacterStub * Character = nullptr;

	UPROPERTY()
	UBBCommandFactoryStub * CommandFactory = nullptr;

	UPROPERTY()
	UBBCloseWidgetCommandStub * CloseCommand = nullptr;

	UPROPERTY()
	UBBOpenWidgetCommandStub * OpenCommand = nullptr;

	UPROPERTY()
	UBBSetContextCommandStub * ContextCommand = nullptr;

	UPROPERTY()
	UBBWidgetSpecificationFactoryStub * WidgetSpecificationFactory = nullptr;

	UPROPERTY()
	UBBWidgetSpecificationStub * WidgetSpecification = nullptr;

	UPROPERTY()
	TArray<UClass *> ComponentClasses;

	// SUT
	UPROPERTY()
	UBBContextComponent * ContextComponent = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBContextComponentSpec)

void UBBContextComponentSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBContextComponent>(FString(TEXT("/Game/Actors/Components")), ComponentClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		CommandFactory = NewObject<UBBCommandFactoryStub>(TestWorld, UBBCommandFactoryStub::StaticClass());

		UTEST_TRUE("Command Factory is valid", IsValid(CommandFactory))

		CloseCommand = NewObject<UBBCloseWidgetCommandStub>(CommandFactory, UBBCloseWidgetCommandStub::StaticClass());

		UTEST_TRUE("Close Command is valid", IsValid(CloseCommand))

		CommandFactory->AddCloseWidgetCommand(CloseCommand);

		OpenCommand = NewObject<UBBOpenWidgetCommandStub>(CommandFactory, UBBOpenWidgetCommandStub::StaticClass());

		UTEST_TRUE("Open Command is valid", IsValid(OpenCommand))

		CommandFactory->AddOpenWidgetCommand(OpenCommand);

		ContextCommand = NewObject<UBBSetContextCommandStub>(CommandFactory, UBBSetContextCommandStub::StaticClass());

		UTEST_TRUE("Context Command is valid", IsValid(ContextCommand))

		CommandFactory->AddSetContextCommand(ContextCommand);

		WidgetSpecificationFactory = NewObject<UBBWidgetSpecificationFactoryStub>(TestWorld, UBBWidgetSpecificationFactoryStub::StaticClass());

		UTEST_TRUE("Widget Specification Factory is valid", IsValid(WidgetSpecificationFactory))

		WidgetSpecification = NewObject<UBBWidgetSpecificationStub>(TestWorld, UBBWidgetSpecificationStub::StaticClass());

		UTEST_TRUE("Widget Specification is valid", IsValid(WidgetSpecificationFactory))

		WidgetSpecificationFactory->AddWidgetSpecification(WidgetSpecification);

		Character = TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Character is valid", IsValid(Character))
			
		HUD = TestWorld->SpawnActor<ABBHUDStub>(ABBHUDStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("HUD is valid", IsValid(HUD))

		HUD->SetWidgetSpecificationFactory(WidgetSpecificationFactory);

		GameInstance->SetCommandFactory(CommandFactory);
		GameInstance->SetHUD(HUD);

		return true;
	});

	AfterEach([this]()
	{
		ContextComponent = nullptr;

		TestWorld->DestroyActor(Character);

		TestWorld->DestroyActor(HUD);

		WidgetSpecification = nullptr;
		WidgetSpecificationFactory = nullptr;

		ContextCommand = nullptr;
		CloseCommand = nullptr;
		OpenCommand = nullptr;
		CommandFactory = nullptr;
		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ComponentClass : ComponentClasses)
	{
		Describe("[" + ComponentClass->GetName() + "]", [this, ComponentClass]()
		{
			It("Given a contextualization on a subscribed character, expect the component to notify the HUD", [this, ComponentClass]()
			{
				ContextComponent = NewObject<UBBContextComponent>(Character, ComponentClass);

				UTEST_TRUE("Context Component is valid", IsValid(ContextComponent))

				Character->AddOwnedComponent(ContextComponent);
				ContextComponent->RegisterComponent();

				ContextComponent->Initialize(TScriptInterface<IBBContextualizable>(Character));

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					Character->UpdateContext(true);

					TEST_TRUE(OpenCommand->GetNumExecutions() == Clicks)
				}

				ContextComponent->Finalize();

				ContextComponent->UnregisterComponent();
				Character->RemoveOwnedComponent(ContextComponent);

				ContextComponent->EndPlay(EEndPlayReason::Destroyed);

				return true;
			});

			It("Given a contextualization on an unsubscribed character, expect the component not to notify the HUD", [this, ComponentClass]()
			{
				ABBCharacterStub * OtherCharacter = TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters);

				UTEST_TRUE("Other Character is valid", IsValid(OtherCharacter))
				
				ContextComponent = NewObject<UBBContextComponent>(Character, ComponentClass);

				UTEST_TRUE("Context Component is valid", IsValid(ContextComponent))

				Character->AddOwnedComponent(ContextComponent);
				ContextComponent->RegisterComponent();

				ContextComponent->Initialize(TScriptInterface<IBBContextualizable>(Character));

				ContextComponent->Finalize();

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					Character->UpdateContext(true);
				}

				TEST_TRUE(OpenCommand->GetNumExecutions() == 0)

				ContextComponent->UnregisterComponent();
				Character->RemoveOwnedComponent(ContextComponent);

				ContextComponent->EndPlay(EEndPlayReason::Destroyed);

				TestWorld->DestroyActor(OtherCharacter);

				return true;
			});

			It("Given a decontextualization on a subscribed character, expect the component to notify the HUD", [this, ComponentClass]()
			{
				ContextComponent = NewObject<UBBContextComponent>(Character, ComponentClass);

				UTEST_TRUE("Context Component is valid", IsValid(ContextComponent))

				Character->AddOwnedComponent(ContextComponent);
				ContextComponent->RegisterComponent();

				ContextComponent->Initialize(TScriptInterface<IBBContextualizable>(Character));

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					Character->UpdateContext(false);

					TEST_TRUE(CloseCommand->GetNumExecutions() == Clicks)
				}

				ContextComponent->Finalize();

				ContextComponent->UnregisterComponent();
				Character->RemoveOwnedComponent(ContextComponent);

				ContextComponent->EndPlay(EEndPlayReason::Destroyed);

				return true;
			});

			It("Given a decontextualization on an unsubscribed character, expect the component not to notify the HUD", [this, ComponentClass]()
			{
				ABBCharacterStub * OtherCharacter = TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters);

				UTEST_TRUE("Other Character is valid", IsValid(OtherCharacter))
				
				ContextComponent = NewObject<UBBContextComponent>(Character, ComponentClass);

				UTEST_TRUE("Context Component is valid", IsValid(ContextComponent))

				Character->AddOwnedComponent(ContextComponent);
				ContextComponent->RegisterComponent();

				ContextComponent->Initialize(TScriptInterface<IBBContextualizable>(Character));

				ContextComponent->Finalize();

				for (int Clicks = 1; Clicks < 6; Clicks++)
				{
					Character->UpdateContext(false);
				}

				TEST_TRUE(CloseCommand->GetNumExecutions() == 0)

				ContextComponent->UnregisterComponent();
				Character->RemoveOwnedComponent(ContextComponent);

				ContextComponent->EndPlay(EEndPlayReason::Destroyed);

				TestWorld->DestroyActor(OtherCharacter);

				return true;
			});

			It("Given a list of valid context options, expect the component to filter any passed options", [this, ComponentClass]()
			{
				ContextComponent = NewObject<UBBContextComponent>(Character, ComponentClass);

				UTEST_TRUE("Context Component is valid", IsValid(ContextComponent))

				Character->AddOwnedComponent(ContextComponent);
				ContextComponent->RegisterComponent();

				ContextComponent->Initialize(TScriptInterface<IBBContextualizable>(Character));

				Character->SetContextOptions(TSet<EBBContext>{ EBBContext::Dossier });

				TEST_TRUE(ContextComponent->IsOption(EBBContext::Build) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Dossier) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Job) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::None) == false);

				Character->SetContextOptions(TSet<EBBContext>{ EBBContext::Build, EBBContext::Dossier });

				TEST_TRUE(ContextComponent->IsOption(EBBContext::Build) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Dossier) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Job) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::None) == false);

				Character->SetContextOptions(TSet<EBBContext>{ EBBContext::Job, EBBContext::None });

				TEST_TRUE(ContextComponent->IsOption(EBBContext::Build) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Dossier) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Job) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::None) == true);

				Character->SetContextOptions(TSet<EBBContext>{ EBBContext::Dossier, EBBContext::Job });

				TEST_TRUE(ContextComponent->IsOption(EBBContext::Build) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Dossier) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Job) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::None) == false);

				Character->SetContextOptions(TSet<EBBContext>{ EBBContext::Dossier, EBBContext::None });

				TEST_TRUE(ContextComponent->IsOption(EBBContext::Build) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Dossier) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Job) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::None) == true);

				Character->SetContextOptions(TSet<EBBContext>{ EBBContext::Build, EBBContext::Job });

				TEST_TRUE(ContextComponent->IsOption(EBBContext::Build) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Dossier) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Job) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::None) == false);

				Character->SetContextOptions(TSet<EBBContext>{ EBBContext::Build, EBBContext::None });

				TEST_TRUE(ContextComponent->IsOption(EBBContext::Build) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Dossier) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Job) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::None) == true);

				Character->SetContextOptions(TSet<EBBContext>{ });

				TEST_TRUE(ContextComponent->IsOption(EBBContext::Build) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Dossier) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Job) == false);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::None) == false);

				Character->SetContextOptions(TSet<EBBContext>{ EBBContext::Build, EBBContext::Dossier, EBBContext::Job, EBBContext::None });

				TEST_TRUE(ContextComponent->IsOption(EBBContext::Build) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Dossier) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::Job) == true);
				TEST_TRUE(ContextComponent->IsOption(EBBContext::None) == true);

				ContextComponent->Finalize();

				ContextComponent->UnregisterComponent();
				Character->RemoveOwnedComponent(ContextComponent);

				ContextComponent->EndPlay(EEndPlayReason::Destroyed);

				return true;
			});
		});
	}
}