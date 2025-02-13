// SaltLakeCity 4.26

#include "BBDateTimeControllerStub.h"
#include "Commands/Controllers/Interfaces/IBBPauseCommand.h"
#include "Commands/Controllers/Interfaces/IBBSpeedCommand.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "GUI/Models/Interfaces/IBBDateTimeModel.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"

UBBDateTimeControllerStub::UBBDateTimeControllerStub() :
	Super()
{
	Model = nullptr;
	View = nullptr;

	CurrentDate = FText::FromString("");
	CurrentTime = FText::FromString("");
}

void UBBDateTimeControllerStub::Initialize(UIBBDateTimeWidget * DateTimeView, UIBBDateTimeModel * DateTimeModel, const UIBBCommandFactory * CommandFactory)
{
	InitializeModel(DateTimeModel);
	InitializeView(DateTimeView, CommandFactory);
}

void UBBDateTimeControllerStub::Finalize()
{
	FinalizeModel();
	FinalizeView();
}

float UBBDateTimeControllerStub::GetSlowMotionTimeDilation()
{
	return -1.0f;
}

float UBBDateTimeControllerStub::GetPlayTimeDilation()
{
	return -1.0f;
}

float UBBDateTimeControllerStub::GetFastForwardTimeDilation()
{
	return -1.0f;
}

FText UBBDateTimeControllerStub::GetDate()
{
	return CurrentDate;
}

void UBBDateTimeControllerStub::SetDate(FText NewDate)
{
	CurrentDate = NewDate;
}

FText UBBDateTimeControllerStub::GetTime()
{
	return CurrentTime;
}

void UBBDateTimeControllerStub::SetTime(FText NewTime)
{
	CurrentTime = NewTime;
}



void UBBDateTimeControllerStub::InitializeModel(UIBBDateTimeModel * DateTimeModel)
{
	Model = DateTimeModel;
}

void UBBDateTimeControllerStub::InitializeView(UIBBDateTimeWidget * DateTimeView, const UIBBCommandFactory * CommandFactory)
{
	View = DateTimeView;

	if (IsValid(View) && IsValid(CommandFactory))
	{
		UIBBPauseCommand * PauseCommand = nullptr;
		CommandFactory->NewPauseCommand(PauseCommand, this);
		View->SetPauseCommand(PauseCommand);

		UIBBSpeedCommand * SlowMotionCommand = nullptr;
		CommandFactory->NewSpeedCommand(SlowMotionCommand, this, 0.5f);
		View->SetSlowMotionCommand(SlowMotionCommand);

		UIBBSpeedCommand * PlayCommand = nullptr;
		CommandFactory->NewSpeedCommand(PlayCommand, this, 1.0f);
		View->SetPlayCommand(PlayCommand);

		UIBBSpeedCommand * FastForwardCommand = nullptr;
		CommandFactory->NewSpeedCommand(FastForwardCommand, this, 2.0f);
		View->SetFastForwardCommand(FastForwardCommand);
	}
}

void UBBDateTimeControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}

void UBBDateTimeControllerStub::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}