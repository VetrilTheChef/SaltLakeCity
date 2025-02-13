// SaltLakeCity 4.26

#include "BBGameModeCommand.h"
#include "GameModes/Interfaces/IBBGameMode.h"

UBBGameModeCommand::UBBGameModeCommand() :
	Super()
{
	GameMode = nullptr;
	ActiveGameMode = EBBGameMode::None;
}

void UBBGameModeCommand::SetGameMode(AIBBGameMode * NewGameMode)
{
	GameMode = NewGameMode;
}

void UBBGameModeCommand::SetActiveGameMode(EBBGameMode NewActiveGameMode)
{
	ActiveGameMode = NewActiveGameMode;
}

void UBBGameModeCommand::Execute()
{
	verifyf(IsValid(GameMode), TEXT("HUD is invalid."));

	GameMode->SetMode(ActiveGameMode);
}