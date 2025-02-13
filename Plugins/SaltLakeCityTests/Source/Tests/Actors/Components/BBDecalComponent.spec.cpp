// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "Actors/Components/BBDecalComponent.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/BBHUDStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBDecalComponentSpec, "SaltLakeCity.Actors.Components.DecalComponent", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBCharacterStub * Character;

	UPROPERTY()
	TArray<UClass *> ComponentClasses;

	// SUT
	UPROPERTY()
	UBBDecalComponent * DecalComponent = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBDecalComponentSpec)

void UBBDecalComponentSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDecalComponent>(FString(TEXT("/Game/Actors/Components")), ComponentClasses);
	
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

		return true;
	});

	AfterEach([this]()
	{
		DecalComponent = nullptr;

		TestWorld->DestroyActor(Character);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ComponentClass : ComponentClasses)
	{
		Describe("[" + ComponentClass->GetName() + "]", [this, ComponentClass]()
		{
			It("Given initialization, expect the decal component to attach a new decal material", [this, ComponentClass]()
			{
				DecalComponent = NewObject<UBBDecalComponent>(Character, ComponentClass);

				UTEST_TRUE("Decal Component is valid", IsValid(DecalComponent))

				Character->AddOwnedComponent(DecalComponent);
				DecalComponent->RegisterComponent();

				DecalComponent->Initialize(TScriptInterface<IBBHighlightable>(Character));

				TEST_TRUE(IsValid(DecalComponent->GetDecalMaterial()))

				DecalComponent->Finalize();

				return true;
			});

			It("Given finalization, expect the decal component to detach its decal material", [this, ComponentClass]()
			{
				DecalComponent = NewObject<UBBDecalComponent>(Character, ComponentClass);

				UTEST_TRUE("Decal Component is valid", IsValid(DecalComponent))

				Character->AddOwnedComponent(DecalComponent);
				DecalComponent->RegisterComponent();

				DecalComponent->Initialize(TScriptInterface<IBBHighlightable>(Character));

				DecalComponent->Finalize();

				TEST_FALSE(IsValid(DecalComponent->GetDecalMaterial()))

				return true;
			});

			It("Given a selection update, expect the decal component to become visible", [this, ComponentClass]()
			{
				DecalComponent = NewObject<UBBDecalComponent>(Character, ComponentClass);

				UTEST_TRUE("Decal Component is valid", IsValid(DecalComponent))

				Character->AddOwnedComponent(DecalComponent);
				DecalComponent->RegisterComponent();

				DecalComponent->Initialize(TScriptInterface<IBBHighlightable>(Character));

				Character->UpdateSelection(true);

				TEST_TRUE(DecalComponent->IsVisible())
				
				Character->UpdateSelection(false);

				DecalComponent->Finalize();

				return true;
			});

			It("Given a deselection update, expect the decal component to become not visible", [this, ComponentClass]()
			{
				DecalComponent = NewObject<UBBDecalComponent>(Character, ComponentClass);

				UTEST_TRUE("Decal Component is valid", IsValid(DecalComponent))

				Character->AddOwnedComponent(DecalComponent);
				DecalComponent->RegisterComponent();

				DecalComponent->Initialize(TScriptInterface<IBBHighlightable>(Character));

				Character->UpdateSelection(true);

				Character->UpdateSelection(false);

				TEST_FALSE(DecalComponent->IsVisible())

				DecalComponent->Finalize();

				return true;
			});
		});
	}
}