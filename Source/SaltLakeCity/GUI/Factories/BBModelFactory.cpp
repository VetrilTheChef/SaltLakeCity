// SaltLakeCity 4.27

#include "BBModelFactory.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "GUI/Components/Interfaces/IBBModelPool.h"
#include "GUI/Components/Iterators/Interfaces/IBBModelIterator.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Models/Interfaces/IBBBuildModel.h"
#include "GUI/Models/Interfaces/IBBBuildEntryModel.h"
#include "GUI/Models/Interfaces/IBBContextModel.h"
#include "GUI/Models/Interfaces/IBBDateTimeModel.h"
#include "GUI/Models/Interfaces/IBBDossierModel.h"
#include "GUI/Models/Interfaces/IBBDossierEntryModel.h"
#include "GUI/Models/Interfaces/IBBJobModel.h"
#include "GUI/Models/Interfaces/IBBModesModel.h"
#include "GUI/Models/Interfaces/IBBProgressModel.h"
#include "GUI/Models/Interfaces/IBBSelectionModel.h"
#include "GUI/Models/Interfaces/IBBSkillEntryModel.h"
#include "GUI/Models/Interfaces/IBBTitleModel.h"

UBBModelFactory::UBBModelFactory() :
	Super()
{
	GameMode = nullptr;
	GameState = nullptr;
	HUD = nullptr;
}

void UBBModelFactory::Initialize(const AIBBGameState * NewGameState, AIBBGameMode * NewGameMode, AIBBHUD * NewHUD)
{
	verifyf(IsValid(NewGameState), TEXT("New Game State is invalid."));

	GameState = NewGameState;

	verifyf(IsValid(NewGameMode), TEXT("New Game Mode is invalid."));

	GameMode = NewGameMode;

	verifyf(IsValid(NewHUD), TEXT("New HUD is invalid."));

	HUD = NewHUD;
}

void UBBModelFactory::Finalize()
{
	GameMode = nullptr;
	GameState = nullptr;
	HUD = nullptr;
}

bool UBBModelFactory::NewBuildModel(UIBBBuildModel * & Model, UIBBBuildWidget * View) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!BuildModelClass.IsNull(), TEXT("Build Model Class is null."));

	Model = NewObject<UIBBBuildModel>(ModelPool, BuildModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, Model->GetDataTable(), Model->GetEntryClass());

		ModelPool->AddBuildModel(Model);
	}

	return IsValid(Model);
}

bool UBBModelFactory::NewBuildEntryModel(UIBBBuildEntryModel * & Model, UIBBBuildEntryWidget * View, const UIBBBuildEntry * Entry) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!BuildEntryModelClass.IsNull(), TEXT("Build Entry Model Class is null."));
	
	Model = NewObject<UIBBBuildEntryModel>(ModelPool, BuildEntryModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, Entry);

		ModelPool->AddBuildEntryModel(Model);
	}

	return IsValid(Model);
}

bool UBBModelFactory::NewContextModel(UIBBContextModel * & Model, UIBBContextWidget * View) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!ContextModelClass.IsNull(), TEXT("Context Model Class is null."));

	Model = NewObject<UIBBContextModel>(ModelPool, ContextModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, HUD, Model->GetDataTable());

		ModelPool->AddContextModel(Model);
	}

	return IsValid(Model);
}

bool UBBModelFactory::NewDateTimeModel(UIBBDateTimeModel * & Model, UIBBDateTimeWidget * View) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!DateTimeModelClass.IsNull(), TEXT("Date Time Model Class is null."));

	Model = NewObject<UIBBDateTimeModel>(ModelPool, DateTimeModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, GameState->GetGameClock());

		ModelPool->AddDateTimeModel(Model);
	}

	return IsValid(Model);
}

bool UBBModelFactory::NewDossierModel(UIBBDossierModel * & Model, UIBBDossierWidget * View, AIBBCharacter * Character) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!DossierModelClass.IsNull(), TEXT("Dossier Model Class is null."));

	Model = NewObject<UIBBDossierModel>(ModelPool, DossierModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, Character);

		ModelPool->AddDossierModel(Model);
	}

	return IsValid(Model);
}

bool UBBModelFactory::NewDossierEntryModel(UIBBDossierEntryModel * & Model, UIBBDossierEntryWidget * View, UIBBDossierEntry * Entry) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!DossierEntryModelClass.IsNull(), TEXT("Dossier Entry Model Class is null."));

	Model = NewObject<UIBBDossierEntryModel>(ModelPool, DossierEntryModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, Entry);

		ModelPool->AddDossierEntryModel(Model);
	}

	return IsValid(Model);
}

bool UBBModelFactory::NewJobModel(UIBBJobModel * & Model, UIBBJobWidget * View) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!JobModelClass.IsNull(), TEXT("Job Model Class is null."));

	Model = NewObject<UIBBJobModel>(ModelPool, JobModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, HUD, Model->GetDataTable());

		ModelPool->AddJobModel(Model);
	}

	return IsValid(Model);
}

bool UBBModelFactory::NewModesModel(UIBBModesModel * & Model, UIBBModesWidget * View) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!ModesModelClass.IsNull(), TEXT("Modes Model Class is null."));

	Model = NewObject<UIBBModesModel>(ModelPool, ModesModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, GameMode);

		ModelPool->AddModesModel(Model);
	}

	return IsValid(Model);
}

bool UBBModelFactory::NewProgressModel(UIBBProgressModel * & Model, UIBBProgressWidget * View, UIBBProgressComponent * Component) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!ProgressModelClass.IsNull(), TEXT("Progress Model Class is null."));

	Model = NewObject<UIBBProgressModel>(ModelPool, ProgressModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, Component);

		ModelPool->AddProgressModel(Model);
	}

	return IsValid(Model);
}

bool UBBModelFactory::NewSelectionModel(UIBBSelectionModel * & Model, UIBBSelectionWidget * View) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!SelectionModelClass.IsNull(), TEXT("Selection Model Class is null."));

	Model = NewObject<UIBBSelectionModel>(ModelPool, SelectionModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, HUD);

		ModelPool->AddSelectionModel(Model);
	}

	return IsValid(Model);
}

bool UBBModelFactory::NewSkillEntryModel(UIBBSkillEntryModel * & Model, UIBBSkillEntryWidget * View, const UIBBSkillEntry * Entry) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!SkillEntryModelClass.IsNull(), TEXT("Skill Entry Model Class is null."));

	Model = NewObject<UIBBSkillEntryModel>(ModelPool, SkillEntryModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, Entry);

		ModelPool->AddSkillEntryModel(Model);
	}

	return IsValid(Model);
}

bool UBBModelFactory::NewTitleModel(UIBBTitleModel * & Model, UIBBTitleWidget * View, UIBBGUIModel * ParentModel) const
{
	UIBBModelPool * ModelPool = HUD->GetModelPool();

	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));
	verifyf(!TitleModelClass.IsNull(), TEXT("Title Model Class is null."));

	Model = NewObject<UIBBTitleModel>(ModelPool, TitleModelClass.LoadSynchronous());

	if (IsValid(Model))
	{
		Model->Initialize(View, ParentModel, HUD);

		ModelPool->AddTitleModel(Model);
	}

	return IsValid(Model);
}