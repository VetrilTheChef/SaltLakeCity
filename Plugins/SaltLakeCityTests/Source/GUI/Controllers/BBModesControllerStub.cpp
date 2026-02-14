// SaltLakeCity 5.7

#include "BBModesControllerStub.h"
#include "GUI/Models/Interfaces/IBBModesModel.h"
#include "GUI/Widgets/Interfaces/IBBModesWidget.h"
#include "Commands/GameModes/Interfaces/IBBGameModeCommand.h"

UBBModesControllerStub::UBBModesControllerStub() :
	Super()
{
	Model = nullptr;
	View = nullptr;

	BuildModeCommand = nullptr;
	PlayModeCommand = nullptr;

	ActiveGameMode = EBBGameMode::None;
}

void UBBModesControllerStub::Initialize(UIBBModesWidget * ModesView, UIBBModesModel * ModesModel, const UIBBCommandFactory * CommandFactory)
{
	InitializeView(ModesView);

	InitializeModel(ModesModel);
}

void UBBModesControllerStub::Finalize()
{
	FinalizeView();
	FinalizeModel();
}

void UBBModesControllerStub::SetViewCommands(UIBBGameModeCommand * NewBuildModeCommand, UIBBGameModeCommand * NewPlayModeCommand)
{
	BuildModeCommand = NewBuildModeCommand;
	PlayModeCommand = NewPlayModeCommand;
}

EBBGameMode UBBModesControllerStub::GetActiveGameMode() const
{
	return ActiveGameMode;
}



void UBBModesControllerStub::InitializeModel(UIBBModesModel * NewModel)
{
	FinalizeModel();

	Model = NewModel;

	if (IsValid(Model))
	{
		Model->OnModeUpdate.AddDynamic(this, &UBBModesControllerStub::UpdateMode);
	}
}

void UBBModesControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
		Model->OnModeUpdate.RemoveDynamic(this, &UBBModesControllerStub::UpdateMode);
	}

	Model = nullptr;
}

void UBBModesControllerStub::InitializeView(UIBBModesWidget * NewView)
{
	FinalizeView();

	View = NewView;

	if (IsValid(View))
	{
		View->SetBuildModeCommand(BuildModeCommand);
		View->SetPlayModeCommand(PlayModeCommand);
	}
}

void UBBModesControllerStub::FinalizeView()
{
	if (IsValid(View))
	{
		View->MarkAsGarbage();
	}

	View = nullptr;
}

void UBBModesControllerStub::UpdateMode(EBBGameMode NewGameMode)
{
	ActiveGameMode = NewGameMode;
}