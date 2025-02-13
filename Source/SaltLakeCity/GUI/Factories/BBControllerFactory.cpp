// SaltLakeCity 4.27

#include "BBControllerFactory.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Widgets/Interfaces/IBBBuildWidget.h"
#include "GUI/Controllers/Interfaces/IBBBuildController.h"
#include "GUI/Widgets/Interfaces/IBBBuildEntryWidget.h"
#include "GUI/Controllers/Interfaces/IBBBuildEntryController.h"
#include "GUI/Widgets/Interfaces/IBBContextWidget.h"
#include "GUI/Controllers/Interfaces/IBBContextController.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"
#include "GUI/Controllers/Interfaces/IBBDateTimeController.h"
#include "GUI/Widgets/Interfaces/IBBDossierWidget.h"
#include "GUI/Controllers/Interfaces/IBBDossierController.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"
#include "GUI/Controllers/Interfaces/IBBDossierEntryController.h"
#include "GUI/Widgets/Interfaces/IBBJobWidget.h"
#include "GUI/Controllers/Interfaces/IBBJobController.h"
#include "GUI/Widgets/Interfaces/IBBModesWidget.h"
#include "GUI/Controllers/Interfaces/IBBModesController.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"
#include "GUI/Controllers/Interfaces/IBBProgressController.h"
#include "GUI/Widgets/Interfaces/IBBSelectionWidget.h"
#include "GUI/Controllers/Interfaces/IBBSelectionController.h"
#include "GUI/Widgets/Interfaces/IBBSkillEntryWidget.h"
#include "GUI/Controllers/Interfaces/IBBSkillEntryController.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"
#include "GUI/Controllers/Interfaces/IBBTitleController.h"

UBBControllerFactory::UBBControllerFactory() :
	Super()
{
	GameInstance = nullptr;
	HUD = nullptr;
}

void UBBControllerFactory::Initialize(const UIBBGameInstance * NewGameInstance, const AIBBHUD * NewHUD)
{
	verifyf(IsValid(NewGameInstance), TEXT("New Game Instance is invalid."));

	GameInstance = NewGameInstance;

	verifyf(IsValid(NewHUD), TEXT("New HUD is invalid."));

	HUD = NewHUD;
}

void UBBControllerFactory::Finalize()
{
	GameInstance = nullptr;
	HUD = nullptr;
}

bool UBBControllerFactory::NewBuildController(UIBBBuildController * & Controller, UIBBBuildWidget * View, UIBBBuildModel * Model) const
{
	verifyf(!BuildControllerClass.IsNull(), TEXT("Build Controller Class is null."));

	Controller = NewObject<UIBBBuildController>(View, BuildControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model);

		return true;
	}

	return false;
}

bool UBBControllerFactory::NewBuildEntryController(UIBBBuildEntryController * & Controller, UIBBBuildEntryWidget * View, UIBBBuildEntryModel * Model) const
{
	verifyf(!BuildEntryControllerClass.IsNull(), TEXT("Build Entry Controller Class is null."));
	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	Controller = NewObject<UIBBBuildEntryController>(View, BuildEntryControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model, GameInstance->GetCommandFactory());

		return true;
	}

	return false;
}

bool UBBControllerFactory::NewContextController(UIBBContextController * & Controller, UIBBContextWidget * View, UIBBContextModel * Model) const
{
	verifyf(!ContextControllerClass.IsNull(), TEXT("Context Controller Class is null."));
	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	Controller = NewObject<UIBBContextController>(View, ContextControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model, HUD->GetWidgetSpecificationFactory(), GameInstance->GetCommandFactory());

		return true;
	}

	return false;
}

bool UBBControllerFactory::NewDateTimeController(UIBBDateTimeController * & Controller, UIBBDateTimeWidget * View, UIBBDateTimeModel * Model) const
{
	verifyf(!DateTimeControllerClass.IsNull(), TEXT("Date Time Controller Class is null."));
	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	Controller = NewObject<UIBBDateTimeController>(View, DateTimeControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model, GameInstance->GetCommandFactory());

		return true;
	}

	return false;
}

bool UBBControllerFactory::NewDossierController(UIBBDossierController * & Controller, UIBBDossierWidget * View, UIBBDossierModel * Model) const
{
	verifyf(!DossierControllerClass.IsNull(), TEXT("Dossier Controller Class is null."));
	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));
	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	Controller = NewObject<UIBBDossierController>(View, DossierControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model, HUD->GetWidgetFactory(), GameInstance->GetSpecificationFactory(), GameInstance->GetCommandFactory());
		
		return true;
	}

	return false;
}

bool UBBControllerFactory::NewDossierEntryController(UIBBDossierEntryController * & Controller, UIBBDossierEntryWidget * View, UIBBDossierEntryModel * Model) const
{
	verifyf(!DossierEntryControllerClass.IsNull(), TEXT("Dossier Entry Controller Class is null."));

	Controller = NewObject<UIBBDossierEntryController>(View, DossierEntryControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model);

		return true;
	}

	return false;
}

bool UBBControllerFactory::NewJobController(UIBBJobController * & Controller, UIBBJobWidget * View, UIBBJobModel * Model) const
{
	verifyf(!JobControllerClass.IsNull(), TEXT("Job Controller Class is null."));
	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));
	verifyf(IsValid(HUD), TEXT("HUD is invalid."));
	
	Controller = NewObject<UIBBJobController>(View, JobControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model, HUD->GetWidgetFactory(), HUD->GetWidgetSpecificationFactory(), GameInstance->GetCommandFactory());

		return true;
	}

	return false;
}

bool UBBControllerFactory::NewModesController(UIBBModesController * & Controller, UIBBModesWidget * View, UIBBModesModel * Model) const
{
	verifyf(!ModesControllerClass.IsNull(), TEXT("Modes Controller Class is null."));
	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	Controller = NewObject<UIBBModesController>(View, ModesControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model, GameInstance->GetCommandFactory());

		return true;
	}

	return false;
}

bool UBBControllerFactory::NewProgressController(UIBBProgressController * & Controller, UIBBProgressWidget * View, UIBBProgressModel * Model) const
{
	verifyf(!ProgressControllerClass.IsNull(), TEXT("Progress Controller Class is null."));

	Controller = NewObject<UIBBProgressController>(View, ProgressControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model);

		return true;
	}

	return false;
}

bool UBBControllerFactory::NewSelectionController(UIBBSelectionController * & Controller, UIBBSelectionWidget * View, UIBBSelectionModel * Model) const
{
	verifyf(!SelectionControllerClass.IsNull(), TEXT("Selection Controller Class is null."));

	Controller = NewObject<UIBBSelectionController>(View, SelectionControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model);

		return true;
	}

	return false;
}

bool UBBControllerFactory::NewSkillEntryController(UIBBSkillEntryController * & Controller, UIBBSkillEntryWidget * View, UIBBSkillEntryModel * Model) const
{
	verifyf(!SkillEntryControllerClass.IsNull(), TEXT("Skill Entry Controller Class is null."));

	Controller = NewObject<UIBBSkillEntryController>(View, SkillEntryControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model);

		return true;
	}

	return false;
}

bool UBBControllerFactory::NewTitleController(UIBBTitleController * & Controller, UIBBTitleWidget * View, UIBBTitleModel * Model) const
{
	verifyf(!TitleControllerClass.IsNull(), TEXT("Title Controller Class is null."));
	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));
	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	Controller = NewObject<UIBBTitleController>(View, TitleControllerClass.LoadSynchronous());

	if (IsValid(Controller))
	{
		Controller->Initialize(View, Model, HUD->GetWidgetSpecificationFactory(), GameInstance->GetCommandFactory());

		return true;
	}

	return false;
}