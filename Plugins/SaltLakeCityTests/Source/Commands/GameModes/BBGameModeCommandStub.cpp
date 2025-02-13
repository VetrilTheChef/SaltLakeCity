// SaltLakeCity 4.27

#include "BBGameModeCommandStub.h"

UBBGameModeCommandStub::UBBGameModeCommandStub() :
	Super()
{
	GameMode = nullptr;
	ActiveGameMode = EBBGameMode::None;

	Executions = 0;
}

AIBBGameMode * UBBGameModeCommandStub::GetGameMode()
{
	return GameMode;
}

void UBBGameModeCommandStub::SetGameMode(AIBBGameMode * NewGameMode)
{
	GameMode = NewGameMode;
}

EBBGameMode UBBGameModeCommandStub::GetActiveGameMode()
{
	return ActiveGameMode;
}

void UBBGameModeCommandStub::SetActiveGameMode(EBBGameMode NewActiveGameMode)
{
	ActiveGameMode = NewActiveGameMode;
}

void UBBGameModeCommandStub::Execute()
{
	Executions++;
}

int UBBGameModeCommandStub::GetNumExecutions() const
{
	return Executions;
}