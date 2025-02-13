// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/BBOpenWidgetCommand.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBHUDStub.h"
#include "Specifications/GUI/BBWidgetSpecificationStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBOpenWidgetCommandSpec, "SaltLakeCity.Commands.GUI.OpenWidgetCommand", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBHUDStub * HUD;

	UPROPERTY()
	TArray<UClass *> CommandClasses;

	// SUT
	UPROPERTY()
	UBBOpenWidgetCommand * Command = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBOpenWidgetCommandSpec)

void UBBOpenWidgetCommandSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBOpenWidgetCommand>(FString(TEXT("/Game/Commands/GUI")), CommandClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		HUD = TestWorld->SpawnActor<ABBHUDStub>(ABBHUDStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("HUD is valid", IsValid(HUD))

		return true;
	});

	AfterEach([this]()
	{
		Command = nullptr;

		TestWorld->DestroyActor(HUD);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & CommandClass : CommandClasses)
	{
		Describe("[" + CommandClass->GetName() + "]", [this, CommandClass]()
		{
			It("Given a new widget specification, expect the command to request its opening upon execution", [this, CommandClass]()
			{
				Command = NewObject<UBBOpenWidgetCommand>(TestWorld, CommandClass);

				UTEST_TRUE("Command is valid", IsValid(Command))

				TArray<UBBWidgetSpecificationStub *> WidgetSpecifications;
				WidgetSpecifications.Empty();
				WidgetSpecifications.Emplace(NewObject<UBBWidgetSpecificationStub>(TestWorld, UBBWidgetSpecificationStub::StaticClass()));
				WidgetSpecifications.Emplace(NewObject<UBBWidgetSpecificationStub>(TestWorld, UBBWidgetSpecificationStub::StaticClass()));
				WidgetSpecifications.Emplace(NewObject<UBBWidgetSpecificationStub>(TestWorld, UBBWidgetSpecificationStub::StaticClass()));
				WidgetSpecifications.Emplace(NewObject<UBBWidgetSpecificationStub>(TestWorld, UBBWidgetSpecificationStub::StaticClass()));
				WidgetSpecifications.Emplace(NewObject<UBBWidgetSpecificationStub>(TestWorld, UBBWidgetSpecificationStub::StaticClass()));

				TArray<bool> PopUps;
				PopUps.Empty();
				PopUps.Emplace(true);
				PopUps.Emplace(false);
				PopUps.Emplace(false);
				PopUps.Emplace(true);
				PopUps.Emplace(false);

				Command->SetHUD(HUD);

				for (int Index = 0; Index < 5; Index++)
				{
					Command->SetSpecification(WidgetSpecifications[Index]);
					Command->SetPopUp(PopUps[Index]);

					Command->Execute();

					TEST_TRUE(HUD->GetWidgetSpecification() == WidgetSpecifications[Index])
					TEST_TRUE(HUD->GetPopUp() == PopUps[Index])
				}

				return true;
			});
		});
	}
}