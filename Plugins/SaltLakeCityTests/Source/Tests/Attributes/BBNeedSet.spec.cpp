// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "Actors/Components/BBAIAbilityComponentStub.h"
#include "Attributes/BBNeedSet.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Data/BBDossierEntryStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBSkillAttributeSetSpec,
	"SaltLakeCity.Attributes.NeedSet",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBCharacterStub * Character = nullptr;

	UPROPERTY()
	UBBAIAbilityComponentStub * AbilityComponent = nullptr;

	UPROPERTY()
	TArray<UClass *> SetClasses;

	// SUT
	UPROPERTY()
	UBBNeedSet * Set = nullptr;

	FActorSpawnParameters SpawnParameters;

	void TestNeed(EBBNeed Need, UBBNeedSet * NeedSet, const TArray<float> & NeedValues)
	{
		for (const float & NeedValue : NeedValues)
		{
			NeedSet->SetValue(Need, NeedValue);

			TEST_TRUE(NeedSet->GetValue(Need) == NeedValue)
		}
	}

	void TestMaxNeed(EBBNeed Need, UBBNeedSet * NeedSet, const TArray<float> & NeedValues)
	{
		for (const float & NeedValue : NeedValues)
		{
			NeedSet->SetMaxValue(Need, NeedValue);

			TEST_TRUE(NeedSet->GetMaxValue(Need) == NeedValue)
		}
	}

	void TestUpdate(EBBNeed Need, UBBNeedSet * NeedSet, TMap<EBBNeed, UBBDossierEntryStub *> Entries, const TArray<float> & NeedValues)
	{
		for (const float & NeedValue : NeedValues)
		{
			NeedSet->SetValue(Need, NeedValue);

			TEST_TRUE(Entries.FindChecked(Need)->GetValue() == NeedValue)
		}
	}

	void TestMaxUpdate(EBBNeed Need, UBBNeedSet * NeedSet, TMap<EBBNeed, UBBDossierEntryStub *> Entries, const TArray<float> & NeedValues)
	{
		for (const float & NeedValue : NeedValues)
		{
			NeedSet->SetMaxValue(Need, NeedValue);

			TEST_TRUE(Entries.FindChecked(Need)->GetMaxValue() == NeedValue)
		}
	}

END_DEFINE_SPEC(UBBSkillAttributeSetSpec)

void UBBSkillAttributeSetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBNeedSet>(FString(TEXT("/Game/Attributes")), SetClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Character = TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Character is valid", IsValid(Character))

		AbilityComponent = NewObject<UBBAIAbilityComponentStub>(Character, UBBAIAbilityComponentStub::StaticClass());

		UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))

		Character->SetAbilitySystemComponent(AbilityComponent);

		return true;
	});

	AfterEach([this]()
	{
		Set = nullptr;

		AbilityComponent = nullptr;

		TestWorld->DestroyActor(Character);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & SetClass : SetClasses)
	{
		Describe("[" + SetClass->GetName() + "]", [this, SetClass]()
		{
			It("Given a new need value, expect the need set to return the new value", [this, SetClass]()
			{
				Set = NewObject<UBBNeedSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TArray<float> SkillValues;
				SkillValues.Emplace(71.75f);
				SkillValues.Emplace(2438.56f);
				SkillValues.Emplace(-63.25f);
				SkillValues.Emplace(-952.05f);
				SkillValues.Emplace(0.0f);
				
				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetValue(EBBNeed::Hunger) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBNeed::Sleep) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBNeed::Thirst) == -1.0f)

				#define EBBNEED_OPERATION(Value) TestNeed(Value, Set, SkillValues);

					FOREACH_ENUM_EBBNEED(EBBNEED_OPERATION)

				#undef EBBNEED_OPERATION

				return true;
			});

			It("Given a new need max value, expect the need set to return the new value", [this, SetClass]()
			{
				Set = NewObject<UBBNeedSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TArray<float> SkillValues;
				SkillValues.Emplace(-222.34f);
				SkillValues.Emplace(0.0f);
				SkillValues.Emplace(-1612.51f);
				SkillValues.Emplace(275.82f);
				SkillValues.Emplace(734.47f);

				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetMaxValue(EBBNeed::Hunger) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBNeed::Sleep) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBNeed::Thirst) == -1.0f)

				#define EBBNEED_OPERATION(Value) TestMaxNeed(Value, Set, SkillValues);

					FOREACH_ENUM_EBBNEED(EBBNEED_OPERATION)

				#undef EBBNEED_OPERATION

				return true;
			});

			It("Given a need, expect the need set to return the need's values", [this, SetClass]()
			{
				struct FBBNeedTestCase
				{
					public:
						FBBNeedTestCase() :
							Need(EBBNeed::Hunger),
							Value(0.0f),
							MaxValue(0.0f)
						{};

						FBBNeedTestCase(EBBNeed NewNeed, float NewValue, float NewMaxValue) :
							Need(NewNeed),
							Value(NewValue),
							MaxValue(NewMaxValue)
						{};

						EBBNeed Need;

						float Value;

						float MaxValue;
				};

				Set = NewObject<UBBNeedSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TArray<FBBNeedTestCase> NeedTestCases;
				NeedTestCases.Empty();

				NeedTestCases.Emplace(FBBNeedTestCase(EBBNeed::Hunger, -412.61f, 25.76f));
				NeedTestCases.Emplace(FBBNeedTestCase(EBBNeed::Sleep, -614.32f, 123.12f));
				NeedTestCases.Emplace(FBBNeedTestCase(EBBNeed::Thirst, 37.12f, -845.75f));

				AbilityComponent->AddAttributeSet(Set);

				for (FBBNeedTestCase & NeedTestCase : NeedTestCases)
				{
					TEST_TRUE(Set->GetValue(NeedTestCase.Need) == -1.0f)
					TEST_TRUE(Set->GetMaxValue(NeedTestCase.Need) == -1.0f)

					Set->SetValue(NeedTestCase.Need, NeedTestCase.Value);
					Set->SetMaxValue(NeedTestCase.Need, NeedTestCase.MaxValue);

					TEST_TRUE(Set->GetValue(NeedTestCase.Need) == NeedTestCase.Value)
					TEST_TRUE(Set->GetMaxValue(NeedTestCase.Need) == NeedTestCase.MaxValue)
				}

				return true;
			});

			It("Given a need value update, expect the need set to broadcast the update", [this, SetClass]()
			{
				Set = NewObject<UBBNeedSet>(Character, SetClass);

				TMap<EBBNeed, UBBDossierEntryStub *> Entries;
				Entries.Emplace(EBBNeed::Hunger, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBNeed::Sleep, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBNeed::Thirst, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));

				UTEST_TRUE("Hunger Entry is valid", IsValid(Entries.FindChecked(EBBNeed::Hunger)))
				UTEST_TRUE("Sleep Entry is valid", IsValid(Entries.FindChecked(EBBNeed::Sleep)))
				UTEST_TRUE("Thirst Entry is valid", IsValid(Entries.FindChecked(EBBNeed::Thirst)))

				Entries.FindChecked(EBBNeed::Hunger)->Initialize(FText::FromString("Hunger Entry"),
					TSoftObjectPtr<UTexture2D>(nullptr),
					Set->GetValueDelegate(EBBNeed::Hunger),
					Set->GetMaxValueDelegate(EBBNeed::Hunger),
					Set->OnUpdate(EBBNeed::Hunger));
				Entries.FindChecked(EBBNeed::Sleep)->Initialize(FText::FromString("Sleep Entry"),
					TSoftObjectPtr<UTexture2D>(nullptr),
					Set->GetValueDelegate(EBBNeed::Sleep),
					Set->GetMaxValueDelegate(EBBNeed::Sleep),
					Set->OnUpdate(EBBNeed::Sleep));
				Entries.FindChecked(EBBNeed::Thirst)->Initialize(FText::FromString("Thirst Entry"),
					TSoftObjectPtr<UTexture2D>(nullptr),
					Set->GetValueDelegate(EBBNeed::Thirst),
					Set->GetMaxValueDelegate(EBBNeed::Thirst),
					Set->OnUpdate(EBBNeed::Thirst));

				TArray<float> UpdateValues;
				UpdateValues.Emplace(-250.61f);
				UpdateValues.Emplace(0.0f);
				UpdateValues.Emplace(315.88f);
				UpdateValues.Emplace(-92.74f);
				UpdateValues.Emplace(127.33f);

				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetValue(EBBNeed::Hunger) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBNeed::Sleep) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBNeed::Thirst) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBNeed::Hunger) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBNeed::Sleep) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBNeed::Thirst) == -1.0f)

				#define EBBNEED_OPERATION(Value) TestUpdate(Value, Set, Entries, UpdateValues);

					FOREACH_ENUM_EBBNEED(EBBNEED_OPERATION)

				#undef EBBNEED_OPERATION

				return true;
			});

			It("Given a need max value update, expect the need set to broadcast the update", [this, SetClass]()
			{
				Set = NewObject<UBBNeedSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TMap<EBBNeed, UBBDossierEntryStub *> Entries;
				Entries.Emplace(EBBNeed::Hunger, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBNeed::Sleep, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBNeed::Thirst, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));

				UTEST_TRUE("Hunger Entry is valid", IsValid(Entries.FindChecked(EBBNeed::Hunger)))
				UTEST_TRUE("Sleep Entry is valid", IsValid(Entries.FindChecked(EBBNeed::Sleep)))
				UTEST_TRUE("Thirst Entry is valid", IsValid(Entries.FindChecked(EBBNeed::Thirst)))
					
				Entries.FindChecked(EBBNeed::Hunger)->Initialize(FText::FromString("Hunger Entry"),
					TSoftObjectPtr<UTexture2D>(nullptr),
					Set->GetValueDelegate(EBBNeed::Hunger),
					Set->GetMaxValueDelegate(EBBNeed::Hunger),
					Set->OnUpdate(EBBNeed::Hunger));
				Entries.FindChecked(EBBNeed::Sleep)->Initialize(FText::FromString("Sleep Entry"),
					TSoftObjectPtr<UTexture2D>(nullptr),
					Set->GetValueDelegate(EBBNeed::Sleep),
					Set->GetMaxValueDelegate(EBBNeed::Sleep),
					Set->OnUpdate(EBBNeed::Sleep));
				Entries.FindChecked(EBBNeed::Thirst)->Initialize(FText::FromString("Thirst Entry"),
					TSoftObjectPtr<UTexture2D>(nullptr),
					Set->GetValueDelegate(EBBNeed::Thirst),
					Set->GetMaxValueDelegate(EBBNeed::Thirst),
					Set->OnUpdate(EBBNeed::Thirst));
				
				TArray<float> UpdateValues;
				UpdateValues.Emplace(43.71f);
				UpdateValues.Emplace(-724.42f);
				UpdateValues.Emplace(0.0f);
				UpdateValues.Emplace(-667.42f);
				UpdateValues.Emplace(152.67f);

				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetValue(EBBNeed::Hunger) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBNeed::Sleep) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBNeed::Thirst) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBNeed::Hunger) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBNeed::Sleep) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBNeed::Thirst) == -1.0f)

				#define EBBNEED_OPERATION(Value) TestMaxUpdate(Value, Set, Entries, UpdateValues);

					FOREACH_ENUM_EBBNEED(EBBNEED_OPERATION)

				#undef EBBNEED_OPERATION

				return true;
			});
		});
	}
}