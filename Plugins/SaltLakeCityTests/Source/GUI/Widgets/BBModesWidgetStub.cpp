// SaltLakeCity 5.7

#include "BBModesWidgetStub.h"
#include "Commands/Interfaces/IBBCommand.h"

UBBModesWidgetStub::UBBModesWidgetStub(const FObjectInitializer& ObjectInitializer) :
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

void UBBModesWidgetStub::AddToScreen(int32 ZOrder)
{
}

UIBBCommand* UBBModesWidgetStub::GetPlayModeCommand() const
{
	return PlayModeCommand.Get();
}

void UBBModesWidgetStub::SetPlayModeCommand(UIBBCommand* Command)
{
	PlayModeCommand = Command;
}

UIBBCommand* UBBModesWidgetStub::GetBuildModeCommand() const
{
	return BuildModeCommand.Get();
}

void UBBModesWidgetStub::SetBuildModeCommand(UIBBCommand* Command)
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
