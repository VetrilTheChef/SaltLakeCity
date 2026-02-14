// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Actors/Buildings/BBBuilding.h"
#include "Actors/Components/BBProgressComponentStub.h"
#include "Actors/Components/BBSelectionComponentStub.h"
#include "Actors/Components/Factories/BBComponentFactoryStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBBuildingSpec,
	"SaltLakeCity.Actors.Buildings.Building",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UMaterialInterface *> MaterialOverrides;

	UPROPERTY()
	UBBComponentFactoryStub * ComponentFactory = nullptr;

	UPROPERTY()
	TArray<UClass *> BuildingClasses;

	// SUT
	UPROPERTY()
	ABBBuilding * Building = nullptr;
	
	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBBuildingSpec)

void UBBBuildingSpec::Define()
{
	UBBTestUtil::GetTestClasses<ABBBuilding>(FString(TEXT("/Game/Actors/Buildings")), BuildingClasses);

	UBBTestUtil::GetTestAssets<UMaterialInterface>(FString(TEXT("/SaltLakeCityTests/Materials/Overrides")), MaterialOverrides);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		ComponentFactory = NewObject<UBBComponentFactoryStub>(TestWorld, UBBComponentFactoryStub::StaticClass());

		UTEST_TRUE("Component Factory is valid", IsValid(ComponentFactory))
		
		ComponentFactory->AddSelectionComponent(NewObject<UBBSelectionComponentStub>(ComponentFactory, UBBSelectionComponentStub::StaticClass()));
		ComponentFactory->AddProgressComponent(NewObject<UBBProgressComponentStub>(ComponentFactory, UBBProgressComponentStub::StaticClass()));
		
		GameInstance->SetComponentFactory(ComponentFactory);

		return true;
	});

	AfterEach([this]()
	{
		TestWorld->DestroyActor(Building);

		ComponentFactory = nullptr;
		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & BuildingClass : BuildingClasses)
	{
		Describe("[" + BuildingClass->GetName() + "]", [this, BuildingClass]()
		{
			It("Given a new price, expect the building to apply it", [this, BuildingClass]()
			{
				Building = TestWorld->SpawnActor<ABBBuilding>(BuildingClass, SpawnParameters);

				UTEST_TRUE("Building is valid", IsValid(Building))
					
				TArray<float> Prices;
				Prices.Emplace(25.51f);
				Prices.Emplace(-6.13f);
				Prices.Emplace(0.0f);
				Prices.Emplace(814.611f);
				Prices.Emplace(-7815.0f);

				for (float & Price : Prices)
				{
					Building->SetPrice(Price);

					TEST_TRUE(Building->GetPrice() == Price);
				}

				return true;
			});

			It("Given a new build time, expect the building to apply it", [this, BuildingClass]()
			{
				Building = TestWorld->SpawnActor<ABBBuilding>(BuildingClass, SpawnParameters);

				UTEST_TRUE("Building is valid", IsValid(Building))

				TArray<float> BuildTimes;
				BuildTimes.Emplace(734.12f);
				BuildTimes.Emplace(0.01f);
				BuildTimes.Emplace(-53.2f);
				BuildTimes.Emplace(326.1f);
				BuildTimes.Emplace(-651.662f);

				for (float & BuildTime : BuildTimes)
				{
					Building->SetBuildTime(BuildTime);

					TEST_TRUE(Building->GetBuildTime() == BuildTime);
				}

				return true;
			});

			It("Given a new progress, expect the building to apply it", [this, BuildingClass]()
			{
				Building = TestWorld->SpawnActor<ABBBuilding>(BuildingClass, SpawnParameters);

				UTEST_TRUE("Building is valid", IsValid(Building))

				TArray<float> Progresses;
				Progresses.Emplace(61.256f);
				Progresses.Emplace(-81.2f);
				Progresses.Emplace(52.16f);
				Progresses.Emplace(743.1f);
				Progresses.Emplace(-236.92f);

				for (float & Progress : Progresses)
				{
					Building->SetProgress(Progress);

					TEST_TRUE(Building->GetProgress() == Progress);
				}

				return true;
			});

			It("Given a new material override, expect the building to apply it", [this, BuildingClass]()
			{
				Building = TestWorld->SpawnActor<ABBBuilding>(BuildingClass, SpawnParameters);

				UTEST_TRUE("Building is valid", IsValid(Building))

				for (UMaterialInterface * & MaterialOverride : MaterialOverrides)
				{
					Building->AddMaterialOverride(MaterialOverride);

					UStaticMeshComponent * Mesh = Building->GetStaticMeshComponent();

					for (int i = 0; i < Mesh->GetNumMaterials(); i++)
					{
						TEST_TRUE(Mesh->GetMaterial(i) == MaterialOverride);
					}

					Building->RemoveMaterialOverride();
				}

				return true;
			});

			It("Given a material override to remove, expect the building to remove it", [this, BuildingClass]()
			{
				Building = TestWorld->SpawnActor<ABBBuilding>(BuildingClass, SpawnParameters);

				UTEST_TRUE("Building is valid", IsValid(Building))

				for (UMaterialInterface * & MaterialOverride : MaterialOverrides)
				{
					Building->AddMaterialOverride(MaterialOverride);

					UStaticMeshComponent * Mesh = Building->GetStaticMeshComponent();

					for (int i = 0; i < Mesh->GetNumMaterials(); i++)
					{
						TEST_TRUE(Mesh->GetMaterial(i) == MaterialOverride);
					}

					Building->RemoveMaterialOverride();

					for (int i = 0; i < Mesh->GetNumMaterials(); i++)
					{
						TEST_TRUE(Mesh->GetMaterial(i) != MaterialOverride);
					}
				}

				return true;
			});
		});
	}
}