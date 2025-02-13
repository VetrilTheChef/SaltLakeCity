// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/BBBuildDataStub.h"
#include "Commands/Controllers/BBOrderBuildCommand.h"
#include "Controllers/BBPlayerControllerStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBOrderBuildCommandSpec, "SaltLakeCity.Commands.Controllers.OrderBuildCommand", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBPlayerControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<UClass *> CommandClasses;

	// SUT
	UPROPERTY()
	UBBOrderBuildCommand * Command = nullptr;
	
	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBOrderBuildCommandSpec)

void UBBOrderBuildCommandSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBOrderBuildCommand>(FString(TEXT("/Game/Commands/Controllers")), CommandClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Controller = TestWorld->SpawnActor<ABBPlayerControllerStub>(ABBPlayerControllerStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		return true;
	});

	AfterEach([this]()
	{
		Command = nullptr;

		TestWorld->DestroyActor(Controller);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & CommandClass : CommandClasses)
	{
		Describe("[" + CommandClass->GetName() + "]", [this, CommandClass]()
		{
			It("Given a new build data class, a price and a time, expect the command to request the ability upon execution", [this, CommandClass]()
			{
				Command = NewObject<UBBOrderBuildCommand>(TestWorld, CommandClass);

				UTEST_TRUE("Command is valid", IsValid(Command))

				TArray<float> Prices;
				Prices.Empty();
				Prices.Emplace(-734.21f);
				Prices.Emplace(263.46f);
				Prices.Emplace(622.35f);
				Prices.Emplace(-347.21f);
				Prices.Emplace(-134.84f);

				TArray<float> Times;
				Times.Empty();
				Times.Emplace(125.17f);
				Times.Emplace(-561.12f);
				Times.Emplace(445.73f);
				Times.Emplace(-723.45f);
				Times.Emplace(852.02f);

				Command->SetController(Controller);
				Command->SetOuter(Controller);
				Command->SetBuildDataClass(TSoftClassPtr<UIBBBuildData>(UBBBuildDataStub::StaticClass()));

				for (int Index = 0; Index < 5; Index++)
				{
					Command->SetPrice(Prices[Index]);
					Command->SetTime(Times[Index]);

					Command->Execute();

					UBBBuildDataStub * RequestedBuildData = Cast<UBBBuildDataStub>(Controller->GetRequestedAbilityData());

					TEST_TRUE(IsValid(RequestedBuildData))

					if (IsValid(RequestedBuildData))
					{
						TEST_TRUE(RequestedBuildData->GetPrice() == Prices[Index])
						TEST_TRUE(RequestedBuildData->GetTime() == Times[Index])
					}
				}

				return true;
			});
		});
	}
}