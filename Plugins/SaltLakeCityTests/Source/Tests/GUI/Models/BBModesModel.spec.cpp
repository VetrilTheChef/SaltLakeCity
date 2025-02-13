// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/Factories/BBCommandFactoryStub.h"
#include "Commands/GameModes/BBGameModeCommandStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameModes/BBGameModeStub.h"
#include "GUI/Controllers/BBModesControllerStub.h"
#include "GUI/Models/BBModesModel.h"
#include "GUI/Widgets/BBModesWidgetStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBModesModelSpec, "SaltLakeCity.GUI.Models.Modes", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBGameModeStub * GameMode = nullptr;

	UPROPERTY()
	UBBCommandFactoryStub * CommandFactory = nullptr;

	UPROPERTY()
	UBBModesWidgetStub * View = nullptr;

	UPROPERTY()
	UBBModesControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<UClass *> ModelClasses;

	// SUT
	UPROPERTY()
	UBBModesModel * Model = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBModesModelSpec)

void UBBModesModelSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBModesModel>(FString(TEXT("/Game/GUI/Models")), ModelClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		GameMode = TestWorld->SpawnActor<ABBGameModeStub>(ABBGameModeStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Game Mode is valid.", IsValid(GameMode))

		View = CreateWidget<UBBModesWidgetStub>(TestWorld, UBBModesWidgetStub::StaticClass());

		UTEST_TRUE("View is valid", IsValid(View))

		View->NativeOnInitialized();

		Controller = NewObject<UBBModesControllerStub>(TestWorld, UBBModesControllerStub::StaticClass());

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		return true;
	});

	AfterEach([this]()
	{
		TestWorld->DestroyActor(GameMode);

		Controller = nullptr;

		View = nullptr;

		Model = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ModelClass : ModelClasses)
	{
		Describe("[" + ModelClass->GetName() + "]", [this, ModelClass]()
		{
			It("Given a new game mode update, expect the model to update the controller", [this, ModelClass]()
			{
				Model = NewObject<UBBModesModel>(Controller, ModelClass);

				UTEST_TRUE("Model is valid", IsValid(Model))

				Model->Initialize(View, GameMode);

				Controller->Initialize(View, Model, CommandFactory);

				TArray<EBBGameMode> ActiveGameModes;
				ActiveGameModes.Emplace(EBBGameMode::Build);
				ActiveGameModes.Emplace(EBBGameMode::Play);
				ActiveGameModes.Emplace(EBBGameMode::None);
				ActiveGameModes.Emplace(EBBGameMode::Build);
				ActiveGameModes.Emplace(EBBGameMode::Play);

				for (EBBGameMode & ActiveGameMode : ActiveGameModes)
				{
					GameMode->OnActiveModeUpdate().Broadcast(ActiveGameMode);

					TEST_TRUE(Controller->GetActiveGameMode() == ActiveGameMode)
				}

				Controller->Finalize();

				Model->Finalize();

				return true;
			});
		});
	}
}