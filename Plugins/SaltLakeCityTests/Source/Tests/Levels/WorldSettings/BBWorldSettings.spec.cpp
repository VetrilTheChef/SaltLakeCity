// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Landscape.h"
#include "Controllers/BBPlayerControllerStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameModes/BBGameModeStub.h"
#include "GameStates/BBGameStateStub.h"
#include "GUI/BBHUDStub.h"
#include "Levels/WorldSettings/BBWorldSettings.h"
#include "Levels/BBLevelScriptActorStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBWorldSettingsSpec,
	"SaltLakeCity.Levels.WorldSettings.WorldSettings",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBPlayerControllerStub * PlayerController = nullptr;

	UPROPERTY()
	AIBBHUD * HUD = nullptr;

	UPROPERTY()
	ABBGameModeStub * GameMode = nullptr;

	UPROPERTY()
	ABBGameStateStub * GameState = nullptr;

	UPROPERTY()
	ABBLevelScriptActorStub * LevelScriptActor = nullptr;

	UPROPERTY()
	TArray<UClass *> WorldSettingsClasses;

	// SUT
	UPROPERTY()
	ABBWorldSettings * WorldSettings = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBWorldSettingsSpec)

void UBBWorldSettingsSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBWorldSettings>(FString(TEXT("/Game/Levels/WorldSettings")), WorldSettingsClasses);

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

		LevelScriptActor = TestWorld->SpawnActor<ABBLevelScriptActorStub>(ABBLevelScriptActorStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Level Script Actor is valid", IsValid(LevelScriptActor))

		CurrentLevel->LevelScriptActor = LevelScriptActor;

		TActorIterator<ALandscape> It = TActorIterator<ALandscape>(TestWorld, ALandscape::StaticClass()) ;

		UTEST_TRUE("Landscape is valid", IsValid(* It))

		LevelScriptActor->SetLandscape(Cast<ALandscape>(* It));

		LevelScriptActor->SetLevelBounds(FVector(1000.0f, 1000.0f, 500.0f));

		PlayerController = NewObject<ABBPlayerControllerStub>(GameInstance, ABBPlayerControllerStub::StaticClass());

		UTEST_TRUE("Player Controller is valid", IsValid(PlayerController))
		
		GameInstance->SetPlayerController(PlayerController);

		HUD = NewObject<ABBHUDStub>(GameInstance, ABBHUDStub::StaticClass());

		UTEST_TRUE("HUD is valid", IsValid(HUD))

		PlayerController->MyHUD = HUD;

		GameMode = NewObject<ABBGameModeStub>(GameInstance, ABBGameModeStub::StaticClass());

		UTEST_TRUE("Game Mode is valid", IsValid(GameMode))

		GameInstance->SetGameMode(GameMode);

		GameState = NewObject<ABBGameStateStub>(GameInstance, ABBGameStateStub::StaticClass());

		UTEST_TRUE("Game State is valid", IsValid(GameState))

		GameInstance->SetGameState(GameState);

		return true;
	});

	AfterEach([this]()
	{
		TestWorld->DestroyActor(WorldSettings);

		TestWorld->DestroyActor(LevelScriptActor);
		GameState = nullptr;
		GameMode = nullptr;
		HUD = nullptr;
		PlayerController = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & WorldSettingsClass : WorldSettingsClasses)
	{
		Describe("[" + WorldSettingsClass->GetName() + "]", [this, WorldSettingsClass]()
		{
			It("Given a new begin play notification, expect the world settings to initialize player controller, HUD, game mode, game state, level script actor, and game instance.", [this, WorldSettingsClass]()
			{
				TEST_TRUE(PlayerController->HasActorBegunPlay() == false)
				TEST_TRUE(HUD->HasActorBegunPlay() == false)
				TEST_TRUE(GameMode->HasActorBegunPlay() == false)
				TEST_TRUE(GameState->HasActorBegunPlay() == false)
				TEST_TRUE(LevelScriptActor->HasActorBegunPlay() == false)

				WorldSettings = TestWorld->SpawnActor<ABBWorldSettings>(WorldSettingsClass, SpawnParameters);

				UTEST_TRUE("World Settings is valid", IsValid(WorldSettings))

				TEST_TRUE(PlayerController->HasActorBegunPlay() == true)
				TEST_TRUE(HUD->HasActorBegunPlay() == true)
				TEST_TRUE(GameMode->HasActorBegunPlay() == true)
				TEST_TRUE(GameState->HasActorBegunPlay() == true)
				TEST_TRUE(LevelScriptActor->HasActorBegunPlay() == true)

				return true;
			});
		});
	}
}