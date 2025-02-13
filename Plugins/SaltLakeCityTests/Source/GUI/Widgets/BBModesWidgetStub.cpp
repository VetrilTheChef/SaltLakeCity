// SaltLakeCity 4.26

#include "BBModesWidgetStub.h"

UBBModesWidgetStub::UBBModesWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	PlayModeCommand = nullptr;
	BuildModeCommand = nullptr;

	ActiveGameMode = EBBGameMode::None;
}

EBBWidget UBBModesWidgetStub::GetType() const
{
	return EBBWidget::Modes;
}

UIBBCommand * UBBModesWidgetStub::GetPlayModeCommand() const
{
	return PlayModeCommand;
}

void UBBModesWidgetStub::SetPlayModeCommand(UIBBCommand * Command)
{
	PlayModeCommand = Command;
}

UIBBCommand * UBBModesWidgetStub::GetBuildModeCommand() const
{
	return BuildModeCommand;
}

void UBBModesWidgetStub::SetBuildModeCommand(UIBBCommand * Command)
{
	BuildModeCommand = Command;
}

EBBGameMode UBBModesWidgetStub::GetActiveMode() const
{
	return ActiveGameMode;
}

void UBBModesWidgetStub::SetActiveMode(EBBGameMode GameMode)
{
	ActiveGameMode = GameMode;
}
