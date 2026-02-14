// SaltLakeCity 5.7

#include "BBDateTimeController.h"
#include "Commands/Controllers/BBPauseCommand.h"
#include "Commands/Controllers/BBSpeedCommand.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "GameInstances/BBGameInstance.h"
#include "GUI/Models/Interfaces/IBBDateTimeModel.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"

UBBDateTimeController::UBBDateTimeController() :
	Super()
{
	Model = nullptr;
	View = nullptr;

	SlowMotionTimeDilation = 0.5f;
	PlayTimeDilation = 1.0f;
	FastForwardTimeDilation = 2.0f;
}

void UBBDateTimeController::Initialize(UIBBDateTimeWidget * DateTimeView, UIBBDateTimeModel * DateTimeModel, const UIBBCommandFactory * CommandFactory)
{
	InitializeView(DateTimeView, CommandFactory);
	InitializeModel(DateTimeModel);
}

void UBBDateTimeController::Finalize()
{
	FinalizeModel();
	FinalizeView();
}

float UBBDateTimeController::GetSlowMotionTimeDilation()
{
	return SlowMotionTimeDilation;
}

float UBBDateTimeController::GetPlayTimeDilation()
{
	return PlayTimeDilation;
}

float UBBDateTimeController::GetFastForwardTimeDilation()
{
	return FastForwardTimeDilation;
}



void UBBDateTimeController::InitializeModel(UIBBDateTimeModel * DateTimeModel)
{
	FinalizeModel();

	verifyf(IsValid(DateTimeModel), TEXT("Date-Time Model is invalid."));

	Model = DateTimeModel;
}

void UBBDateTimeController::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}

void UBBDateTimeController::InitializeView(UIBBDateTimeWidget * DateTimeView, const UIBBCommandFactory * CommandFactory)
{
	FinalizeView();

	verifyf(IsValid(DateTimeView), TEXT("Date-Time View is invalid."));

	View = DateTimeView;

	verifyf(IsValid(CommandFactory), TEXT("Command Factory is invalid."));
	
	CreateCommands(* View, * CommandFactory);
}

void UBBDateTimeController::FinalizeView()
{
	if (IsValid(View))
	{
		View->MarkAsGarbage();
	}

	View = nullptr;
}

void UBBDateTimeController::CreateCommands(UIBBDateTimeWidget & DateTimeView, const UIBBCommandFactory & CommandFactory)
{
	CreatePauseCommand(DateTimeView, CommandFactory);
	CreateSlowMotionCommand(DateTimeView, CommandFactory);
	CreatePlayCommand(DateTimeView, CommandFactory);
	CreateFastForwardCommand(DateTimeView, CommandFactory);
}

void UBBDateTimeController::CreatePauseCommand(UIBBDateTimeWidget & DateTimeView, const UIBBCommandFactory & CommandFactory)
{
	UIBBPauseCommand * Command = nullptr;

	if (CommandFactory.NewPauseCommand(Command, this))
	{
		DateTimeView.SetPauseCommand(Command);
	}
}

void UBBDateTimeController::CreateSlowMotionCommand(UIBBDateTimeWidget & DateTimeView, const UIBBCommandFactory & CommandFactory)
{
	UIBBSpeedCommand * Command = nullptr;

	if (CommandFactory.NewSpeedCommand(Command, this, SlowMotionTimeDilation))
	{
		DateTimeView.SetSlowMotionCommand(Command);
	}
}

void UBBDateTimeController::CreatePlayCommand(UIBBDateTimeWidget & DateTimeView, const UIBBCommandFactory & CommandFactory)
{
	UIBBSpeedCommand * Command = nullptr;

	if (CommandFactory.NewSpeedCommand(Command, this, PlayTimeDilation))
	{
		DateTimeView.SetPlayCommand(Command);
	}
}

void UBBDateTimeController::CreateFastForwardCommand(UIBBDateTimeWidget & DateTimeView, const UIBBCommandFactory & CommandFactory)
{
	UIBBSpeedCommand * Command = nullptr;

	if (CommandFactory.NewSpeedCommand(Command, this, FastForwardTimeDilation))
	{
		DateTimeView.SetFastForwardCommand(Command);
	}
}