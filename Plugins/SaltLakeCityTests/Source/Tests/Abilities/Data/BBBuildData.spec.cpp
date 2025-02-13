// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/BBBuildData.h"
#include "Actors/Buildings/BBBuildingStub.h"
#include "Actors/Targeting/BBTargetingActorStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBBuildDataSpec, "SaltLakeCity.Abilities.Data.BuildData", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> DataClasses;

	// SUT
	UPROPERTY()
	UBBBuildData * BuildData = nullptr;

END_DEFINE_SPEC(UBBBuildDataSpec)

void UBBBuildDataSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBBuildData>(FString(TEXT("/Game/Abilities/Data")), DataClasses);

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
		BuildData = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (auto& DataClass : DataClasses)
	{
		Describe("[" + DataClass->GetName() + "]", [this, DataClass]()
		{
			It("Given a new job type request, expect the build data to return its job type", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				TEST_TRUE(BuildData->GetJobType() == EBBJob::Builder)

				return true;
			});

			It("Given a new event tag request, expect the build data to return its event tag", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				TEST_TRUE(BuildData->GetEventTag() == FGameplayTag::RequestGameplayTag(FName("Ability.Player.Build")))

				return true;
			});

			It("Given a new event data request, expect the build data to return its event data", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))
				UTEST_TRUE("Event data is valid", BuildData->GetEventData() != nullptr)

				TEST_TRUE(BuildData->GetEventData()->EventTag == BuildData->GetEventTag())

				return true;
			});

			It("Given a new ability tags request, expect the build data to return its ability tags", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				FGameplayTagContainer AbilityTags;
				AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Job.Builder")));

				TEST_TRUE(BuildData->GetAbilityTags() == AbilityTags)

				return true;
			});

			It("Given a new price, expect the build data to set its price", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				BuildData->SetPrice(0.0f);

				TEST_TRUE(BuildData->GetPrice() == 0.0f)

				TArray<float> Prices;
				Prices.Emplace(100.45f);
				Prices.Emplace(-25.73f);
				Prices.Emplace(631.05f);
				Prices.Emplace(-65.87f);
				Prices.Emplace(0.01f);

				for (auto & Price : Prices)
				{
					BuildData->SetPrice(Price);

					TEST_TRUE(BuildData->GetPrice() == Price)
				}

				return true;
			});

			It("Given a new time, expect the build data to set its time", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				BuildData->SetTime(0.0f);

				TEST_TRUE(BuildData->GetTime() == 0.0f)

				TArray<float> Times;
				Times.Emplace(932.46f);
				Times.Emplace(-75.61f);
				Times.Emplace(97.56f);
				Times.Emplace(25.67f);
				Times.Emplace(-672.18f);

				for (auto & Time : Times)
				{
					BuildData->SetTime(Time);

					TEST_TRUE(BuildData->GetTime() == Time)
				}

				return true;
			});

			It("Given a new targeting class, expect the build data to set its targeting class", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				BuildData->SetTargetingClass(TSoftClassPtr<AIBBTargetingActor>());

				TEST_TRUE(BuildData->GetTargetingClass().LoadSynchronous() == nullptr)

				TArray<TSoftClassPtr<AIBBTargetingActor>> TargetingClasses;
				TargetingClasses.Emplace(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				TargetingClasses.Emplace(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				TargetingClasses.Emplace(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				TargetingClasses.Emplace(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				TargetingClasses.Emplace(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));

				for (auto & TargetingClass : TargetingClasses)
				{
					BuildData->SetTargetingClass(TargetingClass);

					TEST_TRUE(BuildData->GetTargetingClass() == TargetingClass)
				}

				return true;
			});

			It("Given a new targeting actor, expect the build data to set its targeting actor", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				TEST_TRUE(BuildData->GetTargetingActor() == nullptr)

				FActorSpawnParameters SpawnParameters;
				SpawnParameters.bNoFail = true;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				TArray<ABBTargetingActorStub *> TargetingActors;
				TargetingActors.Emplace(TestWorld->SpawnActor<ABBTargetingActorStub>(ABBTargetingActorStub::StaticClass(), SpawnParameters));
				TargetingActors.Emplace(TestWorld->SpawnActor<ABBTargetingActorStub>(ABBTargetingActorStub::StaticClass(), SpawnParameters));
				TargetingActors.Emplace(TestWorld->SpawnActor<ABBTargetingActorStub>(ABBTargetingActorStub::StaticClass(), SpawnParameters));
				TargetingActors.Emplace(TestWorld->SpawnActor<ABBTargetingActorStub>(ABBTargetingActorStub::StaticClass(), SpawnParameters));
				TargetingActors.Emplace(TestWorld->SpawnActor<ABBTargetingActorStub>(ABBTargetingActorStub::StaticClass(), SpawnParameters));

				for (auto & TargetingActor : TargetingActors)
				{
					UTEST_TRUE("Targeting Actor is valid", IsValid(TargetingActor))

					BuildData->SetTargetingActor(TargetingActor);

					TEST_TRUE(BuildData->GetTargetingActor() == TargetingActor)
				}

				for (auto & TargetingActor : TargetingActors)
				{
					TestWorld->DestroyActor(TargetingActor);
				}

				return true;
			});

			It("Given new buildable classes, expect the build data to set its buildable classes", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				TEST_TRUE(BuildData->GetBuildableClasses() == TArray<FBBBuildablePtr>())
					
				TArray<TArray<FBBBuildablePtr>> AllBuildableClasses;
				TArray<FBBBuildablePtr> BuildableClasses;

				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);
				BuildableClasses.Empty();

				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);
				BuildableClasses.Empty();

				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);
				BuildableClasses.Empty();

				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);
				BuildableClasses.Empty();

				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);
				BuildableClasses.Empty();

				for (auto & Classes : AllBuildableClasses)
				{
					BuildData->SetBuildableClasses(Classes);

					TEST_TRUE(BuildData->GetBuildableClasses() == Classes)
				}

				return true;
			});

			It("Given new buildables to add, expect the build data to add them to its buildables in order", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				TEST_TRUE(BuildData->GetNumBuildables() == 0)

				FActorSpawnParameters SpawnParameters;
				SpawnParameters.bNoFail = true;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				TArray<TArray<ABBBuildingStub *>> AllBuildables;
				TArray<ABBBuildingStub *> Builds;

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				for (auto & Buildables : AllBuildables)
				{
					for (int Index = 0; Index < Buildables.Num(); Index++)
					{
						TScriptInterface<IBBBuildable> Buildable = TScriptInterface<IBBBuildable>(Buildables[Index]);
						BuildData->AddBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));
					}

					TEST_TRUE(BuildData->GetNumBuildables() == Buildables.Num())

					for (int Index = Buildables.Num() - 1; Index >= 0; Index--)
					{
						TEST_TRUE(BuildData->GetBuildable(Index) == Buildables[Index])

						TScriptInterface<IBBBuildable> Buildable = TScriptInterface<IBBBuildable>(Buildables[Index]);
						BuildData->RemoveBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));
					}

					TEST_TRUE(BuildData->GetNumBuildables() == 0)
				}

				for (auto & Buildables : AllBuildables)
				{
					for (auto & Buildable : Buildables)
					{
						TestWorld->DestroyActor(Buildable);
					}
				}

				return true;
			});

			It("Given new buildables to remove, expect the build data to remove them from its buildables", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				TEST_TRUE(BuildData->GetNumBuildables() == 0)

				FActorSpawnParameters SpawnParameters;
				SpawnParameters.bNoFail = true;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				TArray<TArray<ABBBuildingStub *>> AllBuildables;
				TArray<ABBBuildingStub *> Builds;

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				for (auto & Buildables : AllBuildables)
				{
					for (int Index = 0; Index < Buildables.Num(); Index++)
					{
						TScriptInterface<IBBBuildable> Buildable = TScriptInterface<IBBBuildable>(Buildables[Index]);
						BuildData->AddBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));
					}

					TEST_TRUE(BuildData->GetNumBuildables() == Buildables.Num())

					for (int Index = Buildables.Num() - 1; Index >= 0; Index--)
					{
						TScriptInterface<IBBBuildable> Buildable = TScriptInterface<IBBBuildable>(Buildables[Index]);
						BuildData->RemoveBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));

						int NumBuildables = BuildData->GetNumBuildables();

						TEST_TRUE(NumBuildables == Index)

						for (int IndexBuildable = 0; IndexBuildable < NumBuildables; IndexBuildable++)
						{
							TEST_TRUE(BuildData->GetBuildable(IndexBuildable) != Buildable)
						}
					}
				}

				for (auto & Buildables : AllBuildables)
				{
					for (auto & Buildable : Buildables)
					{
						TestWorld->DestroyActor(Buildable);
					}
				}

				return true;
			});

			It("Given new buildables, expect the build data to modify the number of its buildables", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				FActorSpawnParameters SpawnParameters;
				SpawnParameters.bNoFail = true;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				TArray<TArray<ABBBuildingStub *>> AllBuildables;
				TArray<ABBBuildingStub *> Builds;

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				for (auto & Buildables : AllBuildables)
				{
					TEST_TRUE(BuildData->GetNumBuildables() == 0)

					for (int Index = 0; Index < Buildables.Num(); Index++)
					{
						TScriptInterface<IBBBuildable> Buildable = TScriptInterface<IBBBuildable>(Buildables[Index]);
						BuildData->AddBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));

						TEST_TRUE(BuildData->GetNumBuildables() == Index + 1)
					}

					for (int Index = Buildables.Num() - 1; Index >= 0; Index--)
					{
						TScriptInterface<IBBBuildable> Buildable = TScriptInterface<IBBBuildable>(Buildables[Index]);
						BuildData->RemoveBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));

						TEST_TRUE(BuildData->GetNumBuildables() == Index)
					}
				}

				for (auto & Buildables : AllBuildables)
				{
					for (auto & Buildable : Buildables)
					{
						TestWorld->DestroyActor(Buildable);
					}
				}

				return true;
			});

			It("Given new added buildables, expect the build data to return them in order", [this, DataClass]()
			{
				BuildData = NewObject<UBBBuildData>(TestWorld, DataClass);

				UTEST_TRUE("Build data is valid", IsValid(BuildData))

				FActorSpawnParameters SpawnParameters;
				SpawnParameters.bNoFail = true;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				TArray<TArray<ABBBuildingStub *>> AllBuildables;
				TArray<ABBBuildingStub *> Builds;

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				Builds.Emplace(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters));
				AllBuildables.Emplace(Builds);
				Builds.Empty();

				for (auto & Buildables : AllBuildables)
				{
					for (int Index = 0; Index < Buildables.Num(); Index++)
					{
						TScriptInterface<IBBBuildable> Buildable = TScriptInterface<IBBBuildable>(Buildables[Index]);
						BuildData->AddBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));

						TEST_TRUE(BuildData->GetBuildable(Index).GetObject() == Buildables[Index])
					}

					for (int Index = Buildables.Num() - 1; Index >= 0; Index--)
					{
						TScriptInterface<IBBBuildable> Buildable = TScriptInterface<IBBBuildable>(Buildables[Index]);
						BuildData->RemoveBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));
					}
				}

				for (auto & Buildables : AllBuildables)
				{
					for (auto & Buildable : Buildables)
					{
						TestWorld->DestroyActor(Buildable);
					}
				}

				return true;
			});
		});
	}
}