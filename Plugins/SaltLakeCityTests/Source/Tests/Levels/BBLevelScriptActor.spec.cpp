// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Landscape.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameStates/Components/BBGameClockStub.h"
#include "Levels/BBLevelScriptActor.h"
#include "Lighting/BBLightingCycleStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBLevelScriptActorSpec, "SaltLakeCity.Levels.LevelScriptActor", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> LevelScriptActorClasses;

	// SUT
	UPROPERTY()
	ABBLevelScriptActor * LevelScriptActor = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBLevelScriptActorSpec)

void UBBLevelScriptActorSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBLevelScriptActor>(FString(TEXT("/Game/Levels")), LevelScriptActorClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		return true;
	});

	AfterEach([this]()
	{
		TestWorld->DestroyActor(LevelScriptActor);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & LevelScriptActorClass : LevelScriptActorClasses)
	{
		Describe("[" + LevelScriptActorClass->GetName() + "]", [this, LevelScriptActorClass]()
		{
			It("Given initialization, expect the level script actor to initialize its lighting cycle", [this, LevelScriptActorClass]()
			{
				LevelScriptActor = TestWorld->SpawnActor<ABBLevelScriptActor>(LevelScriptActorClass, SpawnParameters);

				UTEST_TRUE("Level Script Actor is valid", IsValid(LevelScriptActor))

				for (int Index = 0; Index < 5; Index++)
				{
					UBBLightingCycleStub * LightingCycle = NewObject<UBBLightingCycleStub>(LevelScriptActor, UBBLightingCycleStub::StaticClass());

					UTEST_TRUE("Lighting Cycle is valid", IsValid(LightingCycle))

					LevelScriptActor->SetLightingCycle(LightingCycle);

					UBBGameClockStub * GameClock = NewObject<UBBGameClockStub>(LevelScriptActor);

					UTEST_TRUE("Game Clock is valid", IsValid(GameClock))

					LevelScriptActor->Initialize(GameClock);

					TEST_TRUE(LightingCycle->GetLevelScriptActor() == LevelScriptActor)
					TEST_TRUE(LightingCycle->GetGameClock() == GameClock)

					LevelScriptActor->Finalize();
				}

				return true;
			});

			It("Given finalization, expect the level script actor to finalize its lighting cycle", [this, LevelScriptActorClass]()
			{
				LevelScriptActor = TestWorld->SpawnActor<ABBLevelScriptActor>(LevelScriptActorClass, SpawnParameters);

				UTEST_TRUE("Level Script Actor is valid", IsValid(LevelScriptActor))

				for (int Index = 0; Index < 5; Index++)
				{
					UBBLightingCycleStub * LightingCycle = NewObject<UBBLightingCycleStub>(LevelScriptActor, UBBLightingCycleStub::StaticClass());

					UTEST_TRUE("Lighting Cycle is valid", IsValid(LightingCycle))

					LevelScriptActor->SetLightingCycle(LightingCycle);

					UBBGameClockStub * GameClock = NewObject<UBBGameClockStub>(LevelScriptActor);

					UTEST_TRUE("Game Clock is valid", IsValid(GameClock))

					LevelScriptActor->Initialize(GameClock);

					LevelScriptActor->Finalize();

					TEST_TRUE(LightingCycle->GetLevelScriptActor() == nullptr)
					TEST_TRUE(LightingCycle->GetGameClock() == nullptr)
				}

				return true;
			});

			It("Given a new tick, expect the level script actor to tick its initialized lighting cycle", [this, LevelScriptActorClass]()
			{
				LevelScriptActor = TestWorld->SpawnActor<ABBLevelScriptActor>(LevelScriptActorClass, SpawnParameters);

				UTEST_TRUE("Level Script Actor is valid", IsValid(LevelScriptActor))

				UBBLightingCycleStub * LightingCycle = NewObject<UBBLightingCycleStub>(LevelScriptActor, UBBLightingCycleStub::StaticClass());

				UTEST_TRUE("Lighting Cycle is valid", IsValid(LightingCycle))

				LevelScriptActor->SetLightingCycle(LightingCycle);

				UBBGameClockStub * GameClock = NewObject<UBBGameClockStub>(LevelScriptActor);

				UTEST_TRUE("Game Clock is valid", IsValid(GameClock))

				LevelScriptActor->Initialize(GameClock);

				TEST_TRUE(LightingCycle->GetNumTicks() == 0)

				for (int Ticks = 1; Ticks < 6; Ticks++)
				{
					LevelScriptActor->Tick(0.001f);

					TEST_TRUE(LightingCycle->GetNumTicks() == Ticks)
				}

				LevelScriptActor->Finalize();

				return true;
			});

			It("Given a new tick, expect the level script actor not to tick its finalized lighting cycle", [this, LevelScriptActorClass]()
			{
				LevelScriptActor = TestWorld->SpawnActor<ABBLevelScriptActor>(LevelScriptActorClass, SpawnParameters);

				UTEST_TRUE("Level Script Actor is valid", IsValid(LevelScriptActor))

				UBBLightingCycleStub * LightingCycle = NewObject<UBBLightingCycleStub>(LevelScriptActor, UBBLightingCycleStub::StaticClass());

				UTEST_TRUE("Lighting Cycle is valid", IsValid(LightingCycle))

				LevelScriptActor->SetLightingCycle(LightingCycle);

				UBBGameClockStub * GameClock = NewObject<UBBGameClockStub>(LevelScriptActor);

				UTEST_TRUE("Game Clock is valid", IsValid(GameClock))

				LevelScriptActor->Initialize(GameClock);

				LevelScriptActor->Finalize();

				TEST_TRUE(LightingCycle->GetNumTicks() == -1)

				for (int Ticks = 1; Ticks < 6; Ticks++)
				{
					LevelScriptActor->Tick(0.001f);

					TEST_TRUE(LightingCycle->GetNumTicks() == -1)
				}

				return true;
			});
		});
	}
}