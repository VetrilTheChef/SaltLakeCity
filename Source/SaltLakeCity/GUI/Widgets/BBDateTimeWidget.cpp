// SaltLakeCity 4.24

#include "BBDateTimeWidget.h"
#include "Components/TextBlock.h"
#include "GameInstances/BBGameInstance.h"
#include "GUI/Components/BBButton.h"

UBBDateTimeWidget::UBBDateTimeWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
}

EBBWidget UBBDateTimeWidget::GetType() const
{
	return EBBWidget::DateTime;
}

void UBBDateTimeWidget::SetPauseCommand(UIBBCommand * Command)
{
	verifyf(IsValid(PauseButton), TEXT("Pause Button is invalid."));

	PauseButton->SetCommand(Command);
}

void UBBDateTimeWidget::SetSlowMotionCommand(UIBBCommand * Command)
{
	verifyf(IsValid(SlowMotionButton), TEXT("Slow Motion Button is invalid."));

	SlowMotionButton->SetCommand(Command);
}

void UBBDateTimeWidget::SetPlayCommand(UIBBCommand * Command)
{
	verifyf(IsValid(PlayButton), TEXT("Play Button is invalid."));

	PlayButton->SetCommand(Command);
}

void UBBDateTimeWidget::SetFastForwardCommand(UIBBCommand * Command)
{
	verifyf(IsValid(FastForwardButton), TEXT("Fast Forward Button is invalid."));

	FastForwardButton->SetCommand(Command);
}

void UBBDateTimeWidget::SetDate(FText Date)
{
	verifyf(IsValid(DateText), TEXT("Date Text is invalid."));

	DateText->SetText(Date);
}

void UBBDateTimeWidget::SetTime(FText Time)
{
	verifyf(IsValid(TimeText), TEXT("Time Text is invalid."));

	TimeText->SetText(Time);
}