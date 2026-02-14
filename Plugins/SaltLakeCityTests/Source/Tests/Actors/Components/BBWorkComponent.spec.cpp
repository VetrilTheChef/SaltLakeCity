// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/BBBuildTaskStub.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "Actors/Components/BBAIAbilityComponentStub.h"
#include "Actors/Components/BBWorkComponent.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameStates/BBGameStateStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBWorkComponentSpec,
	"SaltLakeCity.Actors.Components.WorkComponent",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBGameStateStub * GameState = nullptr;

	UPROPERTY()
	ABBCharacterStub * Character;

	UPROPERTY()
	UBBAIAbilityComponentStub * AbilityComponent;

	UPROPERTY()
	TArray<UClass *> ComponentClasses;

	// SUT
	UPROPERTY()
	UBBWorkComponent * WorkComponent = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBWorkComponentSpec)

void UBBWorkComponentSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBWorkComponent>(FString(TEXT("/Game/Actors/Components")), ComponentClasses);
	
	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		GameState = TestWorld->SpawnActor<ABBGameStateStub>(ABBGameStateStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Game State is valid", IsValid(GameState))

		GameInstance->SetGameState(GameState);

		Character = TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Character is valid", IsValid(Character))

		AbilityComponent = NewObject<UBBAIAbilityComponentStub>(Character, UBBAIAbilityComponentStub::StaticClass());

		UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))

		Character->AddOwnedComponent(AbilityComponent);
		AbilityComponent->RegisterComponent();

		return true;
	});

	AfterEach([this]()
	{
		WorkComponent = nullptr;

		AbilityComponent = nullptr;

		TestWorld->DestroyActor(Character);

		TestWorld->DestroyActor(GameState);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ComponentClass : ComponentClasses)
	{
		Describe("[" + ComponentClass->GetName() + "]", [this, ComponentClass]()
		{
			It("Given a new job, expect the component to update its job and notify the game state", [this, ComponentClass]()
			{
				WorkComponent = NewObject<UBBWorkComponent>(Character, ComponentClass);

				UTEST_TRUE("Work Component is valid", IsValid(WorkComponent))

				TArray<EBBJob> Jobs;
				Jobs.Emplace(EBBJob::Idle);
				Jobs.Emplace(EBBJob::None);
				Jobs.Emplace(EBBJob::Builder);
				Jobs.Emplace(EBBJob::Idle);
				Jobs.Emplace(EBBJob::Builder);

				for (EBBJob & Job : Jobs)
				{
					WorkComponent->SetJob(Job);

					TEST_TRUE(WorkComponent->GetJob() == Job)

					TArray<UIBBWorkComponent *> Consumers = GameState->GetConsumers(Job);

					TEST_TRUE(Consumers.Contains(WorkComponent))
				}

				return true;
			});

			It("Given a new assigned task, expect the component to update its task", [this, ComponentClass]()
			{
				WorkComponent = NewObject<UBBWorkComponent>(Character, ComponentClass);

				UTEST_TRUE("Work Component is valid", IsValid(WorkComponent))

				Character->AddOwnedComponent(WorkComponent);
				WorkComponent->RegisterComponent();
				
				WorkComponent->Initialize(TScriptInterface<IBBWorkable>(Character), AbilityComponent, EBBJob::Builder);

				for (int Work = 0; Work < 6; Work++)
				{
					UBBBuildTaskStub * BuildTask = NewObject<UBBBuildTaskStub>(WorkComponent, UBBBuildTaskStub::StaticClass());

					UTEST_TRUE("Build Task is valid", IsValid(BuildTask))

					TEST_TRUE(WorkComponent->GetTask() == nullptr)

					WorkComponent->AssignTask(BuildTask);

					TEST_TRUE(WorkComponent->GetTask() == BuildTask)

					WorkComponent->UnassignTask();
				}

				WorkComponent->Finalize();

				return true;
			});

			It("Given a new unassigned task, expect the component to clear its task", [this, ComponentClass]()
			{
				WorkComponent = NewObject<UBBWorkComponent>(Character, ComponentClass);

				UTEST_TRUE("Work Component is valid", IsValid(WorkComponent))

				Character->AddOwnedComponent(WorkComponent);
				WorkComponent->RegisterComponent();

				WorkComponent->Initialize(TScriptInterface<IBBWorkable>(Character), AbilityComponent, EBBJob::Builder);

				for (int Work = 0; Work < 6; Work++)
				{
					UBBBuildTaskStub * BuildTask = NewObject<UBBBuildTaskStub>(WorkComponent, UBBBuildTaskStub::StaticClass());

					UTEST_TRUE("Build Task is valid", IsValid(BuildTask))

					WorkComponent->AssignTask(BuildTask);

					TEST_TRUE(WorkComponent->GetTask() != nullptr)

					WorkComponent->UnassignTask();

					TEST_TRUE(WorkComponent->GetTask() == nullptr)
				}

				WorkComponent->Finalize();

				return true;
			});

			It("Given a new request to start working, expect the component to run its task", [this, ComponentClass]()
			{
				WorkComponent = NewObject<UBBWorkComponent>(Character, ComponentClass);

				UTEST_TRUE("Work Component is valid", IsValid(WorkComponent))

				Character->AddOwnedComponent(WorkComponent);
				WorkComponent->RegisterComponent();
				
				WorkComponent->Initialize(TScriptInterface<IBBWorkable>(Character), AbilityComponent, EBBJob::Builder);

				for (int Work = 0; Work < 6; Work++)
				{
					UBBBuildTaskStub * BuildTask = NewObject<UBBBuildTaskStub>(WorkComponent, UBBBuildTaskStub::StaticClass());

					UTEST_TRUE("Build Task is valid", IsValid(BuildTask))

					WorkComponent->AssignTask(BuildTask);
					WorkComponent->StartTask();

					TEST_TRUE(WorkComponent->IsWorking())
					TEST_TRUE(WorkComponent->GetTask() == BuildTask)
					TEST_TRUE(AbilityComponent->IsRunningTask())
					TEST_TRUE(AbilityComponent->GetCurrentTask() == BuildTask)

					WorkComponent->StopTask();
				}

				WorkComponent->Finalize();

				return true;
			});

			It("Given a new request to stop working, expect the component to stop running its task", [this, ComponentClass]()
			{
				WorkComponent = NewObject<UBBWorkComponent>(Character, ComponentClass);

				UTEST_TRUE("Character is valid", IsValid(Character))

				Character->AddOwnedComponent(WorkComponent);
				WorkComponent->RegisterComponent();
				
				WorkComponent->Initialize(TScriptInterface<IBBWorkable>(Character), AbilityComponent, EBBJob::Builder);

				for (int Work = 0; Work < 6; Work++)
				{
					UBBBuildTaskStub * BuildTask = NewObject<UBBBuildTaskStub>(WorkComponent, UBBBuildTaskStub::StaticClass());

					UTEST_TRUE("Build Task is valid", IsValid(BuildTask))

					WorkComponent->AssignTask(BuildTask);
					WorkComponent->StartTask();
					WorkComponent->StopTask();

					TEST_FALSE(WorkComponent->IsWorking())
					TEST_TRUE(WorkComponent->GetTask() == BuildTask)
					TEST_FALSE(AbilityComponent->IsRunningTask())
					TEST_TRUE(AbilityComponent->GetCurrentTask() == nullptr)
				}

				return true;
			});
		});
	}
}