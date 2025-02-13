// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "Actors/Characters/Interfaces/IBBCharacter.h"
#include "Actors/Components/BBAIAbilityComponentStub.h"
#include "Attributes/BBAttributeSetStub.h"
#include "Attributes/BBNeedSetStub.h"
#include "Attributes/BBSkillSetStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Data/Interfaces/IBBDossierEntry.h"
#include "GUI/Models/BBDossierModel.h"
#include "GUI/Widgets/BBDossierWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBDossierModelSpec, "SaltLakeCity.GUI.Models.Dossier", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBDossierWidgetStub * View = nullptr;

	UPROPERTY()
	TArray<UClass *> ModelClasses;

	// SUT
	UPROPERTY()
	UBBDossierModel * Model = nullptr;

	FActorSpawnParameters SpawnParameters;

	template <typename E, class T, class U>
	bool TestEntry(E Enumerator, UBBDossierModel * Model, const T * Set)
	{
		U * Entry = Model->GetDossierEntry(Enumerator);

		UTEST_TRUE("Entry is valid", IsValid(Entry))

		TEST_TRUE(Entry->GetValue() == Set->GetValue(Enumerator))
		TEST_TRUE(Entry->GetMaxValue() == Set->GetMaxValue(Enumerator))

		return true;
	}

END_DEFINE_SPEC(UBBDossierModelSpec)

void UBBDossierModelSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDossierModel>(FString(TEXT("/Game/GUI/Models")), ModelClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		View = CreateWidget<UBBDossierWidgetStub>(TestWorld, UBBDossierWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		return true;
	});

	AfterEach([this]()
	{
		Model = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ModelClass : ModelClasses)
	{
		Describe("[" + ModelClass->GetName() + "]", [this, ModelClass]()
		{
			It("Given a new character, expect the model to expose the character data", [this, ModelClass]()
			{
				TArray<ABBCharacterStub *> Characters;
				Characters.Empty();

				for (int i = 0; i < 5; i++)
				{
					ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(SpawnParameters);

					UTEST_TRUE("Character is valid", IsValid(Character))

					UBBAIAbilityComponentStub * AbilityComponent = NewObject<UBBAIAbilityComponentStub>(Character, UBBAIAbilityComponentStub::StaticClass());

					UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))
					
					UBBAttributeSetStub * AttributeSet = NewObject<UBBAttributeSetStub>(Character, UBBAttributeSetStub::StaticClass());

					UTEST_TRUE("Derived Attribute Set is valid", IsValid(AttributeSet))
				
					UBBNeedSetStub * NeedSet = NewObject<UBBNeedSetStub>(Character, UBBNeedSetStub::StaticClass());

					UTEST_TRUE("Need Set is valid", IsValid(NeedSet))
					
					UBBSkillSetStub * SkillSet = NewObject<UBBSkillSetStub>(Character, UBBSkillSetStub::StaticClass());

					UTEST_TRUE("Skill Set is valid", IsValid(SkillSet))

					AbilityComponent->AddAttributeSet(AttributeSet);
					AbilityComponent->AddAttributeSet(NeedSet);
					AbilityComponent->AddAttributeSet(SkillSet);

					Character->SetAbilitySystemComponent(AbilityComponent);

					Characters.Emplace(Character);
				}

				for (ABBCharacterStub * & Character : Characters)
				{
					Model = NewObject<UBBDossierModel>(TestWorld, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, Character);

					TEST_TRUE(Model->GetDisplayName().EqualTo(Character->GetDisplayName(EBBDisplayName::Full)))

					Model->Finalize();
				}

				for (ABBCharacterStub * & Character : Characters)
				{
					TestWorld->DestroyActor(Character);
				}

				return true;
			});

			It("Given a new character, expect the model to create the attribute entries", [this, ModelClass]()
			{
				struct FBBAttributeTestCase
				{
					public:
						FBBAttributeTestCase(EBBAttribute NewAttribute, float NewValue, float NewMaxValue) :
							Attribute(NewAttribute),
							Value(NewValue),
							MaxValue(NewMaxValue)
						{};

						EBBAttribute Attribute = EBBAttribute::Health;

						float Value = 0.0f;

						float MaxValue = 0.0f;
				};

				TArray<FBBAttributeTestCase> TestCases;
				TestCases.Empty();
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Health, 120.0f, 115.9f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Health, 12.5f, -15.6f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Health, -327.3f, 216.7f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Health, 1350.0f, -516.5f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Health, -25.5f, 63.2f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Stamina, -2368.71f, -834.25f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Stamina, 0.05f, 16.74f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Stamina, 47.128f, -763.46f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Stamina, 893.56f, 5634.62f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Stamina, -532.41f, 83.51f));
				
				TArray<ABBCharacterStub *> Characters;
				Characters.Empty();

				for (int i = 0; i < 5; i++)
				{
					ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(SpawnParameters);

					UTEST_TRUE("Character is valid", IsValid(Character))

					UBBAIAbilityComponentStub * AbilityComponent = NewObject<UBBAIAbilityComponentStub>(Character, UBBAIAbilityComponentStub::StaticClass());

					UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))
						
					UBBAttributeSetStub * AttributeSet = NewObject<UBBAttributeSetStub>(Character, UBBAttributeSetStub::StaticClass());

					UTEST_TRUE("Attribute Set is valid", IsValid(AttributeSet))

					UBBNeedSetStub * NeedSet = NewObject<UBBNeedSetStub>(Character, UBBNeedSetStub::StaticClass());

					UTEST_TRUE("Need Set is valid", IsValid(NeedSet))
				
					UBBSkillSetStub * SkillSet = NewObject<UBBSkillSetStub>(Character, UBBSkillSetStub::StaticClass());

					UTEST_TRUE("Skill Set is valid", IsValid(SkillSet))

					AbilityComponent->AddAttributeSet(AttributeSet);
					AbilityComponent->AddAttributeSet(NeedSet);
					AbilityComponent->AddAttributeSet(SkillSet);

					Character->SetAbilitySystemComponent(AbilityComponent);

					AttributeSet->SetValue(TestCases[i].Attribute, TestCases[i].Value);
					AttributeSet->SetMaxValue(TestCases[i].Attribute, TestCases[i].MaxValue);

					Characters.Emplace(Character);
				}

				for (ABBCharacterStub * & Character : Characters)
				{
					Model = NewObject<UBBDossierModel>(TestWorld, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, Character);

					const UIBBAttributeSet * AttributeSet = Character->GetAbilitySystemComponent()->GetSet<UIBBAttributeSet>();

					UTEST_TRUE("Attribute Set is valid", IsValid(AttributeSet))
					
					#define EBBATTRIBUTE_OPERATION(Value) TestEntry<EBBAttribute, UIBBAttributeSet, UIBBDossierEntry>(Value, Model, AttributeSet);

						FOREACH_ENUM_EBBATTRIBUTE(EBBATTRIBUTE_OPERATION)

					#undef EBBATTRIBUTE_OPERATION

					Model->Finalize();
				}

				for (ABBCharacterStub * & Character : Characters)
				{
					TestWorld->DestroyActor(Character);
				}

				return true;
			});

			It("Given a new character, expect the model to create the need entries", [this, ModelClass]()
			{
				struct FBBNeedTestCase
				{
					public:
						FBBNeedTestCase(EBBNeed NewNeed, float NewValue, float NewMaxValue) :
							Need(NewNeed),
							Value(NewValue),
							MaxValue(NewMaxValue)
						{};

						EBBNeed Need = EBBNeed::Hunger;

						float Value = 0.0f;

						float MaxValue = 0.0f;
				};

				TArray<FBBNeedTestCase> TestCases;
				TestCases.Empty();
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Hunger, 724.6f, 918.35f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Hunger, -425.21f, 141.22f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Hunger, -834.56f, -523.51f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Hunger, 163.2f, -24.11f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Hunger, 724.12f, 121.21f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Sleep, 842.37f, 657.89f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Sleep, -392.64f, 219.54f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Sleep, -753.21f, -482.16f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Sleep, 203.45f, -78.63f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Sleep, 615.29f, 132.87f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Thirst, 437.82f, 845.16f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Thirst, -213.49f, 352.78f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Thirst, -682.34f, -521.07f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Thirst, 174.23f, -65.89f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Thirst, 789.45f, 214.38f));
				
				TArray<ABBCharacterStub *> Characters;
				Characters.Empty();

				for (int i = 0; i < 5; i++)
				{
					ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(SpawnParameters);

					UTEST_TRUE("Character is valid", IsValid(Character))

					UBBAIAbilityComponentStub * AbilityComponent = NewObject<UBBAIAbilityComponentStub>(Character, UBBAIAbilityComponentStub::StaticClass());

					UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))
					UBBAttributeSetStub * AttributeSet = NewObject<UBBAttributeSetStub>(Character, UBBAttributeSetStub::StaticClass());

					UTEST_TRUE("Attribute Set is valid", IsValid(AttributeSet))

					UBBNeedSetStub * NeedSet = NewObject<UBBNeedSetStub>(Character, UBBNeedSetStub::StaticClass());

					UTEST_TRUE("Need Set is valid", IsValid(NeedSet))

					UBBSkillSetStub * SkillSet = NewObject<UBBSkillSetStub>(Character, UBBSkillSetStub::StaticClass());

					UTEST_TRUE("Skill Set is valid", IsValid(SkillSet))

					AbilityComponent->AddAttributeSet(AttributeSet);
					AbilityComponent->AddAttributeSet(NeedSet);
					AbilityComponent->AddAttributeSet(SkillSet);

					Character->SetAbilitySystemComponent(AbilityComponent);

					NeedSet->SetValue(TestCases[i].Need, TestCases[i].Value);
					NeedSet->SetMaxValue(TestCases[i].Need, TestCases[i].MaxValue);

					Characters.Emplace(Character);
				}

				for (ABBCharacterStub * & Character : Characters)
				{
					Model = NewObject<UBBDossierModel>(TestWorld, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, Character);

					const UIBBNeedSet * NeedSet = Character->GetAbilitySystemComponent()->GetSet<UIBBNeedSet>();

					UTEST_TRUE("Need Set is valid", IsValid(NeedSet))
					
					#define EBBNEED_OPERATION(Value) TestEntry<EBBNeed, UIBBNeedSet, UIBBDossierEntry>(Value, Model, NeedSet);

						FOREACH_ENUM_EBBNEED(EBBNEED_OPERATION)

					#undef EBBNEED_OPERATION

					Model->Finalize();
				}

				for (ABBCharacterStub * & Character : Characters)
				{
					TestWorld->DestroyActor(Character);
				}

				return true;
			});

			It("Given a new character, expect the model to create the skill entries", [this, ModelClass]()
			{
				struct FBBSkillTestCase
				{
					public:
						FBBSkillTestCase(EBBSkill NewSkill, float NewValue, float NewMaxValue) :
							Skill(NewSkill),
							Value(NewValue),
							MaxValue(NewMaxValue)
						{};

						EBBSkill Skill = EBBSkill::Build;

						float Value = 0.0f;

						float MaxValue = 0.0f;
				};

				TArray<FBBSkillTestCase> TestCases;
				TestCases.Empty();
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Build, 123.45f, 68.90f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Build, -234.6f, 345.67f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Build, 2789.12f, -456.78f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Build, 91.11f, 112.3f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Build, -314.15f, 6.53f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Fuck, 415.92f, -63.58f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Fuck, 59.79f, 323.84f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Fuck, -626.43f, 33.27f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Fuck, 6502.88f, -419.71f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Fuck, 697.93f, 28.46f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Guard, 4.33f, -5832.79f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Guard, -502.8f, 719.45f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Guard, 93.45f, -372.89f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Guard, -475.85f, 629.3f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Guard, 1738.21f, 764.32f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Lead, 58.72f, -394.85f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Lead, -1672.39f, 489.12f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Lead, 234.78f, 567.89f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Lead, 192.83f, -3384.29f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Lead, -849.21f, 710.32f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Research, -723.91f, 94.8f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Research, 658.34f, 1285.72f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Research, -38.12f, -574.29f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Research, 1902.4f, 1132.48f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Research, 4.21f, -829.4f));
				
				TArray<ABBCharacterStub *> Characters;
				Characters.Empty();

				for (int i = 0; i < 5; i++)
				{
					ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(SpawnParameters);

					UTEST_TRUE("Character is valid", IsValid(Character))

					UBBAIAbilityComponentStub * AbilityComponent = NewObject<UBBAIAbilityComponentStub>(Character, UBBAIAbilityComponentStub::StaticClass());

					UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))

					UBBAttributeSetStub * AttributeSet = NewObject<UBBAttributeSetStub>(Character, UBBAttributeSetStub::StaticClass());

					UTEST_TRUE("Attribute Set is valid", IsValid(AttributeSet))

					UBBNeedSetStub * NeedSet = NewObject<UBBNeedSetStub>(Character, UBBNeedSetStub::StaticClass());

					UTEST_TRUE("Need Set is valid", IsValid(NeedSet))

					UBBSkillSetStub * SkillSet = NewObject<UBBSkillSetStub>(Character, UBBSkillSetStub::StaticClass());

					UTEST_TRUE("Skill Set is valid", IsValid(SkillSet))

					AbilityComponent->AddAttributeSet(AttributeSet);
					AbilityComponent->AddAttributeSet(NeedSet);
					AbilityComponent->AddAttributeSet(SkillSet);

					AbilityComponent->AddAttributeSet(SkillSet);

					Character->SetAbilitySystemComponent(AbilityComponent);

					SkillSet->SetValue(TestCases[i].Skill, TestCases[i].Value);
					SkillSet->SetMaxValue(TestCases[i].Skill, TestCases[i].MaxValue);

					Characters.Emplace(Character);
				}

				for (ABBCharacterStub * & Character : Characters)
				{
					Model = NewObject<UBBDossierModel>(TestWorld, ModelClass);

					UTEST_TRUE("Model is valid", IsValid(Model))

					Model->Initialize(View, Character);

					const UIBBSkillSet * SkillSet = Character->GetAbilitySystemComponent()->GetSet<UIBBSkillSet>();

					UTEST_TRUE("Skill Set is valid", IsValid(SkillSet))
					
					#define EBBSKILL_OPERATION(Value) TestEntry<EBBSkill, UIBBSkillSet, UIBBDossierEntry>(Value, Model, SkillSet);

						FOREACH_ENUM_EBBSKILL(EBBSKILL_OPERATION)

					#undef EBBSKILL_OPERATION

					Model->Finalize();
				}

				for (ABBCharacterStub * & Character : Characters)
				{
					TestWorld->DestroyActor(Character);
				}

				return true;
			});

			It("Given a name update from the character, expect the model to update it", [this, ModelClass]()
			{
				TArray<FText> DisplayNames;
				DisplayNames.Empty();
				DisplayNames.Emplace(FText::FromString("Nice Name"));
				DisplayNames.Emplace(FText::FromString("Awesome"));
				DisplayNames.Emplace(FText::FromString("Weird251"));
				DisplayNames.Emplace(FText::FromString("TH98qt58!__"));
				DisplayNames.Emplace(FText::FromString("_   ?% _ -"));

				Model = NewObject<UBBDossierModel>(TestWorld, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(SpawnParameters);

				UTEST_TRUE("Character is valid", IsValid(Character))

				UBBAIAbilityComponentStub * AbilityComponent = NewObject<UBBAIAbilityComponentStub>(Character, UBBAIAbilityComponentStub::StaticClass());

				UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))
					
				UBBAttributeSetStub * AttributeSet = NewObject<UBBAttributeSetStub>(Character, UBBAttributeSetStub::StaticClass());

				UTEST_TRUE("Attribute Set is valid", IsValid(AttributeSet))

				UBBNeedSetStub * NeedSet = NewObject<UBBNeedSetStub>(Character, UBBNeedSetStub::StaticClass());

				UTEST_TRUE("Need Set is valid", IsValid(NeedSet))
				
				UBBSkillSetStub * SkillSet = NewObject<UBBSkillSetStub>(Character, UBBSkillSetStub::StaticClass());

				UTEST_TRUE("Skill Set is valid", IsValid(SkillSet))

				AbilityComponent->AddAttributeSet(AttributeSet);
				AbilityComponent->AddAttributeSet(NeedSet);
				AbilityComponent->AddAttributeSet(SkillSet);

				Character->SetAbilitySystemComponent(AbilityComponent);

				Model->Initialize(View, Character);

				for (FText & DisplayName : DisplayNames)
				{
					Character->SetDisplayName(DisplayName);

					TEST_TRUE(Model->GetDisplayName().EqualTo(Character->GetDisplayName(EBBDisplayName::Full)))
				}

				Model->Finalize();

				TestWorld->DestroyActor(Character);

				return true;
			});

			It("Given an attribute update from the character, expect the model to update the related attribute entry", [this, ModelClass]()
			{
				struct FBBAttributeTestCase
				{
					public:
						FBBAttributeTestCase(EBBAttribute NewAttribute, float NewValue, float NewMaxValue) :
							Attribute(NewAttribute),
							Value(NewValue),
							MaxValue(NewMaxValue)
						{};

						EBBAttribute Attribute = EBBAttribute::Health;

						float Value = 0.0f;

						float MaxValue = 0.0f;
				};

				TArray<FBBAttributeTestCase> TestCases;
				TestCases.Empty();
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Health, 235.7f, 97.4f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Health, 18.2f, -34.8f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Health, -412.9f, 158.3f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Health, 1427.8f, -623.4f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Health, -37.6f, 74.9f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Stamina, -1892.5f, -721.8f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Stamina, 0.19f, 23.6f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Stamina, 64.3f, -832.5f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Stamina, 1012.8f, 4895.4f));
				TestCases.Emplace(FBBAttributeTestCase(EBBAttribute::Stamina, -478.2f, 92.7f));

				Model = NewObject<UBBDossierModel>(TestWorld, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(SpawnParameters);

				UTEST_TRUE("Character is valid", IsValid(Character))

				UBBAIAbilityComponentStub * AbilityComponent = NewObject<UBBAIAbilityComponentStub>(Character, UBBAIAbilityComponentStub::StaticClass());

				UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))

				UBBAttributeSetStub * AttributeSet = NewObject<UBBAttributeSetStub>(Character, UBBAttributeSetStub::StaticClass());

				UTEST_TRUE("Derived Attribute Set is valid", IsValid(AttributeSet))
				
				UBBNeedSetStub * NeedSet = NewObject<UBBNeedSetStub>(Character, UBBNeedSetStub::StaticClass());

				UTEST_TRUE("Need Set is valid", IsValid(NeedSet))
				
				UBBSkillSetStub * SkillSet = NewObject<UBBSkillSetStub>(Character, UBBSkillSetStub::StaticClass());

				UTEST_TRUE("Skill Set is valid", IsValid(SkillSet))

				AbilityComponent->AddAttributeSet(AttributeSet);
				AbilityComponent->AddAttributeSet(NeedSet);
				AbilityComponent->AddAttributeSet(SkillSet);

				Character->SetAbilitySystemComponent(AbilityComponent);

				AttributeSet->SetValue(EBBAttribute::Health, 0.0f);
				AttributeSet->SetValue(EBBAttribute::Stamina, 0.0f);
				AttributeSet->SetMaxValue(EBBAttribute::Health, 0.0f);
				AttributeSet->SetMaxValue(EBBAttribute::Stamina, 0.0f);

				Model->Initialize(View, Character);

				for (FBBAttributeTestCase & TestCase : TestCases)
				{
					AttributeSet->SetValue(TestCase.Attribute, TestCase.Value);

					#define EBBATTRIBUTE_OPERATION(Value) TestEntry<EBBAttribute, UIBBAttributeSet, UIBBDossierEntry>(Value, Model, AttributeSet);

						FOREACH_ENUM_EBBATTRIBUTE(EBBATTRIBUTE_OPERATION)

					#undef EBBATTRIBUTE_OPERATION
				}

				Model->Finalize();

				TestWorld->DestroyActor(Character);

				return true;
			});

			It("Given a need update from the character, expect the model to update the related need entry", [this, ModelClass]()
			{
				struct FBBNeedTestCase
				{
					public:
						FBBNeedTestCase(EBBNeed NewNeed, float NewValue, float NewMaxValue) :
							Need(NewNeed),
							Value(NewValue),
							MaxValue(NewMaxValue)
						{};

						EBBNeed Need = EBBNeed::Hunger;

						float Value = 0.0f;

						float MaxValue = 0.0f;
				};

				TArray<FBBNeedTestCase> TestCases;
				TestCases.Empty();
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Hunger, 347.8f, 129.4f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Hunger, 22.5f, -45.3f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Hunger, -526.4f, 198.2f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Hunger, 1583.7f, -712.9f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Hunger, -52.1f, 89.6f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Sleep, -2035.6f, -841.3f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Sleep, 0.45f, 30.2f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Sleep, 78.2f, -912.4f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Sleep, 1124.5f, 5213.6f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Sleep, -512.8f, 108.3f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Thirst, -1756.3f, -648.7f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Thirst, 0.32f, 28.4f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Thirst, 85.4f, -726.5f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Thirst, 1345.7f, 4827.8f));
				TestCases.Emplace(FBBNeedTestCase(EBBNeed::Thirst, -528.9f, 116.2f));

				Model = NewObject<UBBDossierModel>(TestWorld, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(SpawnParameters);

				UTEST_TRUE("Character is valid", IsValid(Character))

				UBBAIAbilityComponentStub * AbilityComponent = NewObject<UBBAIAbilityComponentStub>(Character, UBBAIAbilityComponentStub::StaticClass());

				UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))

				UBBAttributeSetStub * AttributeSet = NewObject<UBBAttributeSetStub>(Character, UBBAttributeSetStub::StaticClass());

				UTEST_TRUE("Derived Attribute Set is valid", IsValid(AttributeSet))
				
				UBBNeedSetStub * NeedSet = NewObject<UBBNeedSetStub>(Character, UBBNeedSetStub::StaticClass());

				UTEST_TRUE("Need Set is valid", IsValid(NeedSet))
				
				UBBSkillSetStub * SkillSet = NewObject<UBBSkillSetStub>(Character, UBBSkillSetStub::StaticClass());

				UTEST_TRUE("Skill Set is valid", IsValid(SkillSet))

				AbilityComponent->AddAttributeSet(AttributeSet);
				AbilityComponent->AddAttributeSet(NeedSet);
				AbilityComponent->AddAttributeSet(SkillSet);

				Character->SetAbilitySystemComponent(AbilityComponent);

				NeedSet->SetValue(EBBNeed::Hunger, 0.0f);
				NeedSet->SetValue(EBBNeed::Sleep, 0.0f);
				NeedSet->SetValue(EBBNeed::Thirst, 0.0f);
				NeedSet->SetMaxValue(EBBNeed::Hunger, 0.0f);
				NeedSet->SetMaxValue(EBBNeed::Sleep, 0.0f);
				NeedSet->SetMaxValue(EBBNeed::Thirst, 0.0f);

				Model->Initialize(View, Character);

				for (FBBNeedTestCase & TestCase : TestCases)
				{
					NeedSet->SetValue(TestCase.Need, TestCase.Value);

					#define EBBNEED_OPERATION(Value) TestEntry<EBBNeed, UIBBNeedSet, UIBBDossierEntry>(Value, Model, NeedSet);

						FOREACH_ENUM_EBBNEED(EBBNEED_OPERATION)

					#undef EBBNEED_OPERATION
				}

				Model->Finalize();

				TestWorld->DestroyActor(Character);

				return true;
			});

			It("Given a skill update from the character, expect the model to update the related skill entry", [this, ModelClass]()
			{
				struct FBBSkillTestCase
				{
					public:
						FBBSkillTestCase(EBBSkill NewSkill, float NewValue, float NewMaxValue) :
							Skill(NewSkill),
							Value(NewValue),
							MaxValue(NewMaxValue)
						{};

						EBBSkill Skill = EBBSkill::Build;

						float Value = 0.0f;

						float MaxValue = 0.0f;
				};

				TArray<FBBSkillTestCase> TestCases;
				TestCases.Empty();
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Build, 15.12f, 348.89f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Build, -2285.43f, 127.06f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Build, 74.13f, -1215.18f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Build, 924.38f, 367.62f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Build, -423.72f, 145.8f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Fuck, 2374.8f, -167.33f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Fuck, 4.9f, 236.7f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Fuck, -298.44f, 18.9f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Fuck, 567.2f, -384.68f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Fuck, 721.88f, 2.3f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Guard, -764.3f, 21.71f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Guard, 394.38f, -8167.2f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Guard, 53.15f, 427.638f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Guard, -3485.9f, 312.8f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Guard, 734.2f, 5136.69f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Lead, 28.951f, 52.6f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Lead, -384.1f, 145.38f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Lead, 7.4f, -1493.7f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Lead, 52.7f, 2265.434f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Lead, -315.23f, 19.178f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Research, -672.3f, 47.8f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Research, 394.187f, -183.62f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Research, 53.21f, 472.94f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Research, -4238.7f, 152.62f));
				TestCases.Emplace(FBBSkillTestCase(EBBSkill::Research, 749.83f, 28.11f));

				Model = NewObject<UBBDossierModel>(TestWorld, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(SpawnParameters);

				UTEST_TRUE("Character is valid", IsValid(Character))

				UBBAIAbilityComponentStub * AbilityComponent = NewObject<UBBAIAbilityComponentStub>(Character, UBBAIAbilityComponentStub::StaticClass());

				UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))

				UBBAttributeSetStub * AttributeSet = NewObject<UBBAttributeSetStub>(Character, UBBAttributeSetStub::StaticClass());

				UTEST_TRUE("Derived Attribute Set is valid", IsValid(AttributeSet))
				
				UBBNeedSetStub * NeedSet = NewObject<UBBNeedSetStub>(Character, UBBNeedSetStub::StaticClass());

				UTEST_TRUE("Need Set is valid", IsValid(NeedSet))
				
				UBBSkillSetStub * SkillSet = NewObject<UBBSkillSetStub>(Character, UBBSkillSetStub::StaticClass());

				UTEST_TRUE("Skill Set is valid", IsValid(SkillSet))

				AbilityComponent->AddAttributeSet(AttributeSet);
				AbilityComponent->AddAttributeSet(NeedSet);
				AbilityComponent->AddAttributeSet(SkillSet);

				Character->SetAbilitySystemComponent(AbilityComponent);

				SkillSet->SetValue(EBBSkill::Build, 0.0f);
				SkillSet->SetValue(EBBSkill::Fuck, 0.0f);
				SkillSet->SetValue(EBBSkill::Guard, 0.0f);
				SkillSet->SetValue(EBBSkill::Lead, 0.0f);
				SkillSet->SetValue(EBBSkill::Research, 0.0f);
				SkillSet->SetMaxValue(EBBSkill::Build, 0.0f);
				SkillSet->SetMaxValue(EBBSkill::Fuck, 0.0f);
				SkillSet->SetMaxValue(EBBSkill::Guard, 0.0f);
				SkillSet->SetMaxValue(EBBSkill::Lead, 0.0f);
				SkillSet->SetMaxValue(EBBSkill::Research, 0.0f);

				Model->Initialize(View, Character);

				for (FBBSkillTestCase & TestCase : TestCases)
				{
					SkillSet->SetValue(TestCase.Skill, TestCase.Value);

					#define EBBSKILL_OPERATION(Value) TestEntry<EBBSkill, UIBBSkillSet, UIBBDossierEntry>(Value, Model, SkillSet);

						FOREACH_ENUM_EBBSKILL(EBBSKILL_OPERATION)

					#undef EBBSKILL_OPERATION
				}

				Model->Finalize();

				TestWorld->DestroyActor(Character);

				return true;
			});
		});
	}
}