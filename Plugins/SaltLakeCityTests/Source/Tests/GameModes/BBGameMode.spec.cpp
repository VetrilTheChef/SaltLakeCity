// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Landscape.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameModes/BBGameMode.h"
#include "GameStates/BBGameStateStub.h"
#include "Levels/BBLevelScriptActorStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBGameModeSpec, "SaltLakeCity.GameModes.GameMode", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> GameModeClasses;

	// SUT
	UPROPERTY()
	ABBGameMode * GameMode = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBGameModeSpec)

void UBBGameModeSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBGameMode>(FString(TEXT("/Game/GameModes")), GameModeClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		ULevel * CurrentLevel = TestWorld->GetCurrentLevel();

		UTEST_TRUE("Current Level is valid", IsValid(CurrentLevel))

		ABBLevelScriptActorStub * LevelScriptActor = NewObject<ABBLevelScriptActorStub>(CurrentLevel, ABBLevelScriptActorStub::StaticClass());

		UTEST_TRUE("Level Script Actor is valid", IsValid(LevelScriptActor))

		CurrentLevel->LevelScriptActor = LevelScriptActor;

		TActorIterator<ALandscape> It = TActorIterator<ALandscape>(TestWorld, ALandscape::StaticClass());

		UTEST_TRUE("Landscape is valid", IsValid(*It))

		LevelScriptActor->SetLandscape(Cast<ALandscape>(*It));

		LevelScriptActor->SetLevelBounds(FVector(1000.0f, 1000.0f, 500.0f));

		return true;
	});

	AfterEach([this]()
	{
		TestWorld->DestroyActor(GameMode);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & GameModeClass : GameModeClasses)
	{
		Describe("[" + GameModeClass->GetName() + "]", [this, GameModeClass]()
		{
			It("Given a new active game mode, expect the game mode to broadcast the event", [this, GameModeClass]()
			{
				GameMode = TestWorld->SpawnActor<ABBGameMode>(GameModeClass, SpawnParameters);

				UTEST_TRUE("Game Mode is valid", IsValid(GameMode))

				ABBGameStateStub * GameState = TestWorld->SpawnActor<ABBGameStateStub>(ABBGameStateStub::StaticClass(), SpawnParameters);

				UTEST_TRUE("Game State is valid", IsValid(GameState))

				GameMode->OnActiveModeUpdate().AddUObject(GameState, &ABBGameStateStub::UpdateActiveMode);

				TArray<EBBGameMode> ActiveGameModes;
				ActiveGameModes.Emplace(EBBGameMode::Build);
				ActiveGameModes.Emplace(EBBGameMode::None);
				ActiveGameModes.Emplace(EBBGameMode::Play);
				ActiveGameModes.Emplace(EBBGameMode::Build);
				ActiveGameModes.Emplace(EBBGameMode::Play);

				for (EBBGameMode & ActiveGameMode : ActiveGameModes)
				{
					GameMode->SetMode(ActiveGameMode);

					TEST_TRUE(GameState->GetActiveMode() == ActiveGameMode)
				}

				GameMode->OnActiveModeUpdate().RemoveAll(GameState);

				TestWorld->DestroyActor(GameState);

				return true;
			});
		});
	}
}