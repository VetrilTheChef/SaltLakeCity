// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagsManager.h"
#include "Abilities/Data/BBAbilityDataStub.h"
#include "Abilities/Player/BBPlayerAbilityStub.h"
#include "Actors/Components/BBPlayerAbilityComponent.h"
#include "Controllers/BBPlayerControllerStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBPlayerAbilityComponentSpec,
	"SaltLakeCity.Actors.Components.PlayerAbilityComponent",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBPlayerControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<UClass *> ComponentClasses;

	// SUT
	UPROPERTY()
	UBBPlayerAbilityComponent * AbilityComponent = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBPlayerAbilityComponentSpec)

void UBBPlayerAbilityComponentSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBPlayerAbilityComponent>(FString(TEXT("/Game/Actors/Components")), ComponentClasses);

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
		AbilityComponent->DestroyComponent();

		TestWorld->DestroyActor(Controller);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ComponentClass : ComponentClasses)
	{
		Describe("[" + ComponentClass->GetName() + "]", [this, ComponentClass]()
		{
			It("Given a new ability, expect the player ability component to add it to its abilities", [this, ComponentClass]()
			{
				AbilityComponent = NewObject<UBBPlayerAbilityComponent>(Controller, ComponentClass);

				UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))

				Controller->AddOwnedComponent(AbilityComponent);
				AbilityComponent->RegisterComponent();

				AbilityComponent->ClearAbilities();

				for (int Index = 0; Index < 6; Index++)
				{
					FGameplayAbilitySpec NewSpec = FGameplayAbilitySpec(TSubclassOf<UGameplayAbility>(UBBPlayerAbilityStub::StaticClass()), 1, -1, AbilityComponent);
					FGameplayAbilitySpecHandle Handle = AbilityComponent->GiveAbility(NewSpec);
					FGameplayAbilitySpec * Spec = AbilityComponent->FindAbilitySpecFromHandle(Handle);

					TEST_TRUE(Spec != nullptr)
					TEST_TRUE(IsValid(Spec->Ability))
				}

				return true;
			});

			It("Given a new ability request, expect the player ability component to trigger the appropriate ability", [this, ComponentClass]()
			{
				UGameplayTagsManager & Manager = UGameplayTagsManager::Get();

				FGameplayTagContainer TagContainer;
				Manager.RequestAllGameplayTags(TagContainer, true);

				for (int Index = TagContainer.Num() - 1; Index >= 0; Index--)
				{
					FGameplayTag Tag = TagContainer.GetByIndex(Index);
					FString TagString = Tag.ToString();

					if (!TagString.StartsWith(FString("Ability.Player."), ESearchCase::CaseSensitive))
					{
						TagContainer.RemoveTag(Tag);
					}
				}

				AbilityComponent = NewObject<UBBPlayerAbilityComponent>(Controller, ComponentClass);

				UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))

				Controller->AddOwnedComponent(AbilityComponent);
				AbilityComponent->RegisterComponent();

				AbilityComponent->ClearAbilities();

				TArray<UBBAbilityDataStub *> AbilitiesData;
				UBBAbilityDataStub * Data = nullptr;

				TMap<FGameplayTag, FGameplayAbilitySpec *> AbilitySpecs;

				for (int Index = 0; Index < TagContainer.Num(); Index++)
				{
					FGameplayTag Tag = TagContainer.GetByIndex(Index);

					FGameplayAbilitySpec NewSpec = FGameplayAbilitySpec(TSubclassOf<UGameplayAbility>(UBBPlayerAbilityStub::StaticClass()), 1, -1, AbilityComponent);
					FGameplayAbilitySpecHandle Handle = AbilityComponent->GiveAbility(NewSpec);
					FGameplayAbilitySpec * Spec = AbilityComponent->FindAbilitySpecFromHandle(Handle);

					UTEST_TRUE("Ability specification is not null", Spec != nullptr)

					UBBPlayerAbilityStub * Ability = Cast<UBBPlayerAbilityStub>(Spec->Ability);

					UTEST_TRUE("Ability instance is valid", IsValid(Ability))

					Ability->AbilityTags.AddTag(Tag);

					Ability = Cast<UBBPlayerAbilityStub>(Spec->GetPrimaryInstance());

					UTEST_TRUE("Ability instance is valid", IsValid(Ability))

					Ability->AbilityTags.AddTag(Tag);

					AbilityComponent->MarkAbilitySpecDirty(* Spec);

					AbilitySpecs.Emplace(Tag, Spec);

					Data = NewObject<UBBAbilityDataStub>(TestWorld, UBBAbilityDataStub::StaticClass());

					UTEST_TRUE("Ability Data is valid", IsValid(Data))

					Data->SetEventTag(Tag);
					AbilitiesData.Emplace(Data);
				}

				for (UBBAbilityDataStub * & AbilityData : AbilitiesData)
				{
					FGameplayAbilitySpec * Spec = AbilitySpecs.FindChecked(AbilityData->GetEventTag());

					UTEST_TRUE("Ability Spec is not null", Spec != nullptr)

					UBBPlayerAbilityStub * Ability = Cast<UBBPlayerAbilityStub>(Spec->GetPrimaryInstance());

					UTEST_TRUE("Ability is valid", IsValid(Ability))

					int Activations = Ability->GetNumActivations();

					bool ActivationResult = AbilityComponent->RequestAbility(AbilityData);

					TEST_TRUE(ActivationResult == true)
					TEST_TRUE(Ability->GetNumActivations() == Activations + 1)
				}

				return true;
			});
		});
	}
}