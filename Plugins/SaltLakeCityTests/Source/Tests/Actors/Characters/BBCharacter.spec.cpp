// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/BBBuildTaskStub.h"
#include "Actors/Characters/BBCharacter.h"
#include "Actors/Components/Factories/BBComponentFactoryStub.h"
#include "Actors/Components/BBContextComponentStub.h"
#include "Actors/Components/BBDecalComponentStub.h"
#include "Actors/Components/BBSelectionComponentStub.h"
#include "Actors/Components/BBWorkComponentStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameStates/BBGameStateStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBCharacterSpec,
	"SaltLakeCity.Actors.Characters.Character",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBGameStateStub * GameState = nullptr;

	UPROPERTY()
	UBBComponentFactoryStub * ComponentFactory = nullptr;

	UPROPERTY()
	UBBContextComponentStub * ContextComponent = nullptr;

	UPROPERTY()
	UBBDecalComponentStub * DecalComponent = nullptr;

	UPROPERTY()
	UBBSelectionComponentStub * SelectionComponent = nullptr;

	UPROPERTY()
	UBBWorkComponentStub * WorkComponent = nullptr;

	UPROPERTY()
	TArray<UClass *> CharacterClasses;

	// SUT
	UPROPERTY()
	ABBCharacter * Character = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBCharacterSpec)

void UBBCharacterSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBCharacter>(FString(TEXT("/Game/Actors/Characters")), CharacterClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		GameState = TestWorld->GetGameState<ABBGameStateStub>();

		UTEST_TRUE("Game State is valid", IsValid(GameState))

		ComponentFactory = NewObject<UBBComponentFactoryStub>(TestWorld, UBBComponentFactoryStub::StaticClass());

		UTEST_TRUE("Component Factory is valid", IsValid(ComponentFactory))

		ContextComponent = NewObject<UBBContextComponentStub>(ComponentFactory, UBBContextComponentStub::StaticClass());
		UTEST_TRUE("Context Component is valid", IsValid(ContextComponent))
		DecalComponent = NewObject<UBBDecalComponentStub>(ComponentFactory, UBBDecalComponentStub::StaticClass());
		UTEST_TRUE("Decal Component is valid", IsValid(DecalComponent))
		SelectionComponent = NewObject<UBBSelectionComponentStub>(ComponentFactory, UBBSelectionComponentStub::StaticClass());
		UTEST_TRUE("Selection Component is valid", IsValid(SelectionComponent))
		WorkComponent = NewObject<UBBWorkComponentStub>(ComponentFactory, UBBWorkComponentStub::StaticClass());
		UTEST_TRUE("Work Component is valid", IsValid(WorkComponent))

		ComponentFactory->AddContextComponent(ContextComponent);
		ComponentFactory->AddDecalComponent(DecalComponent);
		ComponentFactory->AddSelectionComponent(SelectionComponent);
		ComponentFactory->AddWorkComponent(WorkComponent);

		GameInstance->SetComponentFactory(ComponentFactory);

		return true;
	});

	AfterEach([this]()
	{
		TestWorld->DestroyActor(Character);

		WorkComponent = nullptr;
		SelectionComponent = nullptr;
		DecalComponent = nullptr;
		ContextComponent = nullptr;

		ComponentFactory = nullptr;
		GameState = nullptr;
		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & CharacterClass : CharacterClasses)
	{
		Describe("[" + CharacterClass->GetName() + "]", [this, CharacterClass]()
		{
			It("Given a new first name, expect the character to update its first name and its full name", [this, CharacterClass]()
			{
				Character = TestWorld->SpawnActor<ABBCharacter>(CharacterClass, SpawnParameters);

				UTEST_TRUE("Character is valid", IsValid(Character))

				TArray<FText> Names;
				Names.Emplace(FText::FromString("SomeName"));
				Names.Emplace(FText::FromString("Bob"));
				Names.Emplace(FText::FromString("Sp1d3rm4n"));
				Names.Emplace(FText::FromString("%)HQRHG?)%"));
				Names.Emplace(FText::FromString("___"));

				Character->SetFirstName(FText::FromString(""));
				Character->SetCodeName(FText::FromString(""));
				Character->SetLastName(FText::FromString(""));

				for (FText & Name : Names)
				{
					Character->SetFirstName(Name);

					TEST_TRUE(Character->GetDisplayName(EBBDisplayName::Short).EqualTo(Name))

					TEST_TRUE(Character->GetDisplayName(EBBDisplayName::Full).ToString().TrimStartAndEnd().Equals(Name.ToString()))
				}

				return true;
			});

			It("Given a new code name, expect the character to update its code name and its full name", [this, CharacterClass]()
			{
				Character = TestWorld->SpawnActor<ABBCharacter>(CharacterClass, SpawnParameters);

				UTEST_TRUE("Character is valid", IsValid(Character))

				TArray<FText> Names;
				Names.Emplace(FText::FromString("Code"));
				Names.Emplace(FText::FromString("RedCobra"));
				Names.Emplace(FText::FromString("Agent 52"));
				Names.Emplace(FText::FromString("6280gb!"));
				Names.Emplace(FText::FromString(" - _ -_1"));

				Character->SetFirstName(FText::FromString(""));
				Character->SetCodeName(FText::FromString(""));
				Character->SetLastName(FText::FromString(""));

				for (FText & Name : Names)
				{
					Character->SetCodeName(Name);

					TEST_TRUE(Character->GetDisplayName(EBBDisplayName::Code).EqualTo(Name))

					FString TrimmedName = Character->GetDisplayName(EBBDisplayName::Full).ToString().TrimStartAndEnd().Replace(TEXT("\""), TEXT(""));
					TEST_TRUE(TrimmedName.Equals(Name.ToString()))
				}

				return true;
			});

			It("Given a new last name, expect the character to update its last name and its full name", [this, CharacterClass]()
			{
				Character = TestWorld->SpawnActor<ABBCharacter>(CharacterClass, SpawnParameters);

				UTEST_TRUE("Character is valid", IsValid(Character))

				TArray<FText> Names;
				Names.Emplace(FText::FromString("Characterson"));
				Names.Emplace(FText::FromString("LastLast"));
				Names.Emplace(FText::FromString("of Rivia"));
				Names.Emplace(FText::FromString("6?&H GH%B!"));
				Names.Emplace(FText::FromString("--1_1-!32"));

				Character->SetFirstName(FText::FromString(""));
				Character->SetCodeName(FText::FromString(""));
				Character->SetLastName(FText::FromString(""));

				for (FText & Name : Names)
				{
					Character->SetLastName(Name);

					TEST_TRUE(Character->GetDisplayName(EBBDisplayName::Long).EqualTo(Name))

					TEST_TRUE(Character->GetDisplayName(EBBDisplayName::Full).ToString().TrimStartAndEnd().Equals(Name.ToString()))
				}

				return true;
			});

			It("Given a new selection request, expect the character to display its selection decal", [this, CharacterClass]()
			{
				Character = TestWorld->SpawnActor<ABBCharacter>(CharacterClass, SpawnParameters);

				UTEST_TRUE("Character is valid", IsValid(Character))

				for (int Selections = 0; Selections < 6; Selections++)
				{
					Character->UpdateSelection(true);

					TEST_TRUE(DecalComponent->IsVisible())

					Character->UpdateSelection(false);
				}

				return true;
			});

			It("Given a new deselection request, expect the character to hide its selection decal", [this, CharacterClass]()
			{
				Character = TestWorld->SpawnActor<ABBCharacter>(CharacterClass, SpawnParameters);

				UTEST_TRUE("Character is valid", IsValid(Character))

				for (int Selections = 0; Selections < 6; Selections++)
				{
					Character->UpdateSelection(true);
					Character->UpdateSelection(false);

					TEST_FALSE(DecalComponent->IsVisible())
				}

				return true;
			});
		});
	}
}