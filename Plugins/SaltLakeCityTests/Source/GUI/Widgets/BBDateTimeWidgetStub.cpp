// SaltLakeCity 5.7

#include "BBDateTimeWidgetStub.h"
#include "Commands/Interfaces/IBBCommand.h"

UBBDateTimeWidgetStub::UBBDateTimeWidgetStub(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	DateText = FText::FromString("");
	TimeText = FText::FromString("");

	PauseCommand = nullptr;
	SlowMotionCommand = nullptr;
	PlayCommand = nullptr;
	FastForwardCommand = nullptr;
}

EBBWidget UBBDateTimeWidgetStub::GetType() const
{
	return EBBWidget::DateTime;
}

void UBBDateTimeWidgetStub::NativeDestruct()
{
}

void UBBDateTimeWidgetStub::NativeOnInitialized()
{
}

void UBBDateTimeWidgetStub::SetPauseCommand(UIBBCommand* Command)
{
	PauseCommand = Command;
}

void UBBDateTimeWidgetStub::SetSlowMotionCommand(UIBBCommand* Command)
{
	SlowMotionCommand = Command;
}

void UBBDateTimeWidgetStub::SetPlayCommand(UIBBCommand* Command)
{
	PlayCommand = Command;
}

void UBBDateTimeWidgetStub::SetFastForwardCommand(UIBBCommand* Command)
{
	FastForwardCommand = Command;
}

FText UBBDateTimeWidgetStub::GetDate()
{
	return DateText;
}

void UBBDateTimeWidgetStub::SetDate(FText Date)
{
	DateText = Date;
}

FText UBBDateTimeWidgetStub::GetTime()
{
	return TimeText;
}

void UBBDateTimeWidgetStub::SetTime(FText Time)
{
	TimeText = Time;
}

void UBBDateTimeWidgetStub::ClickPauseButton()
{
	if (PauseCommand.IsValid())
	{
		PauseCommand->Execute();
	}
}

void UBBDateTimeWidgetStub::ClickSlowMotionButton()
{
	if (SlowMotionCommand.IsValid())
	{
		SlowMotionCommand->Execute();
	}
}

void UBBDateTimeWidgetStub::ClickPlayButton()
{
	if (PlayCommand.IsValid())
	{
		PlayCommand->Execute();
	}
}

void UBBDateTimeWidgetStub::ClickFastForwardButton()
{
	if (FastForwardCommand.IsValid())
	{
		FastForwardCommand->Execute();
	}
}