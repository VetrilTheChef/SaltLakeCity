// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/BBAIAbilityComponent.h"
#include "Attributes/BBAttributeSetStub.h"
#include "Attributes/BBNeedSetStub.h"
#include "Attributes/BBSkillSetStub.h"
#include "Controllers/BBAIControllerStub.h"
#include "Engine/DataTable.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBAIAbilityComponentSpec, "SaltLakeCity.Actors.Components.AIAbilityComponent", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBAIControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<UDataTable *> NeedsDataTables;

	UPROPERTY()
	TArray<UDataTable *> SkillsDataTables;

	UPROPERTY()
	TArray<UDataTable *> AttributesDataTables;

	UPROPERTY()
	TArray<UClass *> ComponentClasses;

	// SUT
	UPROPERTY()
	UBBAIAbilityComponent * AbilityComponent = nullptr;

	FActorSpawnParameters SpawnParameters;

	template<typename E, class T>
	void TestAttributeInitialization(E AttributeEnum, FString & Context, FString AttributeSetName, UDataTable & DataTable, const T & AttributeSet)
	{
		FString EnumName = UEnum::GetValueAsString(AttributeEnum);

		int32 ScopeIndex = EnumName.Find(TEXT("::"), ESearchCase::CaseSensitive);

		if (ScopeIndex != INDEX_NONE)
		{
			EnumName = EnumName.Mid(ScopeIndex + 2);
		}

		FName RowName(AttributeSetName + TEXT(".") + EnumName);
		FName MaxRowName(AttributeSetName + TEXT(".Max") + EnumName);

		FAttributeMetaData * Row = DataTable.FindRow<FAttributeMetaData>(RowName, Context, false);
		FAttributeMetaData * MaxRow = DataTable.FindRow<FAttributeMetaData>(MaxRowName, Context, false);

		TEST_TRUE(Row != nullptr);
		TEST_TRUE(MaxRow != nullptr);

		TEST_TRUE(AttributeSet.GetValue(AttributeEnum) == Row->BaseValue);
		TEST_TRUE(AttributeSet.GetMaxValue(AttributeEnum) == MaxRow->BaseValue);
	};

END_DEFINE_SPEC(UBBAIAbilityComponentSpec)

void UBBAIAbilityComponentSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBAIAbilityComponent>(FString(TEXT("/Game/Actors/Components")), ComponentClasses);

	UBBTestUtil::GetTestAssets<UDataTable>(FString(TEXT("/SaltLakeCityTests/Attributes/Data/Characters/Needs")), NeedsDataTables);
	UBBTestUtil::GetTestAssets<UDataTable>(FString(TEXT("/SaltLakeCityTests/Attributes/Data/Characters/Skills")), SkillsDataTables);
	UBBTestUtil::GetTestAssets<UDataTable>(FString(TEXT("/SaltLakeCityTests/Attributes/Data/Characters/Attributes")), AttributesDataTables);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Controller = TestWorld->SpawnActor<ABBAIControllerStub>(ABBAIControllerStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		return true;
	});

	AfterEach([this]()
	{
		AbilityComponent = nullptr;

		TestWorld->DestroyActor(Controller);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ComponentClass : ComponentClasses)
	{
		Describe("[" + ComponentClass->GetName() + "]", [this, ComponentClass]()
		{
			It("Given initialization, expect the AI ability component to create its attribute sets", [this, ComponentClass]()
			{
				FString Context = FString(TEXT("UBBAIAbilityComponentSpec"));

				AbilityComponent = NewObject<UBBAIAbilityComponent>(Controller, ComponentClass);

				UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))

				Controller->AddOwnedComponent(AbilityComponent);
				AbilityComponent->RegisterComponent();

				for (UDataTable * & NeedsDataTable : NeedsDataTables)
				{
					for (UDataTable * & SkillsDataTable : SkillsDataTables)
					{
						for (UDataTable * & AttributesDataTable : AttributesDataTables)
						{
							TArray<FBBAttributeSetData> SetsData;
							SetsData.Emplace(FBBAttributeSetData(TSoftClassPtr<UIBBAttributeSet>(UBBNeedSetStub::StaticClass()), TSoftObjectPtr<UDataTable>(NeedsDataTable)));
							SetsData.Emplace(FBBAttributeSetData(TSoftClassPtr<UIBBAttributeSet>(UBBSkillSetStub::StaticClass()), TSoftObjectPtr<UDataTable>(SkillsDataTable)));
							SetsData.Emplace(FBBAttributeSetData(TSoftClassPtr<UIBBAttributeSet>(UBBAttributeSetStub::StaticClass()), TSoftObjectPtr<UDataTable>(AttributesDataTable)));

							AbilityComponent->Initialize(Controller, SetsData);

							const UIBBNeedSet * NeedsSet = AbilityComponent->GetSet<UIBBNeedSet>();

							UTEST_TRUE("Needs Set is valid", IsValid(NeedsSet))

							const UIBBSkillSet * SkillsSet = AbilityComponent->GetSet<UIBBSkillSet>();

							UTEST_TRUE("Skills Set is valid", IsValid(SkillsSet))

							const UIBBAttributeSet * AttributesSet = AbilityComponent->GetSet<UIBBAttributeSet>();

							UTEST_TRUE("Derived Attributes Set is valid", IsValid(AttributesSet))

							#define EBBNEED_OPERATION(Value) TestAttributeInitialization<EBBNeed, UIBBNeedSet>(Value, Context, TEXT("BBNeedSetStub"), * NeedsDataTable, * NeedsSet);

								FOREACH_ENUM_EBBNEED(EBBNEED_OPERATION)

							#undef EBBNEED_OPERATION

							#define EBBSKILL_OPERATION(Value) TestAttributeInitialization<EBBSkill, UIBBSkillSet>(Value, Context, TEXT("BBSkillSetStub"), * SkillsDataTable, * SkillsSet);

								FOREACH_ENUM_EBBSKILL(EBBSKILL_OPERATION)

							#undef EBBSKILL_OPERATION

							#define EBBATTRIBUTE_OPERATION(Value) TestAttributeInitialization<EBBAttribute, UIBBAttributeSet>(Value, Context, TEXT("BBAttributeSetStub"), * AttributesDataTable, * AttributesSet);

								FOREACH_ENUM_EBBATTRIBUTE(EBBATTRIBUTE_OPERATION)

							#undef EBBATTRIBUTE_OPERATION

							AbilityComponent->Finalize();
						}
					}
				}

				return true;
			});

			It("Given finalization, expect the AI ability component to destroy its attribute sets", [this, ComponentClass]()
			{
				FString Context = FString(TEXT("UBBAIAbilityComponentSpec"));

				AbilityComponent = NewObject<UBBAIAbilityComponent>(Controller, ComponentClass);

				UTEST_TRUE("Ability Component is valid", IsValid(AbilityComponent))

				Controller->AddOwnedComponent(AbilityComponent);
				AbilityComponent->RegisterComponent();

				for (UDataTable * & NeedsDataTable : NeedsDataTables)
				{
					for (UDataTable * & SkillsDataTable : SkillsDataTables)
					{
						for (UDataTable * & AttributesDataTable : AttributesDataTables)
						{
							TArray<FBBAttributeSetData> SetsData;
							SetsData.Emplace(FBBAttributeSetData(TSoftClassPtr<UIBBAttributeSet>(UBBNeedSetStub::StaticClass()), TSoftObjectPtr<UDataTable>(NeedsDataTable)));
							SetsData.Emplace(FBBAttributeSetData(TSoftClassPtr<UIBBAttributeSet>(UBBSkillSetStub::StaticClass()), TSoftObjectPtr<UDataTable>(SkillsDataTable)));
							SetsData.Emplace(FBBAttributeSetData(TSoftClassPtr<UIBBAttributeSet>(UBBAttributeSetStub::StaticClass()), TSoftObjectPtr<UDataTable>(AttributesDataTable)));

							AbilityComponent->Initialize(Controller, SetsData);

							const UIBBNeedSet * NeedsSet = AbilityComponent->GetSet<UIBBNeedSet>();
							const UIBBSkillSet * SkillsSet = AbilityComponent->GetSet<UIBBSkillSet>();
							const UIBBAttributeSet * AttributesSet = AbilityComponent->GetSet<UIBBAttributeSet>();

							TEST_TRUE(IsValid(NeedsSet))
							TEST_TRUE(IsValid(SkillsSet))
							TEST_TRUE(IsValid(AttributesSet))

							AbilityComponent->Finalize();
							
							NeedsSet = AbilityComponent->GetSet<UIBBNeedSet>();
							SkillsSet = AbilityComponent->GetSet<UIBBSkillSet>();
							AttributesSet = AbilityComponent->GetSet<UIBBAttributeSet>();

							TEST_FALSE(IsValid(NeedsSet))
							TEST_FALSE(IsValid(SkillsSet))
							TEST_FALSE(IsValid(AttributesSet))
						}
					}
				}

				return true;
			});
		});
	}
}