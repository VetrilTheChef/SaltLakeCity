 // SaltLakeCity 5.7

#include "BBWidgetFactory.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GUI/Factories/BBControllerFactory.h"
#include "GUI/Factories/BBModelFactory.h"
#include "GUI/Factories/BBViewFactory.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Widgets/Interfaces/IBBBuildEntryWidget.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"

UBBWidgetFactory::UBBWidgetFactory() :
	Super()
{
	GameInstance = nullptr;
	GameState = nullptr;
	GameMode = nullptr;
	HUD = nullptr;
	PlayerController = nullptr;
	SpecificationFactory = nullptr;

	ModelFactory = nullptr;
	ViewFactory = nullptr;
	ControllerFactory = nullptr;
}

void UBBWidgetFactory::Initialize(const UIBBGameInstance * NewGameInstance, const AIBBGameState * NewGameState, AIBBGameMode * NewGameMode, AIBBHUD * NewHUD, APlayerController * NewPlayerController)
{
	GameInstance = NewGameInstance;
	GameState = NewGameState;
	GameMode = NewGameMode;
	HUD = NewHUD;
	PlayerController = NewPlayerController;

	InitializeFactories();
}

void UBBWidgetFactory::Finalize()
{
	FinalizeFactories();

	GameInstance = nullptr;
	GameState = nullptr;
	GameMode = nullptr;
	HUD = nullptr;
	PlayerController = nullptr;
	SpecificationFactory = nullptr;
}

void UBBWidgetFactory::InjectSpecificationFactory(UIBBSpecificationFactory * NewSpecificationFactory)
{
	SpecificationFactory = NewSpecificationFactory;
}

bool UBBWidgetFactory::NewBuildWidget(UIBBBuildWidget * & Widget) const
{
	VerifyFactories();

	Widget = nullptr;
	UIBBBuildModel * BuildModel = nullptr;
	UIBBBuildController * BuildController = nullptr;

	if (ViewFactory->NewBuildView(Widget))
	{
		if (ModelFactory->NewBuildModel(BuildModel, Widget))
		{
			if (ControllerFactory->NewBuildController(BuildController, Widget, BuildModel))
			{
				return true;
			}
		}
	}

	return false;
}

bool UBBWidgetFactory::NewBuildEntryWidget(UIBBBuildEntryWidget * & Widget, const UIBBBuildEntry * Entry) const
{
	VerifyFactories();

	verifyf(IsValid(Widget), TEXT("Build Entry Widget is invalid."));

	UIBBBuildEntryModel * BuildEntryModel = nullptr;
	UIBBBuildEntryController * BuildEntryController = nullptr;

	if (ModelFactory->NewBuildEntryModel(BuildEntryModel, Widget, Entry))
	{
		if (ControllerFactory->NewBuildEntryController(BuildEntryController, Widget, BuildEntryModel))
		{
			return true;
		}
	}

	return false;
}

bool UBBWidgetFactory::NewContextWidget(UIBBContextWidget * & Widget) const
{
	VerifyFactories();

	Widget = nullptr;
	UIBBContextModel * ContextModel = nullptr;
	UIBBContextController * ContextController = nullptr;

	if (ViewFactory->NewContextView(Widget))
	{
		if (ModelFactory->NewContextModel(ContextModel, Widget))
		{
			if (ControllerFactory->NewContextController(ContextController, Widget, ContextModel))
			{
				return true;
			}
		}
	}

	return false;
}

bool UBBWidgetFactory::NewDateTimeWidget(UIBBDateTimeWidget * & Widget) const
{
	VerifyFactories();

	Widget = nullptr;
	UIBBDateTimeModel * DateTimeModel = nullptr;
	UIBBDateTimeController * DateTimeController = nullptr;

	if (ViewFactory->NewDateTimeView(Widget))
	{
		if (ModelFactory->NewDateTimeModel(DateTimeModel, Widget))
		{
			if (ControllerFactory->NewDateTimeController(DateTimeController, Widget, DateTimeModel))
			{
				return true;
			}
		}
	}

	return false;
}

bool UBBWidgetFactory::NewDossierWidget(UIBBDossierWidget * & Widget, AIBBCharacter * Character) const
{
	VerifyFactories();

	Widget = nullptr;
	UIBBDossierModel * DossierModel = nullptr;
	UIBBDossierController * DossierController = nullptr;

	if (ViewFactory->NewDossierView(Widget))
	{
		if (ModelFactory->NewDossierModel(DossierModel, Widget, Character))
		{
			if (ControllerFactory->NewDossierController(DossierController, Widget, DossierModel))
			{
				return true;
			}
		}
	}

	return false;
}

bool UBBWidgetFactory::NewDossierEntryWidget(UIBBDossierEntryWidget * & Widget, UIBBDossierEntry * Entry) const
{
	VerifyFactories();

	verifyf(IsValid(Widget), TEXT("Dossier Entry Widget is invalid."));

	UIBBDossierEntryModel * DossierEntryModel = nullptr;
	UIBBDossierEntryController * DossierEntryController = nullptr;

	if (ModelFactory->NewDossierEntryModel(DossierEntryModel, Widget, Entry))
	{
		if (ControllerFactory->NewDossierEntryController(DossierEntryController, Widget, DossierEntryModel))
		{
			return true;
		}
	}

	return false;
}

bool UBBWidgetFactory::NewJobWidget(UIBBJobWidget * & Widget) const
{
	VerifyFactories();

	Widget = nullptr;
	UIBBJobModel * JobModel = nullptr;
	UIBBJobController * JobController = nullptr;

	if (ViewFactory->NewJobView(Widget))
	{
		if (ModelFactory->NewJobModel(JobModel, Widget))
		{
			if (ControllerFactory->NewJobController(JobController, Widget, JobModel))
			{
				return true;
			}
		}
	}

	return false;
}

bool UBBWidgetFactory::NewModesWidget(UIBBModesWidget * & Widget) const
{
	VerifyFactories();

	Widget = nullptr;
	UIBBModesModel * ModesModel = nullptr;
	UIBBModesController * ModesController = nullptr;

	if (ViewFactory->NewModesView(Widget))
	{
		if (ModelFactory->NewModesModel(ModesModel, Widget))
		{
			if (ControllerFactory->NewModesController(ModesController, Widget, ModesModel))
			{
				return true;
			}
		}
	}

	return false;
}

bool UBBWidgetFactory::NewProgressWidget(UIBBProgressWidget * & Widget, UIBBProgressComponent * Component) const
{
	VerifyFactories();

	Widget = nullptr;
	UIBBProgressModel * ProgressModel = nullptr;
	UIBBProgressController * ProgressController = nullptr;

	if (ViewFactory->NewProgressView(Widget))
	{
		if (ModelFactory->NewProgressModel(ProgressModel, Widget, Component))
		{
			if (ControllerFactory->NewProgressController(ProgressController, Widget, ProgressModel))
			{
				return true;
			}
		}
	}

	return false;
}

bool UBBWidgetFactory::NewSelectionWidget(UIBBSelectionWidget * & Widget) const
{
	VerifyFactories();

	Widget = nullptr;
	UIBBSelectionModel * SelectionModel = nullptr;
	UIBBSelectionController * SelectionController = nullptr;

	if (ViewFactory->NewSelectionView(Widget))
	{
		if (ModelFactory->NewSelectionModel(SelectionModel, Widget))
		{
			if (ControllerFactory->NewSelectionController(SelectionController, Widget, SelectionModel))
			{
				return true;
			}
		}
	}

	return false;
}

bool UBBWidgetFactory::NewTitleWidget(UIBBTitleWidget * & Widget, UIBBGUIModel * ParentModel) const
{
	VerifyFactories();

	UIBBTitleModel * TitleModel = nullptr;
	UIBBTitleController * TitleController = nullptr;

	if (ViewFactory->NewTitleView(Widget))
	{
		if (ModelFactory->NewTitleModel(TitleModel, Widget, ParentModel))
		{
			if (ControllerFactory->NewTitleController(TitleController, Widget, TitleModel))
			{
				return true;
			}
		}
	}

	return false;
}



void UBBWidgetFactory::InitializeFactories()
{
	InitializeModelFactory();
	InitializeViewFactory();
	InitializeControllerFactory();
}

void UBBWidgetFactory::InitializeModelFactory()
{
	verifyf(!ModelFactoryClass.IsNull(), TEXT("Model Factory class is null."));

	ModelFactory = NewObject<UBBModelFactory>(this, ModelFactoryClass.LoadSynchronous());

	verifyf(IsValid(ModelFactory), TEXT("Model Factory is invalid."));

	ModelFactory->Initialize(GameState, GameMode, HUD, GameInstance->GetWidgetManager());
}

void UBBWidgetFactory::InitializeViewFactory()
{
	verifyf(!ViewFactoryClass.IsNull(), TEXT("View Factory class is null."));

	ViewFactory = NewObject<UBBViewFactory>(this, ViewFactoryClass.LoadSynchronous());

	verifyf(IsValid(ViewFactory), TEXT("View Factory is invalid."));

	ViewFactory->Initialize(PlayerController);
}

void UBBWidgetFactory::InitializeControllerFactory()
{
	verifyf(!ControllerFactoryClass.IsNull(), TEXT("Controller Factory class is null."));

	ControllerFactory = NewObject<UBBControllerFactory>(this, ControllerFactoryClass.LoadSynchronous());

	verifyf(IsValid(ControllerFactory), TEXT("Controller Factory is invalid."));

	ControllerFactory->Initialize(GameInstance, GameInstance->GetWidgetManager());
}

void UBBWidgetFactory::FinalizeFactories()
{
	FinalizeModelFactory();
	FinalizeViewFactory();
	FinalizeControllerFactory();
}

void UBBWidgetFactory::FinalizeModelFactory()
{
	if (IsValid(ModelFactory))
	{
		ModelFactory->MarkAsGarbage();
	}

	ModelFactory = nullptr;
}

void UBBWidgetFactory::FinalizeViewFactory()
{
	if (IsValid(ViewFactory))
	{
		ViewFactory->MarkAsGarbage();
	}

	ViewFactory = nullptr;
}

void UBBWidgetFactory::FinalizeControllerFactory()
{
	if (IsValid(ControllerFactory))
	{
		ControllerFactory->MarkAsGarbage();
	}

	ControllerFactory = nullptr;
}

void UBBWidgetFactory::VerifyFactories() const
{
	verifyf(IsValid(ModelFactory), TEXT("Model Factory is invalid."));
	verifyf(IsValid(ViewFactory), TEXT("View Factory is invalid."));
	verifyf(IsValid(ControllerFactory), TEXT("Controller Factory is invalid."));
}
