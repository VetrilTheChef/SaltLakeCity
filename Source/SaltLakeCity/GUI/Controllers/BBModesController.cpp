// SaltLakeCity 4.26

#include "BBModesController.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Commands/GameModes/Interfaces/IBBGameModeCommand.h"
#include "GUI/Models/Interfaces/IBBModesModel.h"
#include "GUI/Widgets/Interfaces/IBBModesWidget.h"

UBBModesController::UBBModesController() :
	Super()
{
	Model = nullptr;
	View = nullptr;
}

void UBBModesController::Initialize(UIBBModesWidget * ModesView, UIBBModesModel * ModesModel, const UIBBCommandFactory * CommandFactory)
{
	InitializeView(ModesView, CommandFactory);
	InitializeModel(ModesModel);
}

void UBBModesController::Finalize()
{
	FinalizeModel();
	FinalizeView();
}



void UBBModesController::InitializeModel(UIBBModesModel * ModesModel)
{
	FinalizeModel();

	verifyf(IsValid(ModesModel), TEXT("Modes Model is invalid."));

	Model = ModesModel;

	Model->OnModeUpdate.AddDynamic(this, &UBBModesController::UpdateMode);
}

void UBBModesController::FinalizeModel()
{
	if (IsValid(Model))
	{
		Model->OnModeUpdate.RemoveDynamic(this, &UBBModesController::UpdateMode);
	}

	Model = nullptr;
}

void UBBModesController::InitializeView(UIBBModesWidget * ModesView, const UIBBCommandFactory * CommandFactory)
{
	FinalizeView();

	verifyf(IsValid(ModesView), TEXT("Modes View is invalid."));

	View = ModesView;

	verifyf(IsValid(CommandFactory), TEXT("Command Factory is invalid."));
	
	CreateCommands(* View, * CommandFactory);
}

void UBBModesController::FinalizeView()
{
	if (IsValid(View))
	{
		View->MarkPendingKill();
	}

	View = nullptr;
}

void UBBModesController::CreateCommands(UIBBModesWidget & ModesView, const UIBBCommandFactory & CommandFactory)
{
	CreatePlayCommand(ModesView, CommandFactory);
	CreateBuildCommand(ModesView, CommandFactory);
}

void UBBModesController::CreatePlayCommand(UIBBModesWidget & ModesView, const UIBBCommandFactory & CommandFactory)
{
	UIBBGameModeCommand * Command = nullptr;

	if (CommandFactory.NewGameModeCommand(Command, this, EBBGameMode::Play))
	{
		ModesView.SetPlayModeCommand(Command);
	}
}

void UBBModesController::CreateBuildCommand(UIBBModesWidget & ModesView, const UIBBCommandFactory & CommandFactory)
{
	UIBBGameModeCommand * Command = nullptr;

	if (CommandFactory.NewGameModeCommand(Command, this, EBBGameMode::Build))
	{
		ModesView.SetBuildModeCommand(Command);
	}
}

void UBBModesController::UpdateMode(EBBGameMode NewGameMode)
{
	View->SetActiveMode(NewGameMode);
}