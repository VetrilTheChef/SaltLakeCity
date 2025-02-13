// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/Factories/Interfaces/IBBComponentFactory.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Controllers/BBPlayerControllerStub.h"
#include "GameInstances/BBGameInstance.h"
#include "GameModes/BBGameModeStub.h"
#include "GameStates/BBGameStateStub.h"
#include "GUI/BBHUDStub.h"
#include "Specifications/Factories/Interfaces/IBBSpecificationFactory.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBGameInstanceSpec, "SaltLakeCity.GameInstances.GameInstance", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	ABBGameModeStub * GameMode = nullptr;

	UPROPERTY()
	ABBGameStateStub * GameState = nullptr;

	UPROPERTY()
	ABBHUDStub * HUD = nullptr;

	UPROPERTY()
	ABBPlayerControllerStub * PlayerController = nullptr;

	UPROPERTY()
	TArray<UClass *> GameInstanceClasses;

	// SUT
	UPROPERTY()
	UBBGameInstance * GameInstance = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBGameInstanceSpec)

void UBBGameInstanceSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBGameInstance>(FString(TEXT("/Game/GameInstances")), GameInstanceClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameMode = TestWorld->SpawnActor<ABBGameModeStub>(ABBGameModeStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Game Mode is valid", IsValid(GameMode))

		GameState = TestWorld->SpawnActor<ABBGameStateStub>(ABBGameStateStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Game State is valid", IsValid(GameState))

		HUD = TestWorld->SpawnActor<ABBHUDStub>(ABBHUDStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("HUD is valid", IsValid(HUD))

		PlayerController = TestWorld->SpawnActor<ABBPlayerControllerStub>(ABBPlayerControllerStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Player Controller is valid", IsValid(PlayerController))

		return true;
	});

	AfterEach([this]()
	{
		TestWorld->DestroyActor(GameMode);

		TestWorld->DestroyActor(GameState);

		TestWorld->DestroyActor(HUD);

		TestWorld->DestroyActor(PlayerController);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & GameInstanceClass : GameInstanceClasses)
	{
		Describe("[" + GameInstanceClass->GetName() + "]", [this, GameInstanceClass]()
		{
			It("Given creation, expect the game instance to initialize its factories", [this, GameInstanceClass]()
			{
				GameInstance = NewObject<UBBGameInstance>(TestWorld, GameInstanceClass);

				UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

				GameInstance->Init();

				TEST_TRUE(IsValid(GameInstance->GetCommandFactory()))

				TEST_TRUE(IsValid(GameInstance->GetComponentFactory()))

				TEST_TRUE(IsValid(GameInstance->GetSpecificationFactory()))

				GameInstance->Shutdown();

				return true;
			});

			It("Given initialization, expect the game instance to store the passed instances", [this, GameInstanceClass]()
			{
				GameInstance = NewObject<UBBGameInstance>(TestWorld, GameInstanceClass);

				UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

				GameInstance->Init();

				GameInstance->Initialize(TestWorld, GameMode, GameState, HUD, PlayerController);

				TEST_TRUE(GameInstance->GetGameMode() == GameMode)

				TEST_TRUE(GameInstance->GetGameState() == GameState)

				TEST_TRUE(GameInstance->GetHUD() == HUD)

				TEST_TRUE(GameInstance->GetPlayerController() == PlayerController)

				GameInstance->Finalize(TestWorld);

				GameInstance->Shutdown();

				return true;
			});

			It("Given initialization, expect the game instance to setup subscriptions to the passed instances events", [this, GameInstanceClass]()
			{
				TArray<EBBGameMode> ActiveGameModes;
				ActiveGameModes.Emplace(EBBGameMode::Play);
				ActiveGameModes.Emplace(EBBGameMode::Build);
				ActiveGameModes.Emplace(EBBGameMode::None);
				ActiveGameModes.Emplace(EBBGameMode::Play);
				ActiveGameModes.Emplace(EBBGameMode::Build);

				TArray<int> TargetFloorDeltas;
				TargetFloorDeltas.Emplace(1);
				TargetFloorDeltas.Emplace(-1);
				TargetFloorDeltas.Emplace(2);
				TargetFloorDeltas.Emplace(-1);
				TargetFloorDeltas.Emplace(-2);

				TArray<float> TargetFloorHeights;
				TargetFloorHeights.Emplace(124.02f);
				TargetFloorHeights.Emplace(-751.12f);
				TargetFloorHeights.Emplace(54.75f);
				TargetFloorHeights.Emplace(-952.65f);
				TargetFloorHeights.Emplace(-45.82f);

				GameInstance = NewObject<UBBGameInstance>(TestWorld, GameInstanceClass);

				UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

				GameInstance->Init();

				GameInstance->Initialize(TestWorld, GameMode, GameState, HUD, PlayerController);

				for (int Events = 1; Events < 6; Events++)
				{
					EBBGameMode ActiveGameMode = ActiveGameModes[Events - 1];
					int TargetFloorDelta = TargetFloorDeltas[Events - 1];
					float TargetFloorHeight = TargetFloorHeights[Events - 1];

					GameMode->SetMode(ActiveGameMode);
					GameMode->BroadcastActiveModeUpdate();

					TEST_TRUE(GameState->GetActiveMode() == ActiveGameMode);
					TEST_TRUE(HUD->GetActiveMode() == ActiveGameMode);
					TEST_TRUE(PlayerController->GetActiveMode() == ActiveGameMode);

					PlayerController->BroadcastFloorChangeRequest(TargetFloorDelta, TargetFloorHeight);

					TEST_TRUE(GameState->GetRequestedTargetFloorDelta() == TargetFloorDelta);
					TEST_TRUE(GameState->GetRequestedTargetFloorHeight() == TargetFloorHeight);
				}

				GameInstance->Finalize(TestWorld);

				GameInstance->Shutdown();

				return true;
			});
		});
	}
}