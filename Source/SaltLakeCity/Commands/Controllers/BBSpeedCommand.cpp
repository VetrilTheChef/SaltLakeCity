// SaltLakeCity 4.26

#include "BBSpeedCommand.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "GameFramework/WorldSettings.h"

UBBSpeedCommand::UBBSpeedCommand() :
	Super()
{
	Controller = nullptr;
	TimeDilation = 1.0;
}

void UBBSpeedCommand::SetController(AIBBPlayerController * NewController)
{
	verifyf(IsValid(NewController), TEXT("New Controller is invalid."));

	Controller = NewController;
}

float UBBSpeedCommand::GetTimeDilation()
{
	return TimeDilation;
}

void UBBSpeedCommand::SetTimeDilation(float NewTimeDilation)
{
	TimeDilation = FMath::Max(NewTimeDilation, 0.001f);
}

void UBBSpeedCommand::Execute()
{
	verifyf(IsValid(Controller), TEXT("Controller is invalid."));

	Controller->SetPause(false);
	Controller->CustomTimeDilation = (1.0f / TimeDilation);

	AWorldSettings * WorldSettings = Controller->GetWorldSettings();

	verifyf(IsValid(WorldSettings), TEXT("World Settings is invalid."));

	WorldSettings->SetTimeDilation(TimeDilation);
}