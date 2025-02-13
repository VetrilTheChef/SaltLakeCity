// SaltLakeCity 4.26

#include "BBPauseCommand.h"
#include "Controllers/Interfaces/IBBPlayerController.h"

UBBPauseCommand::UBBPauseCommand() :
	Super()
{
	Controller = nullptr;
}

void UBBPauseCommand::SetController(AIBBPlayerController * NewController)
{
	verifyf(IsValid(NewController), TEXT("New Controller is invalid."));

	Controller = NewController;
}

void UBBPauseCommand::Execute()
{
	verifyf(IsValid(Controller), TEXT("Controller is invalid."));

	Controller->SetPause(!(Controller->IsPaused()), nullptr);
}