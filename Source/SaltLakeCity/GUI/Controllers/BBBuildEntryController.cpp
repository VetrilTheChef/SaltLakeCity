// SaltLakeCity 4.26

#include "BBBuildEntryController.h"
#include "Abilities/Data/Interfaces/IBBBuildData.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Commands/Controllers/Interfaces/IBBOrderBuildCommand.h"
#include "GUI/Models/Interfaces/IBBBuildEntryModel.h"
#include "GUI/Widgets/Interfaces/IBBBuildEntryWidget.h"

UBBBuildEntryController::UBBBuildEntryController() :
	Super()
{
}

void UBBBuildEntryController::Initialize(UIBBBuildEntryWidget * BuildEntryView, UIBBBuildEntryModel * BuildEntryModel, const UIBBCommandFactory * CommandFactory)
{
	verifyf(IsValid(BuildEntryView), TEXT("Build Entry View is invalid."));
	verifyf(IsValid(BuildEntryModel), TEXT("Build Entry Model is invalid."));
	verifyf(IsValid(CommandFactory), TEXT("Command Factory is invalid."));

	InitializeView(* BuildEntryView, * BuildEntryModel, * CommandFactory);
}

void UBBBuildEntryController::Finalize()
{
}



void UBBBuildEntryController::InitializeView(UIBBBuildEntryWidget & BuildEntryView, UIBBBuildEntryModel & BuildEntryModel, const UIBBCommandFactory & CommandFactory) const
{
	BuildEntryView.SetEntryName(BuildEntryModel.GetEntryName());
	BuildEntryView.SetIcon(BuildEntryModel.GetEntryIcon().Get());
	BuildEntryView.SetPrice(BuildEntryModel.GetEntryPrice());
	BuildEntryView.SetTime(BuildEntryModel.GetEntryTime());

	CreateCommands(BuildEntryView, BuildEntryModel, CommandFactory);
}

void UBBBuildEntryController::CreateCommands(UIBBBuildEntryWidget & BuildEntryView, UIBBBuildEntryModel & BuildEntryModel, const UIBBCommandFactory & CommandFactory) const
{
	UIBBOrderBuildCommand * Command = nullptr;

	if (CommandFactory.NewOrderBuildCommand(Command, & BuildEntryView, BuildEntryModel.GetEntryBuildDataClass(), BuildEntryModel.GetEntryTargetingClass(), BuildEntryModel.GetEntryBuildableClasses(), BuildEntryModel.GetEntryPrice(), BuildEntryModel.GetEntryTime()))
	{
		BuildEntryView.SetCommand(Command);
	}
}