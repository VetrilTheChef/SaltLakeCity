// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Actors/Buildings/BBBuildingStub.h"
#include "Commands/GameStates/BBSelectCommand.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameStates/BBGameStateStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBSelectCommandSpec,
	"SaltLakeCity.Commands.GameStates.SelectCommand",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBGameStateStub * GameState;

	UPROPERTY()
	TArray<UClass *> CommandClasses;

	// SUT
	UPROPERTY()
	UBBSelectCommand * Command = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBSelectCommandSpec)

void UBBSelectCommandSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBSelectCommand>(FString(TEXT("/Game/Commands/GameStates")), CommandClasses);

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

		TestWorld->SetGameState(GameState);

		return true;
	});

	AfterEach([this]()
	{
		Command = nullptr;

		TestWorld->DestroyActor(GameState);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & CommandClass : CommandClasses)
	{
		Describe("[" + CommandClass->GetName() + "]", [this, CommandClass]()
		{
			It("Given a new selectable actor, expect the command to notify the game state upon execution", [this, CommandClass]()
			{
				Command = NewObject<UBBSelectCommand>(TestWorld, CommandClass);

				UTEST_TRUE("Command is valid", IsValid(Command))

				TArray<TScriptInterface<IBBSelectable>> Selectables;
				Selectables.Empty();
				Selectables.Emplace(TScriptInterface<IBBSelectable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				Selectables.Emplace(TScriptInterface<IBBSelectable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				Selectables.Emplace(TScriptInterface<IBBSelectable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				Selectables.Emplace(TScriptInterface<IBBSelectable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				Selectables.Emplace(TScriptInterface<IBBSelectable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));

				Command->SetGameState(GameState);

				for (TScriptInterface<IBBSelectable> & Selectable : Selectables)
				{
					Command->SetSelectable(Forward<TScriptInterface<IBBSelectable>>(Selectable));

					Command->Execute();

					TEST_TRUE(GameState->GetSelection() == Selectable)
				}

				for (TScriptInterface<IBBSelectable> & Selectable : Selectables)
				{
					TestWorld->DestroyActor(Selectable->ToActor());
				}

				return true;
			});
		});
	}
}