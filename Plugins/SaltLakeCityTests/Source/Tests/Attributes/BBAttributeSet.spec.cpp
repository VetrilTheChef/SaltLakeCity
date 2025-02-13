// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "Actors/Components/BBAIAbilityComponentStub.h"
#include "Attributes/BBAttributeSet.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Data/BBDossierEntryStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBAttributeSetSpec, "SaltLakeCity.Attributes.AttributeSet", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

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
	UBBAttributeSet * Set = nullptr;

	FActorSpawnParameters SpawnParameters;

	void TestAttribute(EBBAttribute Attribute, UBBAttributeSet * AttributeSet, const TArray<float> & AttributeValues)
	{
		for (const float & AttributeValue : AttributeValues)
		{
			AttributeSet->SetValue(Attribute, AttributeValue);

			TEST_TRUE(AttributeSet->GetValue(Attribute) == AttributeValue)
		}
	}

	void TestMaxAttribute(EBBAttribute Attribute, UBBAttributeSet * AttributeSet, const TArray<float> & AttributeValues)
	{
		for (const float & AttributeValue : AttributeValues)
		{
			AttributeSet->SetMaxValue(Attribute, AttributeValue);

			TEST_TRUE(AttributeSet->GetMaxValue(Attribute) == AttributeValue)
		}
	}

	void TestUpdate(EBBAttribute Attribute, UBBAttributeSet * AttributeSet, TMap<EBBAttribute, UBBDossierEntryStub *> Entries, const TArray<float> & AttributeValues)
	{
		for (const float & AttributeValue : AttributeValues)
		{
			AttributeSet->SetValue(Attribute, AttributeValue);

			TEST_TRUE(Entries.FindChecked(Attribute)->GetValue() == AttributeValue)
		}
	}

	void TestMaxUpdate(EBBAttribute Attribute, UBBAttributeSet * AttributeSet, TMap<EBBAttribute, UBBDossierEntryStub *> Entries, const TArray<float> & AttributeValues)
	{
		for (const float & AttributeValue : AttributeValues)
		{
			AttributeSet->SetMaxValue(Attribute, AttributeValue);

			TEST_TRUE(Entries.FindChecked(Attribute)->GetMaxValue() == AttributeValue)
		}
	}

END_DEFINE_SPEC(UBBAttributeSetSpec)

void UBBAttributeSetSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBAttributeSet>(FString(TEXT("/Game/Attributes")), SetClasses);

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
			It("Given a new attribute value, expect the attribute set to return the new value", [this, SetClass]()
			{
				Set = NewObject<UBBAttributeSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TArray<float> SkillValues;
				SkillValues.Emplace(-52.06f);
				SkillValues.Emplace(734.1f);
				SkillValues.Emplace(0.0f);
				SkillValues.Emplace(-1770.22f);
				SkillValues.Emplace(560.72f);
				
				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetValue(EBBAttribute::Health) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBAttribute::Stamina) == -1.0f)

				#define EBBATTRIBUTE_OPERATION(Value) TestAttribute(Value, Set, SkillValues);

					FOREACH_ENUM_EBBATTRIBUTE(EBBATTRIBUTE_OPERATION)

				#undef EBBATTRIBUTE_OPERATION

				return true;
			});

			It("Given a new attribute max value, expect the attribute set to return the new value", [this, SetClass]()
			{
				Set = NewObject<UBBAttributeSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TArray<float> SkillValues;
				SkillValues.Emplace(100.0f);
				SkillValues.Emplace(21.112f);
				SkillValues.Emplace(470.0f);
				SkillValues.Emplace(0.0f);
				SkillValues.Emplace(-14.21f);

				AbilityComponent->AddAttributeSet(Set);
				
				TEST_TRUE(Set->GetMaxValue(EBBAttribute::Health) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBAttribute::Stamina) == -1.0f)

				#define EBBATTRIBUTE_OPERATION(Value) TestMaxAttribute(Value, Set, SkillValues);

					FOREACH_ENUM_EBBATTRIBUTE(EBBATTRIBUTE_OPERATION)

				#undef EBBATTRIBUTE_OPERATION

				return true;
			});

			It("Given an attribute, expect the attribute set to return the attribute's values", [this, SetClass]()
			{
				Set = NewObject<UBBAttributeSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				float HealthValue = 457.81f;
				float HealthMaxValue = -688.24f;
				float StaminaValue = -362.67f;
				float StaminaMaxValue = 865.47f;

				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetValue(EBBAttribute::Health) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBAttribute::Stamina) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBAttribute::Health) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBAttribute::Stamina) == -1.0f)

				Set->SetValue(EBBAttribute::Health, HealthValue);
				Set->SetValue(EBBAttribute::Stamina, StaminaValue);
				Set->SetMaxValue(EBBAttribute::Health, HealthMaxValue);
				Set->SetMaxValue(EBBAttribute::Stamina, StaminaMaxValue);

				TEST_TRUE(Set->GetValue(EBBAttribute::Health) == HealthValue)
				TEST_TRUE(Set->GetValue(EBBAttribute::Stamina) == StaminaValue)
				TEST_TRUE(Set->GetMaxValue(EBBAttribute::Health) == HealthMaxValue)
				TEST_TRUE(Set->GetMaxValue(EBBAttribute::Stamina) == StaminaMaxValue)

				return true;
			});

			It("Given an attribute value update, expect the attribute set to broadcast the update", [this, SetClass]()
			{
				Set = NewObject<UBBAttributeSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))

				TMap<EBBAttribute, UBBDossierEntryStub *> Entries;
				Entries.Emplace(EBBAttribute::Health, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBAttribute::Stamina, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));

				UTEST_TRUE("Health Entry is valid", IsValid(Entries.FindChecked(EBBAttribute::Health)))
				UTEST_TRUE("Stamina Entry is valid", IsValid(Entries.FindChecked(EBBAttribute::Stamina)))

				Entries.FindChecked(EBBAttribute::Health)->Initialize(FText::FromString("Health Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBAttribute::Health), & Set->OnMaxValueUpdate(EBBAttribute::Health));
				Entries.FindChecked(EBBAttribute::Stamina)->Initialize(FText::FromString("Stamina Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBAttribute::Stamina), & Set->OnMaxValueUpdate(EBBAttribute::Stamina));

				TArray<float> UpdateValues;
				UpdateValues.Emplace(-100.54f);
				UpdateValues.Emplace(85.58f);
				UpdateValues.Emplace(0.0f);
				UpdateValues.Emplace(-95.75f);
				UpdateValues.Emplace(61.25f);

				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetValue(EBBAttribute::Health) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBAttribute::Stamina) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBAttribute::Health) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBAttribute::Stamina) == -1.0f)

				#define EBBATTRIBUTE_OPERATION(Value) TestUpdate(Value, Set, Entries, UpdateValues);

					FOREACH_ENUM_EBBATTRIBUTE(EBBATTRIBUTE_OPERATION)

				#undef EBBATTRIBUTE_OPERATION

				return true;
			});

			It("Given an attribute max value update, expect the attribute set to broadcast the update", [this, SetClass]()
			{
				Set = NewObject<UBBAttributeSet>(Character, SetClass);

				UTEST_TRUE("Set is valid", IsValid(Set))
				
				TMap<EBBAttribute, UBBDossierEntryStub *> Entries;
				Entries.Emplace(EBBAttribute::Health, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));
				Entries.Emplace(EBBAttribute::Stamina, NewObject<UBBDossierEntryStub>(Set, UBBDossierEntryStub::StaticClass()));

				UTEST_TRUE("Health Entry is valid", IsValid(Entries.FindChecked(EBBAttribute::Health)))
				UTEST_TRUE("Stamina Entry is valid", IsValid(Entries.FindChecked(EBBAttribute::Stamina)))

				Entries.FindChecked(EBBAttribute::Health)->Initialize(FText::FromString("Health Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBAttribute::Health), & Set->OnMaxValueUpdate(EBBAttribute::Health));
				Entries.FindChecked(EBBAttribute::Stamina)->Initialize(FText::FromString("Stamina Entry"), TSoftObjectPtr<UTexture2D>(nullptr), & Set->OnValueUpdate(EBBAttribute::Stamina), & Set->OnMaxValueUpdate(EBBAttribute::Stamina));

				TArray<float> UpdateValues;
				UpdateValues.Emplace(-15.07f);
				UpdateValues.Emplace(-277.84f);
				UpdateValues.Emplace(186.53f);
				UpdateValues.Emplace(613.22f);
				UpdateValues.Emplace(0.0f);

				AbilityComponent->AddAttributeSet(Set);

				TEST_TRUE(Set->GetValue(EBBAttribute::Health) == -1.0f)
				TEST_TRUE(Set->GetValue(EBBAttribute::Stamina) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBAttribute::Health) == -1.0f)
				TEST_TRUE(Set->GetMaxValue(EBBAttribute::Stamina) == -1.0f)

				#define EBBATTRIBUTE_OPERATION(Value) TestMaxUpdate(Value, Set, Entries, UpdateValues);

					FOREACH_ENUM_EBBATTRIBUTE(EBBATTRIBUTE_OPERATION)

				#undef EBBATTRIBUTE_OPERATION

				return true;
			});
		});
	}
}