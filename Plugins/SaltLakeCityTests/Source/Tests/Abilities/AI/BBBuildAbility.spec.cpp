// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/Tasks/BBBuildTaskStub.h"
#include "Actors/BBActorStub.h"
#include "Actors/Buildings/BBBuildingStub.h"
#include "Actors/Components/BBAIAbilityComponentStub.h"
#include "Abilities/Ai/Interfaces/IBBBuildAbility.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Materials/BBMaterialInterfaceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBBuildAbilitySpec,
	"SaltLakeCity.Abilities.AI.BuildAbility",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBActorStub * Owner = nullptr;

	UPROPERTY()
	UBBAIAbilityComponentStub * AbilityComponentStub = nullptr;

	UPROPERTY()
	UBBBuildTaskStub * BuildTaskStub = nullptr;

	UPROPERTY()
	TArray<UClass *> AbilityClasses;

END_DEFINE_SPEC(UBBBuildAbilitySpec)

void UBBBuildAbilitySpec::Define()
{
	UBBTestUtil::GetTestClasses<UIBBBuildAbility>(FString(TEXT("/Game/Abilities/AI")), AbilityClasses);
	
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

		AbilityComponentStub = NewObject<UBBAIAbilityComponentStub>(Owner, UBBAIAbilityComponentStub::StaticClass());

		UTEST_TRUE("Ability Component Stub is valid", IsValid(AbilityComponentStub))

		Owner->AddOwnedComponent(AbilityComponentStub);
		AbilityComponentStub->RegisterComponent();
		AbilityComponentStub->InitAbilityActorInfo(Owner, Owner);

		BuildTaskStub = NewObject<UBBBuildTaskStub>(AbilityComponentStub, UBBBuildTaskStub::StaticClass());

		UTEST_TRUE("Build Task Stub is valid", IsValid(BuildTaskStub))

		return true;
	});

	AfterEach([this]()
	{
		BuildTaskStub = nullptr;

		AbilityComponentStub->DestroyComponent();
		AbilityComponentStub = nullptr;

		TestWorld->DestroyActor(Owner);

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (auto & AbilityClass : AbilityClasses)
	{
		Describe("[" + AbilityClass->GetName() + "]", [this, AbilityClass]()
		{
			It("Given a new ability request, expect the ability to run its behavior tree with the related task", [this, AbilityClass]()
			{
				TSubclassOf<UGameplayAbility> AbilitySubclass = TSubclassOf<UGameplayAbility>(AbilityClass);
				FGameplayAbilitySpec NewSpec = FGameplayAbilitySpec(AbilityClass);

				FGameplayAbilitySpecHandle Handle = AbilityComponentStub->GiveAbility(NewSpec);

				FGameplayEventData EventData = FGameplayEventData();
				EventData.OptionalObject = BuildTaskStub;

				TArray<TScriptInterface<IBBBuildable>> Buildables;
				Buildables.Emplace(TScriptInterface<IBBBuildable>(NewObject<AIBBBuilding>(TestWorld, ABBBuildingStub::StaticClass())));

				BuildTaskStub->SetEventTag(FGameplayTag::RequestGameplayTag(FName("Event.Build")));
				BuildTaskStub->SetEventData(EventData);
				BuildTaskStub->SetBuildables(Buildables);
				BuildTaskStub->SetProgress(5.0f);
				BuildTaskStub->SetPrice(10.0f);
				BuildTaskStub->SetTime(11.8f);

				FGameplayAbilitySpec * Spec = AbilityComponentStub->FindAbilitySpecFromHandle(Handle);

				UTEST_TRUE("Specification is not null", Spec != nullptr)

				TEST_TRUE(AbilityComponentStub->GetBehaviorTree() == nullptr)
				TEST_TRUE(AbilityComponentStub->GetTaskName().IsEqual(FName(), ENameCase::CaseSensitive))
				TEST_TRUE(AbilityComponentStub->GetTask() == nullptr)

				AbilityComponentStub->TriggerAbilityFromGameplayEvent(Spec->Handle, AbilityComponentStub->AbilityActorInfo.Get(), BuildTaskStub->GetEventTag(), BuildTaskStub->GetEventData(), * AbilityComponentStub);
					
				UIBBBuildAbility * BuildAbility = Spec->GetAbilityInstances().IsValidIndex(0) ?
						Cast<UIBBBuildAbility>(Spec->GetAbilityInstances()[0]) : nullptr;
					
				UTEST_TRUE("Build Ability is valid", IsValid(BuildAbility))

				TEST_TRUE(AbilityComponentStub->GetBehaviorTree() == BuildAbility->GetBehaviorTree())
				TEST_TRUE(AbilityComponentStub->GetTaskName() == BuildAbility->GetTaskName())
				TEST_TRUE(AbilityComponentStub->GetTask() == BuildAbility->GetTask())

				AbilityComponentStub->ClearAllAbilities();

				return true;
			});

			It("Given a completed task, expect the buildings to remove the preview material", [this, AbilityClass]()
			{
				TSubclassOf<UGameplayAbility> AbilitySubclass = TSubclassOf<UGameplayAbility>(AbilityClass);
				FGameplayAbilitySpec NewSpec = FGameplayAbilitySpec(AbilityClass);

				FGameplayAbilitySpecHandle Handle = AbilityComponentStub->GiveAbility(NewSpec);

				FGameplayEventData EventData = FGameplayEventData();
				EventData.OptionalObject = BuildTaskStub;

				TArray<TScriptInterface<IBBBuildable>> Buildables;

				for (int Index = 0; Index < 3; Index++)
				{
					ABBBuildingStub * BuildingStub = NewObject<ABBBuildingStub>(TestWorld, ABBBuildingStub::StaticClass());
					BuildingStub->AddMaterialOverride(NewObject<UBBMaterialInterfaceStub>(TestWorld, UBBMaterialInterfaceStub::StaticClass()));

					Buildables.Emplace(TScriptInterface<IBBBuildable>(BuildingStub));
				}

				BuildTaskStub->SetEventTag(FGameplayTag::RequestGameplayTag(FName("Event.Build")));
				BuildTaskStub->SetEventData(EventData);
				BuildTaskStub->SetBuildables(Buildables);
				BuildTaskStub->SetProgress(5.0f);
				BuildTaskStub->SetPrice(10.0f);
				BuildTaskStub->SetTime(11.8f);

				FGameplayAbilitySpec * Spec = AbilityComponentStub->FindAbilitySpecFromHandle(Handle);

				UTEST_TRUE("Specification is not null", Spec != nullptr)

				AbilityComponentStub->TriggerAbilityFromGameplayEvent(Spec->Handle, AbilityComponentStub->AbilityActorInfo.Get(), BuildTaskStub->GetEventTag(), BuildTaskStub->GetEventData(), *AbilityComponentStub);

				UIBBBuildAbility * BuildAbility = Spec->GetAbilityInstances().IsValidIndex(0) ?
					Cast<UIBBBuildAbility>(Spec->GetAbilityInstances()[0]) : nullptr;

				UTEST_TRUE("Build Ability is valid", IsValid(BuildAbility))

				BuildTaskStub->Complete();

				for (TScriptInterface<IBBBuildable> & Buildable : Buildables)
				{
					ABBBuildingStub * BuildingStub = Cast<ABBBuildingStub>(Buildable->ToActor());

					UTEST_TRUE("Building Stub is valid", IsValid(BuildingStub))

					TEST_TRUE(BuildingStub->GetMaterialOverride() == nullptr)
				}

				return true;
			});
		});
	}
}