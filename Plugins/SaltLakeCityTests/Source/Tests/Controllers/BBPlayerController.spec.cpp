// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/BBAbilityDataStub.h"
#include "Actors/Pawns/BBPawnStub.h"
#include "Actors/Components/BBPlayerAbilityComponentStub.h"
#include "Actors/Components/Factories/BBComponentFactoryStub.h"
#include "Controllers/BBPlayerController.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBPlayerControllerSpec,
	"SaltLakeCity.Controllers.PlayerController",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBComponentFactoryStub * ComponentFactory = nullptr;

	UPROPERTY()
	UBBPlayerAbilityComponentStub * PlayerAbilityComponent = nullptr;

	UPROPERTY()
	TArray<UClass *> ControllerClasses;

	// SUT
	UPROPERTY()
	ABBPlayerController * Controller = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBPlayerControllerSpec)

void UBBPlayerControllerSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBPlayerController>(FString(TEXT("/Game/Controllers")), ControllerClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		ComponentFactory = NewObject<UBBComponentFactoryStub>(GameInstance, UBBComponentFactoryStub::StaticClass());

		UTEST_TRUE("Component Factory is valid", IsValid(ComponentFactory))

		GameInstance->SetComponentFactory(ComponentFactory);

		PlayerAbilityComponent = NewObject<UBBPlayerAbilityComponentStub>(ComponentFactory, UBBPlayerAbilityComponentStub::StaticClass());
		
		UTEST_TRUE("Player Ability Component is valid", IsValid(PlayerAbilityComponent))

		ComponentFactory->AddPlayerAbilityComponent(PlayerAbilityComponent);

		return true;
	});

	AfterEach([this]()
	{
		TestWorld->DestroyActor(Controller);

		PlayerAbilityComponent = nullptr;

		ComponentFactory = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ControllerClass : ControllerClasses)
	{
		Describe("[" + ControllerClass->GetName() + "]", [this, ControllerClass]()
		{
			It("Given a new lerp request, expect the controller to lerp to the given height", [this, ControllerClass]()
			{
				Controller = TestWorld->SpawnActor<ABBPlayerController>(ControllerClass, SpawnParameters);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				ABBPawnStub * Pawn = TestWorld->SpawnActor<ABBPawnStub>(SpawnParameters);

				UTEST_TRUE("Pawn is valid", IsValid(Pawn))

				Controller->UnPossess();

				Controller->Possess(Pawn);

				TArray<float> Heights;
				Heights.Emplace(304.02f);
				Heights.Emplace(-231.63f);
				Heights.Emplace(86.75f);
				Heights.Emplace(-912.43f);
				Heights.Emplace(756.16f);

				for (float & Height : Heights)
				{ 
					Controller->LerpToHeight(Height);

					TEST_TRUE(Pawn->GetLerpTarget().Z == Height);
				}

				return true;
			});

			It("Given a new ability request, expect the controller to forward it to the ability component", [this, ControllerClass]()
			{
				Controller = TestWorld->SpawnActor<ABBPlayerController>(ControllerClass, SpawnParameters);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				TArray<UBBAbilityDataStub *> AbilitiesData;
				AbilitiesData.Emplace(NewObject<UBBAbilityDataStub>(Controller, UBBAbilityDataStub::StaticClass()));
				AbilitiesData.Emplace(NewObject<UBBAbilityDataStub>(Controller, UBBAbilityDataStub::StaticClass()));
				AbilitiesData.Emplace(NewObject<UBBAbilityDataStub>(Controller, UBBAbilityDataStub::StaticClass()));
				AbilitiesData.Emplace(NewObject<UBBAbilityDataStub>(Controller, UBBAbilityDataStub::StaticClass()));
				AbilitiesData.Emplace(NewObject<UBBAbilityDataStub>(Controller, UBBAbilityDataStub::StaticClass()));

				for (UBBAbilityDataStub * & AbilityData : AbilitiesData)
				{
					Controller->RequestAbility(AbilityData);

					TEST_TRUE(PlayerAbilityComponent->GetRequestedAbilityData() == AbilityData)
				}

				return true;
			});

			It("Given a new grid position request, expect the controller to return the grid position", [this, ControllerClass]()
			{
				Controller = TestWorld->SpawnActor<ABBPlayerController>(ControllerClass, SpawnParameters);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				return true;
			});

			It("Given a new ability target confirmation, expect the controller to confirm the ability's target", [this, ControllerClass]()
			{
				Controller = TestWorld->SpawnActor<ABBPlayerController>(ControllerClass, SpawnParameters);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				TEST_TRUE(PlayerAbilityComponent->GetNumTargetConfirmations() == 0)

				for (int Confirmations = 1; Confirmations < 6; Confirmations++)
				{
					Controller->ConfirmTarget();

					TEST_TRUE(PlayerAbilityComponent->GetNumTargetConfirmations() == Confirmations)
				}

				return true;
			});

			It("Given a new ability target cancellation, expect the controller to cancel the ability's target", [this, ControllerClass]()
			{
				Controller = TestWorld->SpawnActor<ABBPlayerController>(ControllerClass, SpawnParameters);

				UTEST_TRUE("Controller is valid", IsValid(Controller))

				TEST_TRUE(PlayerAbilityComponent->GetNumTargetCancellations() == 0)

				for (int Cancellations = 1; Cancellations < 6; Cancellations++)
				{
					Controller->CancelTarget();

					TEST_TRUE(PlayerAbilityComponent->GetNumTargetCancellations() == Cancellations)
				}

				return true;
			});
		});
	}
}