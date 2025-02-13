// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Landscape.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameStates/BBGameState.h"
#include "Levels/BBLevelScriptActorStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBGameStateSpec, "SaltLakeCity.GameStates.GameState", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> GameStateClasses;

	// SUT
	UPROPERTY()
	ABBGameState * GameState = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBGameStateSpec)

void UBBGameStateSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBGameState>(FString(TEXT("/Game/GameStates")), GameStateClasses);

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

		TActorIterator<ALandscape> It = TActorIterator<ALandscape>(TestWorld, ALandscape::StaticClass()) ;

		UTEST_TRUE("Landscape is valid", IsValid(* It))

		LevelScriptActor->SetLandscape(Cast<ALandscape>(* It));

		LevelScriptActor->SetLevelBounds(FVector(1000.0f, 1000.0f, 500.0f));

		return true;
	});

	AfterEach([this]()
	{
		TestWorld->DestroyActor(GameState);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & GameStateClass : GameStateClasses)
	{
		Describe("[" + GameStateClass->GetName() + "]", [this, GameStateClass]()
		{
			It("Given a new selected actor, expect the game state to set its selected actor", [this, GameStateClass]()
			{
				GameState = TestWorld->SpawnActor<ABBGameState>(GameStateClass, SpawnParameters);

				UTEST_TRUE("Game State is valid", IsValid(GameState))

				TArray<ABBCharacterStub *> Characters;
				Characters.Emplace(TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters));
				Characters.Emplace(TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters));
				Characters.Emplace(TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters));
				Characters.Emplace(TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters));
				Characters.Emplace(TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters));

				for (ABBCharacterStub * & Character : Characters)
				{
					GameState->SetSelection(TScriptInterface<IBBSelectable>(Character));

					TEST_TRUE(GameState->GetSelection().GetObject() == Character);
				}

				for (ABBCharacterStub * & Character : Characters)
				{
					TestWorld->DestroyActor(Character);

					Character = nullptr;
				}

				return true;
			});
		});
	}
}