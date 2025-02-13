// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/Controllers/BBSpeedCommand.h"
#include "Controllers/BBPlayerControllerStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Levels/WorldSettings/BBWorldSettingsStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBSpeedCommandSpec, "SaltLakeCity.Commands.Controllers.SpeedCommand", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBWorldSettingsStub * WorldSettings = nullptr;

	UPROPERTY()
	ABBPlayerControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<UClass *> CommandClasses;

	// SUT
	UPROPERTY()
	UBBSpeedCommand * Command = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBSpeedCommandSpec)

void UBBSpeedCommandSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBSpeedCommand>(FString(TEXT("/Game/Commands/Controllers")), CommandClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		WorldSettings = TestWorld->SpawnActor<ABBWorldSettingsStub>(ABBWorldSettingsStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("World Settings is valid", IsValid(WorldSettings))

		WorldSettings->MinGlobalTimeDilation = 0.0f;
		WorldSettings->MaxGlobalTimeDilation = 100.0f;

		TestWorld->GetCurrentLevel()->SetWorldSettings(WorldSettings);

		Controller = TestWorld->SpawnActor<ABBPlayerControllerStub>(ABBPlayerControllerStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		return true;
	});

	AfterEach([this]()
	{
		Command = nullptr;

		TestWorld->DestroyActor(Controller);
		TestWorld->DestroyActor(WorldSettings);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & CommandClass : CommandClasses)
	{
		Describe("[" + CommandClass->GetName() + "]", [this, CommandClass]()
		{
			It("Given a new time dilation, expect the command to set it and unpause upon execution", [this, CommandClass]()
			{
				Command = NewObject<UBBSpeedCommand>(TestWorld, CommandClass);

				UTEST_TRUE("Command is valid", IsValid(Command))

				float MinTimeDilation = WorldSettings->MinGlobalTimeDilation;
				float MaxTimeDilation = WorldSettings->MaxGlobalTimeDilation;

				TArray<float> TimeDilations;
				TimeDilations.Empty();
				TimeDilations.Emplace(FMath::Clamp(1.73f, MinTimeDilation, MaxTimeDilation));
				TimeDilations.Emplace(FMath::Clamp(0.27f, MinTimeDilation, MaxTimeDilation));
				TimeDilations.Emplace(FMath::Clamp(5.31f, MinTimeDilation, MaxTimeDilation));
				TimeDilations.Emplace(FMath::Clamp(10.00f, MinTimeDilation, MaxTimeDilation));
				TimeDilations.Emplace(FMath::Clamp(0.04f, MinTimeDilation, MaxTimeDilation));

				Command->SetController(Controller);

				for (int Index = 0; Index < 5; Index++)
				{
					Command->SetTimeDilation(TimeDilations[Index]);

					Command->Execute();

					TEST_TRUE(Controller->IsPaused() == false)
					TEST_TRUE(Controller->CustomTimeDilation == (1.0f / TimeDilations[Index]))
					TEST_TRUE(WorldSettings->TimeDilation == TimeDilations[Index])
				}

				return true;
			});
		});
	}
}