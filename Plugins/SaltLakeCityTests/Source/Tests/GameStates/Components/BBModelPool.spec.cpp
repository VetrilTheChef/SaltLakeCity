// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/BBCharacterStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GUI/Components/BBModelPool.h"
#include "GUI/Models/BBBuildEntryModelStub.h"
#include "GUI/Models/BBBuildModelStub.h"
#include "GUI/Models/BBContextModelStub.h"
#include "GUI/Models/BBDateTimeModelStub.h"
#include "GUI/Models/BBDossierModelStub.h"
#include "GUI/Models/BBJobModelStub.h"
#include "GUI/Models/BBModesModelStub.h"
#include "GUI/Models/BBProgressModelStub.h"
#include "GUI/Models/BBSelectionModelStub.h"
#include "GUI/Models/BBTitleModelStub.h"
#include "GUI/Widgets/BBWidgetStub.h"
#include "Specifications/GUI/BBWidgetSpecificationStub.h"
#include "Tests/BBTestUtil.h"

class UBBModelPool;

BEGIN_DEFINE_SPEC(UBBModelPoolSpec, "SaltLakeCity.Game States.Components.ModelPool", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> ModelPoolClasses;

	// SUT
	UPROPERTY()
	UBBModelPool * ModelPool = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBModelPoolSpec)

void UBBModelPoolSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBModelPool>(FString(TEXT("/Game/GUI/Components/ModelPools")), ModelPoolClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		return true;
	});

	AfterEach([this]()
	{
		ModelPool = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});
	for (UClass * & ModelPoolClass : ModelPoolClasses)
	{
		Describe("[" + ModelPoolClass->GetName() + "]", [this, ModelPoolClass]()
		{
			It("Given a specification of a model which is not available, expect the model pool to return null", [this, ModelPoolClass]()
			{
				ModelPool = NewObject<UBBModelPool>(TestWorld, ModelPoolClass);

				UTEST_TRUE("Model Pool is valid.", IsValid(ModelPool))

				UBBWidgetSpecificationStub * Specification = NewObject<UBBWidgetSpecificationStub>(TestWorld, UBBWidgetSpecificationStub::StaticClass());

				UTEST_TRUE("Specification is valid.", IsValid(Specification))

				ABBCharacterStub * Character1 = TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters);
				ABBCharacterStub * Character2 = TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters);

				UTEST_TRUE("Character 1 is valid.", IsValid(Character1))
				UTEST_TRUE("Character 2 is valid.", IsValid(Character2))

				UBBWidgetStub * Widget = CreateWidget<UBBWidgetStub>(TestWorld, UBBWidgetStub::StaticClass());

				UTEST_TRUE("Widget is valid.", IsValid(Widget))

				UBBDossierModelStub * DossierModel = NewObject<UBBDossierModelStub>(TestWorld, UBBDossierModelStub::StaticClass());
				UTEST_TRUE("Dossier Model is valid.", IsValid(DossierModel))
				DossierModel->SetWidgetTarget(TScriptInterface<IBBWidgetTarget>(Character2));
				ModelPool->AddDossierModel(DossierModel);

				UBBJobModelStub * JobModel = NewObject<UBBJobModelStub>(TestWorld, UBBJobModelStub::StaticClass());
				UTEST_TRUE("Job Model is valid.", IsValid(JobModel))
				JobModel->SetWidgetTarget(TScriptInterface<IBBWidgetTarget>(Character2));
				ModelPool->AddJobModel(JobModel);

				UBBTitleModelStub * TitleModel = NewObject<UBBTitleModelStub>(TestWorld, UBBTitleModelStub::StaticClass());
				UTEST_TRUE("Title Model is valid.", IsValid(TitleModel))
				TitleModel->SetWidgetTarget(TScriptInterface<IBBWidgetTarget>(Widget));
				ModelPool->AddTitleModel(TitleModel);

				Specification->SetEvaluation(false);

				UIBBGUIModel * Model = nullptr;

				for (int Requests = 0; Requests < 5; Requests++)
				{
					Model = ModelPool->GetModel(* Specification);

					TEST_TRUE(Model == nullptr);
				}

				TestWorld->DestroyActor(Character1);
				TestWorld->DestroyActor(Character2);

				return true;
			});

			It("Given a specification of a model which is available, expect the model pool to return the model", [this, ModelPoolClass]()
			{
				ModelPool = NewObject<UBBModelPool>(TestWorld, ModelPoolClass);

				UTEST_TRUE("Model Pool is valid.", IsValid(ModelPool))

				UBBWidgetSpecificationStub * Specification = NewObject<UBBWidgetSpecificationStub>(TestWorld, UBBWidgetSpecificationStub::StaticClass());

				UTEST_TRUE("Specification is valid.", IsValid(Specification))

				ABBCharacterStub * Character = TestWorld->SpawnActor<ABBCharacterStub>(ABBCharacterStub::StaticClass(), SpawnParameters);

				UTEST_TRUE("Character is valid.", IsValid(Character))

				UBBWidgetStub * Widget = CreateWidget<UBBWidgetStub>(TestWorld, UBBWidgetStub::StaticClass());

				UTEST_TRUE("Widget is valid.", IsValid(Widget))

				UBBBuildEntryModelStub * BuildEntryModel = NewObject<UBBBuildEntryModelStub>(TestWorld, UBBBuildEntryModelStub::StaticClass());
				UTEST_TRUE("Build Entry Model is valid.", IsValid(BuildEntryModel))
				ModelPool->AddBuildEntryModel(BuildEntryModel);

				UBBBuildModelStub * BuildModel = NewObject<UBBBuildModelStub>(TestWorld, UBBBuildModelStub::StaticClass());
				UTEST_TRUE("Build Model is valid.", IsValid(BuildModel))
				ModelPool->AddBuildModel(BuildModel);

				UBBContextModelStub * ContextModel = NewObject<UBBContextModelStub>(TestWorld, UBBContextModelStub::StaticClass());
				UTEST_TRUE("Context Model is valid.", IsValid(ContextModel))
				ModelPool->AddContextModel(ContextModel);

				UBBDateTimeModelStub * DateTimeModel = NewObject<UBBDateTimeModelStub>(TestWorld, UBBDateTimeModelStub::StaticClass());
				UTEST_TRUE("Date Time Model is valid.", IsValid(DateTimeModel))
				ModelPool->AddDateTimeModel(NewObject<UBBDateTimeModelStub>(TestWorld, UBBDateTimeModelStub::StaticClass()));

				UBBDossierModelStub * DossierModel = NewObject<UBBDossierModelStub>(TestWorld, UBBDossierModelStub::StaticClass());
				UTEST_TRUE("Dossier Model is valid.", IsValid(DossierModel))
				DossierModel->SetWidgetTarget(TScriptInterface<IBBWidgetTarget>(Character));
				ModelPool->AddDossierModel(DossierModel);

				UBBJobModelStub * JobModel = NewObject<UBBJobModelStub>(TestWorld, UBBDossierModelStub::StaticClass());
				UTEST_TRUE("Job Model is valid.", IsValid(JobModel))
				JobModel->SetWidgetTarget(TScriptInterface<IBBWidgetTarget>(Character));
				ModelPool->AddJobModel(JobModel);

				UBBModesModelStub * ModesModel = NewObject<UBBModesModelStub>(TestWorld, UBBModesModelStub::StaticClass());
				UTEST_TRUE("Modes Model is valid.", IsValid(ModesModel))
				ModelPool->AddModesModel(ModesModel);

				UBBProgressModelStub * ProgressModel = NewObject<UBBProgressModelStub>(TestWorld, UBBProgressModelStub::StaticClass());
				UTEST_TRUE("Progress Model is valid.", IsValid(ProgressModel))
				ModelPool->AddProgressModel(ProgressModel);

				UBBSelectionModelStub * SelectionModel = NewObject<UBBSelectionModelStub>(TestWorld, UBBSelectionModelStub::StaticClass());
				UTEST_TRUE("Selection Model is valid.", IsValid(SelectionModel))
				ModelPool->AddSelectionModel(SelectionModel);

				UBBTitleModelStub * TitleModel = NewObject<UBBTitleModelStub>(TestWorld, UBBTitleModelStub::StaticClass());
				UTEST_TRUE("Title Model is valid.", IsValid(TitleModel))
				TitleModel->SetWidgetTarget(TScriptInterface<IBBWidgetTarget>(Widget));
				ModelPool->AddTitleModel(TitleModel);

				UIBBGUIModel * Model = nullptr;

				// ---

				Specification->SetEvaluation(true, BuildModel);

				Model = ModelPool->GetModel(* Specification);

				TEST_TRUE(Model == BuildModel);

				// ---

				Specification->SetEvaluation(true, BuildEntryModel);

				Model = ModelPool->GetModel(* Specification);

				TEST_TRUE(Model == BuildEntryModel);

				// ---

				Specification->SetEvaluation(true, ContextModel);

				Model = ModelPool->GetModel(* Specification);

				TEST_TRUE(Model == ContextModel);

				// ---

				Specification->SetEvaluation(true, DateTimeModel);

				Model = ModelPool->GetModel(* Specification);

				TEST_TRUE(Model == DateTimeModel);

				// ---

				Specification->SetEvaluation(true, DossierModel);

				Model = ModelPool->GetModel(* Specification);

				TEST_TRUE(Model == DossierModel);

				// ---

				Specification->SetEvaluation(true, JobModel);

				Model = ModelPool->GetModel(* Specification);

				TEST_TRUE(Model == JobModel);

				// ---

				Specification->SetEvaluation(true, ModesModel);

				Model = ModelPool->GetModel(* Specification);

				TEST_TRUE(Model == ModesModel);

				// ---

				Specification->SetEvaluation(true, ProgressModel);

				Model = ModelPool->GetModel(* Specification);

				TEST_TRUE(Model == ProgressModel);

				// ---

				Specification->SetEvaluation(true, SelectionModel);

				Model = ModelPool->GetModel(* Specification);

				TEST_TRUE(Model == SelectionModel);

				// ---

				Specification->SetEvaluation(true, TitleModel);

				Model = ModelPool->GetModel(* Specification);

				TEST_TRUE(Model == TitleModel);

				// ---

				TestWorld->DestroyActor(Character);

				return true;
			});
		});
	}
}