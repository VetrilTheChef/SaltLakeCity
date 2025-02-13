// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Buildings/BBBuildingStub.h"
#include "Actors/Targeting/BBTargetingActor.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBTargetingActorSpec, "SaltLakeCity.Actors.Targeting.TargetingActor", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> TargetingActorClasses;

	// SUT
	UPROPERTY()
	ABBTargetingActor * TargetActor = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBTargetingActorSpec)

void UBBTargetingActorSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBTargetingActor>(FString(TEXT("/Game/Actors/Targeting")), TargetingActorClasses);

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
		TestWorld->DestroyActor(TargetActor);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & TargetingActorClass : TargetingActorClasses)
	{
		Describe("[" + TargetingActorClass->GetName() + "]", [this, TargetingActorClass]()
		{
			It("Given a new attach request, expect the targeting actor to attach the given actor", [this, TargetingActorClass]()
			{
				TargetActor = TestWorld->SpawnActor<ABBTargetingActor>(TargetingActorClass, SpawnParameters);

				UTEST_TRUE("Target Actor is valid.", IsValid(TargetActor))

				TArray<ABBBuildingStub *> Buildings;
				Buildings.Empty();

				Buildings.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Buildings.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Buildings.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Buildings.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Buildings.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));

				TEST_TRUE(TargetActor->GetAttachedActorsNum() == 0);

				for (int Index = 0; Index < Buildings.Num(); Index++)
				{
					TargetActor->AttachActor(Buildings[Index]);

					TEST_TRUE(TargetActor->GetAttachedActorsNum() == Index + 1);
				}

				TargetActor->DetachAllActors();

				for (ABBBuildingStub * & Building : Buildings)
				{
					TestWorld->DestroyActor(Building);
				}

				return true;
			});

			It("Given a new detach request, expect the targeting actor to detach all actors", [this, TargetingActorClass]()
			{
				TargetActor = TestWorld->SpawnActor<ABBTargetingActor>(TargetingActorClass, SpawnParameters);

				UTEST_TRUE("Target Actor is valid.", IsValid(TargetActor))

				TArray<ABBBuildingStub *> Buildings;
				Buildings.Empty();

				Buildings.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Buildings.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Buildings.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Buildings.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Buildings.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));

				for (int Index = 0; Index < Buildings.Num(); Index++)
				{
					TargetActor->AttachActor(Buildings[Index]);
				}

				TEST_TRUE(TargetActor->GetAttachedActorsNum() == Buildings.Num());

				TargetActor->DetachAllActors();

				TEST_TRUE(TargetActor->GetAttachedActorsNum() == 0);

				for (ABBBuildingStub * & Building : Buildings)
				{
					TestWorld->DestroyActor(Building);
				}

				return true;
			});

			It("Given a new preview material request, expect the targeting actor to return its preview material", [this, TargetingActorClass]()
			{
				TargetActor = TestWorld->SpawnActor<ABBTargetingActor>(TargetingActorClass, SpawnParameters);

				UTEST_TRUE("Target Actor is valid.", IsValid(TargetActor))

				TargetActor->StartTargeting(nullptr);

				TEST_TRUE(IsValid(TargetActor->GetPreviewMaterial()))

				return true;
			});
		});
	}
}