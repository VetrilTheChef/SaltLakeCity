// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "Actors/Components/BBAIAbilityComponentStub.h"
#include "Attributes/BBSkillSet.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Data/BBDossierEntryStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBSkillSetSpec, "SaltLakeCity.Attributes.SkillSet", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

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
	UBBSkillSet * Set = nullptr;

	FActorSpawnParameters SpawnParameters;

	void TestSkill(EBBSkill Skill, UBBSkillSet * SkillSet, const TArray<float> & SkillValues)
	{
		for (const float & SkillValue : SkillValues)
		{
			SkillSet->SetValue(Skill, SkillValue);

			TEST_TRUE(SkillSet->GetValue(Skill) == SkillValue)
		}
	}

	void TestMaxSkill(EBBSkill Skill, UBBSkillSet * SkillSet, const TArray<float> & SkillValues)
	{
		for (const float & SkillValue : SkillValues)
		{
			SkillSet->SetMaxValue(Skill, SkillValue);

			TEST_TRUE(SkillSet->GetMaxValue(Skill) == SkillValue)
		}
	}

	void TestUpdate(EBBSkill Skill, UBBSkillSet * SkillSet, TMap<EBBSkill, UBBDossierEntryStub *> Entries, const TArray<float> & SkillValues)
	{
		for (const float & SkillValue : SkillValues)
		{
			SkillSet->SetValue(Skill, SkillValue);

			TEST_TRUE(Entries.FindChecked(Skill)->GetValue() == SkillValue)
		}
	}

	void TestMaxUpdate(EBBSkill Skill, UBBSkillSet * SkillSet, TMap<EBBSkill, UBBDossierEntryStub *> Entries, const TArray<float> & SkillValues)
	{
		for (const float & SkillValue : SkillValues)
		{
			SkillSet->SetMaxValue(Skill, SkillValue);

			TEST_TRUE(Entries.FindChecked(Skill)->GetMaxValue() == SkillValue)
		}
	}

END_DEFINE_SPEC(UBBSkillSetSpec)

void UBBSkillSetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBSkillSet>(FString(TEXT("/Game/Attributes")), SetClasses);

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
			It("Given a new skill value, expect the skill set to return the new value", [this, SetClass]()
			{
				Set = NewObject<UBBSkillSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TArray<float> SkillValues;
				SkillValues.Empty();

				SkillValues.Emplace(63.24f);
				SkillValues.Emplace(-72.57f);
				SkillValues.Emplace(-421.61f);
				SkillValues.Emplace(1658.12f);
				SkillValues.Emplace(0.0f);

				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetValue(EBBSkill::Build) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Fuck) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Guard) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Lead) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Research) == -1.0f)

				#define EBBSKILL_OPERATION(Value) TestSkill(Value, Set, SkillValues);

					FOREACH_ENUM_EBBSKILL(EBBSKILL_OPERATION)

				#undef EBBSKILL_OPERATION

				return true;
			});

			It("Given a new skill max value, expect the skill set to return the new value", [this, SetClass]()
			{
				Set = NewObject<UBBSkillSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TArray<float> SkillValues;
				SkillValues.Empty();

				SkillValues.Emplace(10.0f);
				SkillValues.Emplace(51.34f);
				SkillValues.Emplace(-23.47f);
				SkillValues.Emplace(0.0f);
				SkillValues.Emplace(0.04f);

				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetMaxValue(EBBSkill::Build) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Fuck) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Guard) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Lead) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Research) == -1.0f)
					
				#define EBBSKILL_OPERATION(Value) TestMaxSkill(Value, Set, SkillValues);

					FOREACH_ENUM_EBBSKILL(EBBSKILL_OPERATION)

				#undef EBBSKILL_OPERATION

				return true;
			});

			It("Given a skill, expect the skill set to return the skill's values", [this, SetClass]()
			{
				struct FBBSkillTestCase
				{
					public:
						FBBSkillTestCase() :
							Skill(EBBSkill::Build),
							Value(0.0f),
							MaxValue(0.0f)
						{};

						FBBSkillTestCase(EBBSkill NewSkill, float NewValue, float NewMaxValue) :
							Skill(NewSkill),
							Value(NewValue),
							MaxValue(NewMaxValue)
						{};

						EBBSkill Skill;

						float Value;

						float MaxValue;
				};

				Set = NewObject<UBBSkillSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TArray<FBBSkillTestCase> SkillTestCases;
				SkillTestCases.Empty();

				SkillTestCases.Emplace(FBBSkillTestCase(EBBSkill::Build, -622.31f, 754.12f));
				SkillTestCases.Emplace(FBBSkillTestCase(EBBSkill::Fuck, 252.37f, -563.24f));
				SkillTestCases.Emplace(FBBSkillTestCase(EBBSkill::Guard, 326.19f, 175.27f));
				SkillTestCases.Emplace(FBBSkillTestCase(EBBSkill::Lead, -589.24f, -127.35f));
				SkillTestCases.Emplace(FBBSkillTestCase(EBBSkill::Research, 326.51f, 873.51f));
				
				AbilityComponent->AddAttributeSet(Set);

				for (FBBSkillTestCase & SkillTestCase : SkillTestCases)
				{
					TEST_TRUE(Set->GetValue(SkillTestCase.Skill) == -1.0f)
					TEST_TRUE(Set->GetMaxValue(SkillTestCase.Skill) == -1.0f)

					Set->SetValue(SkillTestCase.Skill, SkillTestCase.Value);
					Set->SetMaxValue(SkillTestCase.Skill, SkillTestCase.MaxValue);

					TEST_TRUE(Set->GetValue(SkillTestCase.Skill) == SkillTestCase.Value)
					TEST_TRUE(Set->GetMaxValue(SkillTestCase.Skill) == SkillTestCase.MaxValue)
				}

				return true;
			});

			It("Given a skill value update, expect the skill set to broadcast the update", [this, SetClass]()
			{
				Set = NewObject<UBBSkillSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TMap<EBBSkill, UBBDossierEntryStub *> Entries;
				Entries.Emplace(EBBSkill::Build, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBSkill::Fuck, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBSkill::Guard, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBSkill::Lead, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBSkill::Research, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));

				UTEST_TRUE("Build Entry is valid", IsValid(Entries.FindChecked(EBBSkill::Build)))
				UTEST_TRUE("Fuck Entry is valid", IsValid(Entries.FindChecked(EBBSkill::Fuck)))
				UTEST_TRUE("Guard Entry is valid", IsValid(Entries.FindChecked(EBBSkill::Guard)))
				UTEST_TRUE("Lead Entry is valid", IsValid(Entries.FindChecked(EBBSkill::Lead)))
				UTEST_TRUE("Research Entry is valid", IsValid(Entries.FindChecked(EBBSkill::Research)))

				Entries.FindChecked(EBBSkill::Build)->Initialize(FText::FromString("Build Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBSkill::Build), & Set->OnMaxValueUpdate(EBBSkill::Build));
				Entries.FindChecked(EBBSkill::Fuck)->Initialize(FText::FromString("Fuck Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBSkill::Fuck), & Set->OnMaxValueUpdate(EBBSkill::Fuck));
				Entries.FindChecked(EBBSkill::Guard)->Initialize(FText::FromString("Guard Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBSkill::Guard), & Set->OnMaxValueUpdate(EBBSkill::Guard));
				Entries.FindChecked(EBBSkill::Lead)->Initialize(FText::FromString("Lead Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBSkill::Lead), & Set->OnMaxValueUpdate(EBBSkill::Lead));
				Entries.FindChecked(EBBSkill::Research)->Initialize(FText::FromString("Research Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBSkill::Research), & Set->OnMaxValueUpdate(EBBSkill::Research));

				TArray<float> UpdateValues;
				UpdateValues.Emplace(735.12f);
				UpdateValues.Emplace(-43.61f);
				UpdateValues.Emplace(537.32f);
				UpdateValues.Emplace(0.0f);
				UpdateValues.Emplace(-634.41f);

				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetValue(EBBSkill::Build) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Fuck) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Guard) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Lead) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Guard) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Build) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Fuck) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Guard) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Lead) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Guard) == -1.0f)

				#define EBBSKILL_OPERATION(Value) TestUpdate(Value, Set, Entries, UpdateValues);

					FOREACH_ENUM_EBBSKILL(EBBSKILL_OPERATION)

				#undef EBBSKILL_OPERATION

				return true;
			});

			It("Given a skill value update, expect the skill set to broadcast the update", [this, SetClass]()
			{
				Set = NewObject<UBBSkillSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TMap<EBBSkill, UBBDossierEntryStub *> Entries;
				Entries.Emplace(EBBSkill::Build, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBSkill::Fuck, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBSkill::Guard, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBSkill::Lead, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBSkill::Research, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));

				UTEST_TRUE("Build Entry is valid", IsValid(Entries.FindChecked(EBBSkill::Build)))
				UTEST_TRUE("Fuck Entry is valid", IsValid(Entries.FindChecked(EBBSkill::Fuck)))
				UTEST_TRUE("Guard Entry is valid", IsValid(Entries.FindChecked(EBBSkill::Guard)))
				UTEST_TRUE("Lead Entry is valid", IsValid(Entries.FindChecked(EBBSkill::Lead)))
				UTEST_TRUE("Research Entry is valid", IsValid(Entries.FindChecked(EBBSkill::Research)))

				Entries.FindChecked(EBBSkill::Build)->Initialize(FText::FromString("Build Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBSkill::Build), & Set->OnMaxValueUpdate(EBBSkill::Build));
				Entries.FindChecked(EBBSkill::Fuck)->Initialize(FText::FromString("Fuck Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBSkill::Fuck), & Set->OnMaxValueUpdate(EBBSkill::Fuck));
				Entries.FindChecked(EBBSkill::Guard)->Initialize(FText::FromString("Guard Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBSkill::Guard), & Set->OnMaxValueUpdate(EBBSkill::Guard));
				Entries.FindChecked(EBBSkill::Lead)->Initialize(FText::FromString("Lead Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBSkill::Lead), & Set->OnMaxValueUpdate(EBBSkill::Lead));
				Entries.FindChecked(EBBSkill::Research)->Initialize(FText::FromString("Research Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBSkill::Research), & Set->OnMaxValueUpdate(EBBSkill::Research));

				TArray<float> UpdateValues;
				UpdateValues.Emplace(0.0f);
				UpdateValues.Emplace(672.23f);
				UpdateValues.Emplace(-314.12f);
				UpdateValues.Emplace(-63.24f);
				UpdateValues.Emplace(737.89f);

				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetValue(EBBSkill::Build) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Fuck) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Guard) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Lead) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBSkill::Guard) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Build) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Fuck) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Guard) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Lead) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBSkill::Guard) == -1.0f)

				#define EBBSKILL_OPERATION(Value) TestMaxUpdate(Value, Set, Entries, UpdateValues);

					FOREACH_ENUM_EBBSKILL(EBBSKILL_OPERATION)

				#undef EBBSKILL_OPERATION

				return true;
			});
		});
	}
}