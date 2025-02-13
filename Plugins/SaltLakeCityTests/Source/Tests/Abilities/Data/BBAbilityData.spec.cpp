// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/BBAbilityData.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBAbilityDataSpec, "SaltLakeCity.Abilities.Data.AbilityData", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> DataClasses;

	// SUT
	UPROPERTY()
	UBBAbilityData * AbilityData = nullptr;

END_DEFINE_SPEC(UBBAbilityDataSpec)

void UBBAbilityDataSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBAbilityData>(FString(TEXT("/Game/Abilities/Data")), DataClasses);
	
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
		AbilityData = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & DataClass : DataClasses)
	{
		Describe("[" + DataClass->GetName() + "]", [this, DataClass]()
		{
			It("Given a , expect the ability data to ", [this, DataClass]()
			{
			});
		});
	}
}