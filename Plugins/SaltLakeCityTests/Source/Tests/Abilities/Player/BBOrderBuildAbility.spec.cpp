// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/Data/BBBuildDataStub.h"
#include "Actors/BBActorStub.h"
#include "Actors/Buildings/BBBuildingStub.h"
#include "Actors/Targeting/Interfaces/IBBTargetingActor.h"
#include "Actors/Targeting/BBTargetingActorStub.h"
#include "Actors/Components/BBPlayerAbilityComponentStub.h"
#include "Abilities/Player/Interfaces/IBBOrderBuildAbility.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBOrderBuildAbilitySpec, "SaltLakeCity.Abilities.Player.OrderBuildAbility", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBActorStub * Owner = nullptr;

	UPROPERTY()
	UBBPlayerAbilityComponentStub * AbilityComponentStub = nullptr;

	UPROPERTY()
	UBBBuildDataStub * BuildDataStub = nullptr;

	UPROPERTY()
	TArray<UClass *> AbilityClasses;

END_DEFINE_SPEC(UBBOrderBuildAbilitySpec)

void UBBOrderBuildAbilitySpec::Define()
{
	UBBTestUtil::GetTestClasses<UIBBOrderBuildAbility>(FString(TEXT("/Game/Abilities/Player")), AbilityClasses);
	
	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.bNoFail = true;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		Owner = TestWorld->SpawnActor<ABBActorStub>(SpawnParameters);

		UTEST_TRUE("Owner is valid", IsValid(Owner))

		AbilityComponentStub = NewObject<UBBPlayerAbilityComponentStub>(Owner, UBBPlayerAbilityComponentStub::StaticClass());
		
		UTEST_TRUE("Ability Component Stub is valid", IsValid(AbilityComponentStub))

		Owner->AddOwnedComponent(AbilityComponentStub);
		AbilityComponentStub->RegisterComponent();
		AbilityComponentStub->InitAbilityActorInfo(Owner, Owner);

		BuildDataStub = NewObject<UBBBuildDataStub>(AbilityComponentStub, UBBBuildDataStub::StaticClass());

		UTEST_TRUE("Build Data Stub is valid", IsValid(BuildDataStub))

		return true;
	});

	AfterEach([this]()
	{
		BuildDataStub = nullptr;

		AbilityComponentStub->DestroyComponent();
		AbilityComponentStub = nullptr;

		TestWorld->DestroyActor(Owner);

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (auto& AbilityClass : AbilityClasses)
	{
		Describe("[" + AbilityClass->GetName() + "]", [this, AbilityClass]()
		{
			It("Given a new building request, expect the ability to spawn a targeting actor", [this, AbilityClass]()
			{
				TSubclassOf<UGameplayAbility> AbilitySubclass = TSubclassOf<UGameplayAbility>(AbilityClass);
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);

				FGameplayAbilitySpecHandle Handle = AbilityComponentStub->GiveAbility(AbilitySpec);

				FGameplayAbilitySpec * Spec = AbilityComponentStub->FindAbilitySpecFromHandle(Handle);

				UTEST_TRUE("Specification is not null", Spec != nullptr)

				UIBBOrderBuildAbility * BuildAbility = Spec->GetAbilityInstances().IsValidIndex(0) ?
					Cast<UIBBOrderBuildAbility>(Spec->GetAbilityInstances()[0]) : nullptr;

				UTEST_TRUE("Build ability is valid", IsValid(BuildAbility))

				BuildDataStub->SetEventTag(FGameplayTag::RequestGameplayTag(FName("Ability.Player.Build")));

				FGameplayEventData EventData = FGameplayEventData();
				EventData.OptionalObject = BuildDataStub;
				BuildDataStub->SetEventData(EventData);
				BuildDataStub->SetTargetingClass(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				BuildDataStub->SetBuildableClasses(TArray<FBBBuildablePtr>());
				BuildDataStub->SetBuildables(TArray<TScriptInterface<IBBBuildable>>());

				TArray<float> Prices;
				Prices.Empty();
				Prices.Emplace(10.0f);
				Prices.Emplace(0.0f);
				Prices.Emplace(-3.0f);
				Prices.Emplace(-235.4f);
				Prices.Emplace(324.111f);

				TArray<float> Times;
				Times.Empty();
				Times.Emplace(50.0f);
				Times.Emplace(11.8f);
				Times.Emplace(-257.0f);
				Times.Emplace(0.4f);
				Times.Emplace(24.003f);

				for (int Index = 0; Index < 5; Index++)
				{
					BuildDataStub->SetPrice(Prices[Index]);
					BuildDataStub->SetTime(Times[Index]);

					int TargetActorsNum = AbilityComponentStub->SpawnedTargetActors.Num();

					AbilityComponentStub->TriggerAbilityFromGameplayEvent(AbilitySpec.Handle, AbilityComponentStub->AbilityActorInfo.Get(), BuildDataStub->GetEventTag(), BuildDataStub->GetEventData(), * AbilityComponentStub);

					TEST_TRUE(IsValid(BuildDataStub->GetTargetingActor()))

					AbilityComponentStub->TargetCancel();
				}

				AbilityComponentStub->ClearAllAbilities();
				
				return true;
			});

			It("Given a new canceled building request, expect the targeting actor to despawn", [this, AbilityClass]()
			{
				TSubclassOf<UGameplayAbility> AbilitySubclass = TSubclassOf<UGameplayAbility>(AbilityClass);
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);

				FGameplayAbilitySpecHandle Handle = AbilityComponentStub->GiveAbility(AbilitySpec);

				FGameplayAbilitySpec * Spec = AbilityComponentStub->FindAbilitySpecFromHandle(Handle);

				UTEST_TRUE("Specification is not null", Spec != nullptr)

				UIBBOrderBuildAbility * BuildAbility = Spec->GetAbilityInstances().IsValidIndex(0) ?
					Cast<UIBBOrderBuildAbility>(Spec->GetAbilityInstances()[0]) : nullptr;

				UTEST_TRUE("Build ability is valid", IsValid(BuildAbility))

				BuildDataStub->SetEventTag(FGameplayTag::RequestGameplayTag(FName("Ability.Player.Build")));

				FGameplayEventData EventData = FGameplayEventData();
				EventData.OptionalObject = BuildDataStub;
				BuildDataStub->SetEventData(EventData);
				BuildDataStub->SetTargetingClass(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				BuildDataStub->SetBuildableClasses(TArray<FBBBuildablePtr>());
				BuildDataStub->SetBuildables(TArray<TScriptInterface<IBBBuildable>>());

				TArray<float> Prices;
				Prices.Empty();
				Prices.Emplace(10.0f);
				Prices.Emplace(0.0f);
				Prices.Emplace(-3.0f);
				Prices.Emplace(-235.4f);
				Prices.Emplace(324.111f);

				TArray<float> Times;
				Times.Empty();
				Times.Emplace(50.0f);
				Times.Emplace(11.8f);
				Times.Emplace(-257.0f);
				Times.Emplace(0.4f);
				Times.Emplace(24.003f);

				for (int Index = 0; Index < 5; Index++)
				{
					BuildDataStub->SetPrice(Prices[Index]);
					BuildDataStub->SetTime(Times[Index]);

					int TargetActorsNum = AbilityComponentStub->SpawnedTargetActors.Num();

					AbilityComponentStub->TriggerAbilityFromGameplayEvent(AbilitySpec.Handle, AbilityComponentStub->AbilityActorInfo.Get(), BuildDataStub->GetEventTag(), BuildDataStub->GetEventData(), *AbilityComponentStub);

					TEST_TRUE(IsValid(BuildDataStub->GetTargetingActor()))

					AbilityComponentStub->TargetCancel();

					TEST_TRUE(!IsValid(BuildDataStub->GetTargetingActor()))
				}

				AbilityComponentStub->ClearAllAbilities();

				return true;
			});

			It("Given a new confirm building request, expect the targeting actor to despawn", [this, AbilityClass]()
			{
				TSubclassOf<UGameplayAbility> AbilitySubclass = TSubclassOf<UGameplayAbility>(AbilityClass);
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);

				FGameplayAbilitySpecHandle Handle = AbilityComponentStub->GiveAbility(AbilitySpec);

				FGameplayAbilitySpec * Spec = AbilityComponentStub->FindAbilitySpecFromHandle(Handle);

				UTEST_TRUE("Specification is not null", Spec != nullptr)

				UIBBOrderBuildAbility * BuildAbility = Spec->GetAbilityInstances().IsValidIndex(0) ?
					Cast<UIBBOrderBuildAbility>(Spec->GetAbilityInstances()[0]) : nullptr;

				UTEST_TRUE("Build ability is valid", IsValid(BuildAbility))

				BuildDataStub->SetEventTag(FGameplayTag::RequestGameplayTag(FName("Ability.Player.Build")));

				FGameplayEventData EventData = FGameplayEventData();
				EventData.OptionalObject = BuildDataStub;
				BuildDataStub->SetEventData(EventData);
				BuildDataStub->SetTargetingClass(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				BuildDataStub->SetBuildableClasses(TArray<FBBBuildablePtr>());
				BuildDataStub->SetBuildables(TArray<TScriptInterface<IBBBuildable>>());

				TArray<float> Prices;
				Prices.Empty();
				Prices.Emplace(10.0f);
				Prices.Emplace(0.0f);
				Prices.Emplace(-3.0f);
				Prices.Emplace(-235.4f);
				Prices.Emplace(324.111f);

				TArray<float> Times;
				Times.Empty();
				Times.Emplace(50.0f);
				Times.Emplace(11.8f);
				Times.Emplace(-257.0f);
				Times.Emplace(0.4f);
				Times.Emplace(24.003f);

				for (int Index = 0; Index < 5; Index++)
				{
					BuildDataStub->SetPrice(Prices[Index]);
					BuildDataStub->SetTime(Times[Index]);

					int TargetActorsNum = AbilityComponentStub->SpawnedTargetActors.Num();

					AbilityComponentStub->TriggerAbilityFromGameplayEvent(AbilitySpec.Handle, AbilityComponentStub->AbilityActorInfo.Get(), BuildDataStub->GetEventTag(), BuildDataStub->GetEventData(), *AbilityComponentStub);

					TEST_TRUE(IsValid(BuildDataStub->GetTargetingActor()))

					AbilityComponentStub->TargetConfirm();

					TEST_TRUE(!IsValid(BuildDataStub->GetTargetingActor()))
				}

				AbilityComponentStub->ClearAllAbilities();

				return true;
			});

			It("Given a spawned targeting actor, expect the ability to attach all the required buildings to it", [this, AbilityClass]()
			{
				TSubclassOf<UGameplayAbility> AbilitySubclass = TSubclassOf<UGameplayAbility>(AbilityClass);
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);

				FGameplayAbilitySpecHandle Handle = AbilityComponentStub->GiveAbility(AbilitySpec);

				FGameplayAbilitySpec * Spec = AbilityComponentStub->FindAbilitySpecFromHandle(Handle);

				UTEST_TRUE("Specification is not null", Spec != nullptr)

				UIBBOrderBuildAbility * BuildAbility = Spec->GetAbilityInstances().IsValidIndex(0) ?
					Cast<UIBBOrderBuildAbility>(Spec->GetAbilityInstances()[0]) : nullptr;

				UTEST_TRUE("Build ability is valid", IsValid(BuildAbility))

				BuildDataStub->SetEventTag(FGameplayTag::RequestGameplayTag(FName("Ability.Player.Build")));

				FGameplayEventData EventData = FGameplayEventData();
				EventData.OptionalObject = BuildDataStub;
				BuildDataStub->SetEventData(EventData);
				BuildDataStub->SetTargetingClass(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				BuildDataStub->SetPrice(15.0f);
				BuildDataStub->SetTime(256.1f);

				TArray<TArray<FBBBuildablePtr>> AllBuildableClasses;
				TArray<FBBBuildablePtr> BuildableClasses;

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
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);

				BuildableClasses.Empty();
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);

				for (int Index = 0; Index < 5; Index++)
				{
					BuildDataStub->SetBuildableClasses(AllBuildableClasses[Index]);
					BuildDataStub->SetBuildables(TArray<TScriptInterface<IBBBuildable>>());

					int TargetActorsNum = AbilityComponentStub->SpawnedTargetActors.Num();

					AbilityComponentStub->TriggerAbilityFromGameplayEvent(AbilitySpec.Handle, AbilityComponentStub->AbilityActorInfo.Get(), BuildDataStub->GetEventTag(), BuildDataStub->GetEventData(), *AbilityComponentStub);

					AIBBTargetingActor * TargetingActor = BuildDataStub->GetTargetingActor();

					UTEST_TRUE("Targeting actor is valid", IsValid(TargetingActor))

					TEST_TRUE(TargetingActor->GetAttachedActorsNum() == AllBuildableClasses[Index].Num())

					AbilityComponentStub->TargetCancel();
				}

				AbilityComponentStub->ClearAllAbilities();

				return true;
			});

			It("Given a spawned targeting actor, expect the ability to apply a preview material to all the required buildings", [this, AbilityClass]()
			{
				TSubclassOf<UGameplayAbility> AbilitySubclass = TSubclassOf<UGameplayAbility>(AbilityClass);
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);

				FGameplayAbilitySpecHandle Handle = AbilityComponentStub->GiveAbility(AbilitySpec);

				FGameplayAbilitySpec * Spec = AbilityComponentStub->FindAbilitySpecFromHandle(Handle);

				UTEST_TRUE("Specification is not null", Spec != nullptr)

				UIBBOrderBuildAbility * BuildAbility = Spec->GetAbilityInstances().IsValidIndex(0) ?
					Cast<UIBBOrderBuildAbility>(Spec->GetAbilityInstances()[0]) : nullptr;

				UTEST_TRUE("Build ability is valid", IsValid(BuildAbility))

				BuildDataStub->SetEventTag(FGameplayTag::RequestGameplayTag(FName("Ability.Player.Build")));

				FGameplayEventData EventData = FGameplayEventData();
				EventData.OptionalObject = BuildDataStub;
				BuildDataStub->SetEventData(EventData);
				BuildDataStub->SetTargetingClass(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				BuildDataStub->SetPrice(15.0f);
				BuildDataStub->SetTime(256.1f);

				TArray<TArray<FBBBuildablePtr>> AllBuildableClasses;
				TArray<FBBBuildablePtr> BuildableClasses;

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
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);

				BuildableClasses.Empty();
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);

				for (int Index = 0; Index < 5; Index++)
				{
					BuildDataStub->SetBuildableClasses(AllBuildableClasses[Index]);
					BuildDataStub->SetBuildables(TArray<TScriptInterface<IBBBuildable>>());

					AbilityComponentStub->TriggerAbilityFromGameplayEvent(AbilitySpec.Handle, AbilityComponentStub->AbilityActorInfo.Get(), BuildDataStub->GetEventTag(), BuildDataStub->GetEventData(), *AbilityComponentStub);
					
					TEST_TRUE(BuildDataStub->GetNumBuildables() == AllBuildableClasses[Index].Num())

					AIBBTargetingActor * TargetingActor = BuildDataStub->GetTargetingActor();

					UTEST_TRUE("Targeting actor is valid", IsValid(TargetingActor))

					TArray<AActor *> AttachedActors;
								
					TargetingActor->GetAttachedActors(AttachedActors, false);

					for (auto& AttachedActor : AttachedActors)
					{
						ABBBuildingStub * BuildingStub = Cast<ABBBuildingStub>(AttachedActor);

						UTEST_TRUE("Building Stub is valid", IsValid(BuildingStub))

						TEST_TRUE(BuildingStub->GetMaterialOverride() == TargetingActor->GetPreviewMaterial())
					}

					AbilityComponentStub->TargetCancel();
				}

				AbilityComponentStub->ClearAllAbilities();

				return true;
			});

			It("Given a canceled targeting request, expect the buildings to despawn", [this, AbilityClass]()
			{
				TSubclassOf<UGameplayAbility> AbilitySubclass = TSubclassOf<UGameplayAbility>(AbilityClass);
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);

				FGameplayAbilitySpecHandle Handle = AbilityComponentStub->GiveAbility(AbilitySpec);

				FGameplayAbilitySpec * Spec = AbilityComponentStub->FindAbilitySpecFromHandle(Handle);

				UTEST_TRUE("Specification is not null", Spec != nullptr)

				UIBBOrderBuildAbility * BuildAbility = Spec->GetAbilityInstances().IsValidIndex(0) ?
					Cast<UIBBOrderBuildAbility>(Spec->GetAbilityInstances()[0]) : nullptr;

				UTEST_TRUE("Build ability is valid", IsValid(BuildAbility))

				BuildDataStub->SetEventTag(FGameplayTag::RequestGameplayTag(FName("Ability.Player.Build")));

				FGameplayEventData EventData = FGameplayEventData();
				EventData.OptionalObject = BuildDataStub;
				BuildDataStub->SetEventData(EventData);
				BuildDataStub->SetTargetingClass(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				BuildDataStub->SetPrice(15.0f);
				BuildDataStub->SetTime(256.1f);

				TArray<TArray<FBBBuildablePtr>> AllBuildableClasses;
				TArray<FBBBuildablePtr> BuildableClasses;

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
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);

				BuildableClasses.Empty();
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);

				BuildableClasses.Empty();
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);

				for (int Index = 0; Index < 5; Index++)
				{
					BuildDataStub->SetBuildableClasses(AllBuildableClasses[Index]);
					BuildDataStub->SetBuildables(TArray<TScriptInterface<IBBBuildable>>());

					int TargetActorsNum = AbilityComponentStub->SpawnedTargetActors.Num();

					AbilityComponentStub->TriggerAbilityFromGameplayEvent(AbilitySpec.Handle, AbilityComponentStub->AbilityActorInfo.Get(), BuildDataStub->GetEventTag(), BuildDataStub->GetEventData(), *AbilityComponentStub);
					
					TEST_TRUE(BuildDataStub->GetNumBuildables() == AllBuildableClasses[Index].Num());

					AbilityComponentStub->TargetCancel();
					
					TEST_TRUE(BuildDataStub->GetNumBuildables() == 0);
				}

				AbilityComponentStub->ClearAllAbilities();

				return true;
			});

			It("Given a confirmed targeting request, expect the buildings not to despawn", [this, AbilityClass]()
			{
				TSubclassOf<UGameplayAbility> AbilitySubclass = TSubclassOf<UGameplayAbility>(AbilityClass);
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);

				FGameplayAbilitySpecHandle Handle = AbilityComponentStub->GiveAbility(AbilitySpec);

				FGameplayAbilitySpec * Spec = AbilityComponentStub->FindAbilitySpecFromHandle(Handle);

				UTEST_TRUE("Specification is not null", Spec != nullptr)

				UIBBOrderBuildAbility * BuildAbility = Spec->GetAbilityInstances().IsValidIndex(0) ?
					Cast<UIBBOrderBuildAbility>(Spec->GetAbilityInstances()[0]) : nullptr;

				UTEST_TRUE("Build ability is valid", IsValid(BuildAbility))

				BuildDataStub->SetEventTag(FGameplayTag::RequestGameplayTag(FName("Ability.Player.Build")));

				FGameplayEventData EventData = FGameplayEventData();
				EventData.OptionalObject = BuildDataStub;
				BuildDataStub->SetEventData(EventData);
				BuildDataStub->SetTargetingClass(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				BuildDataStub->SetPrice(15.0f);
				BuildDataStub->SetTime(256.1f);

				TArray<TArray<FBBBuildablePtr>> AllBuildableClasses;
				TArray<FBBBuildablePtr> BuildableClasses;

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

				for (int Index = 0; Index < 5; Index++)
				{
					BuildDataStub->SetBuildableClasses(AllBuildableClasses[Index]);
					BuildDataStub->SetBuildables(TArray<TScriptInterface<IBBBuildable>>());

					AbilityComponentStub->TriggerAbilityFromGameplayEvent(AbilitySpec.Handle, AbilityComponentStub->AbilityActorInfo.Get(), BuildDataStub->GetEventTag(), BuildDataStub->GetEventData(), * AbilityComponentStub);

					TEST_TRUE(BuildDataStub->GetNumBuildables() == AllBuildableClasses[Index].Num());

					AbilityComponentStub->TargetConfirm();

					TEST_TRUE(BuildDataStub->GetNumBuildables() == AllBuildableClasses[Index].Num());

					for (int BuildableIndex = BuildDataStub->GetNumBuildables() - 1; BuildableIndex >= 0; BuildableIndex--)
					{
						TScriptInterface<IBBBuildable> Buildable = BuildDataStub->GetBuildable(BuildableIndex);

						BuildDataStub->RemoveBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));

						TestWorld->DestroyActor(Buildable->ToActor());
					}
				}

				AbilityComponentStub->ClearAllAbilities();
				
				return true;
			});

			It("Given a confirmed targeting request, expect the buildings not to remove the preview material", [this, AbilityClass]()
			{
				TSubclassOf<UGameplayAbility> AbilitySubclass = TSubclassOf<UGameplayAbility>(AbilityClass);
				FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);

				FGameplayAbilitySpecHandle AbilityHandle = AbilityComponentStub->GiveAbility(AbilitySpec);

				FGameplayAbilitySpec * Spec = AbilityComponentStub->FindAbilitySpecFromHandle(AbilityHandle);

				UTEST_TRUE("Spec is not null", Spec != nullptr)

				BuildDataStub->SetEventTag(FGameplayTag::RequestGameplayTag(FName("Ability.Player.Build")));

				FGameplayEventData EventData = FGameplayEventData();
				EventData.OptionalObject = BuildDataStub;
				BuildDataStub->SetEventData(EventData);
				BuildDataStub->SetTargetingClass(TSoftClassPtr<AIBBTargetingActor>(ABBTargetingActorStub::StaticClass()));
				BuildDataStub->SetPrice(15.0f);
				BuildDataStub->SetTime(256.1f);

				TArray<TArray<FBBBuildablePtr>> AllBuildableClasses;
				TArray<FBBBuildablePtr> BuildableClasses;

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
				AllBuildableClasses.Emplace(BuildableClasses);

				BuildableClasses.Empty();
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);

				BuildableClasses.Empty();
				BuildableClasses.Emplace(FBBBuildablePtr(ABBBuildingStub::StaticClass()));
				AllBuildableClasses.Emplace(BuildableClasses);

				for (int Index = 0; Index < 5; Index++)
				{
					BuildDataStub->SetBuildableClasses(AllBuildableClasses[Index]);
					BuildDataStub->SetBuildables(TArray<TScriptInterface<IBBBuildable>>());

					AbilityComponentStub->TriggerAbilityFromGameplayEvent(AbilitySpec.Handle, AbilityComponentStub->AbilityActorInfo.Get(), BuildDataStub->GetEventTag(), BuildDataStub->GetEventData(), *AbilityComponentStub);

					TEST_TRUE(BuildDataStub->GetNumBuildables() == AllBuildableClasses[Index].Num())

					UGameplayAbility * Ability = Spec->GetPrimaryInstance();

					UTEST_TRUE("Ability is valid", IsValid(Ability))

					AIBBTargetingActor * TargetingActor = BuildDataStub->GetTargetingActor();

					UTEST_TRUE("Targeting Actor is valid", IsValid(TargetingActor))

					UMaterialInterface * MaterialOverride = TargetingActor->GetPreviewMaterial();

					UTEST_TRUE("Material Override is valid", IsValid(MaterialOverride))

					TEST_TRUE(BuildDataStub->GetNumBuildables() == AllBuildableClasses[Index].Num())

					for (int BuildableIndex = 0; BuildableIndex < BuildDataStub->GetNumBuildables(); BuildableIndex++)
					{
						ABBBuildingStub * BuildingStub = Cast<ABBBuildingStub>(BuildDataStub->GetBuildable(BuildableIndex).GetObject());

						UTEST_TRUE("Building stub is valid", IsValid(BuildingStub))

							TEST_TRUE(BuildingStub->GetMaterialOverride() == MaterialOverride)
					}

					AbilityComponentStub->TargetConfirm();

					TEST_TRUE(BuildDataStub->GetNumBuildables() == AllBuildableClasses[Index].Num())

					for (int BuildableIndex = BuildDataStub->GetNumBuildables() - 1; BuildableIndex >= 0; BuildableIndex--)
					{
						TScriptInterface<IBBBuildable> Buildable = BuildDataStub->GetBuildable(BuildableIndex);

						ABBBuildingStub * BuildingStub = Cast<ABBBuildingStub>(Buildable.GetObject());

						UTEST_TRUE("Building stub is valid", IsValid(BuildingStub))

						TEST_TRUE(BuildingStub->GetMaterialOverride() == MaterialOverride)

						BuildDataStub->RemoveBuildable(Forward<TScriptInterface<IBBBuildable>>(Buildable));

						TestWorld->DestroyActor(BuildingStub);
					}
				}

				AbilityComponentStub->ClearAllAbilities();

				return true;
			});
		});
	}
}