// SaltLakeCity 4.27

#include "BBSpeedCommandStub.h"

UBBSpeedCommandStub::UBBSpeedCommandStub() :
	Super()
{
	Controller = nullptr;
	TimeDilation = 1.0;

	Executions = 0;
}

AIBBPlayerController * UBBSpeedCommandStub::GetController()
{
	return Controller;
}

void UBBSpeedCommandStub::SetController(AIBBPlayerController * NewController)
{
	Controller = NewController;
}

float UBBSpeedCommandStub::GetTimeDilation()
{
	return TimeDilation;
}

void UBBSpeedCommandStub::SetTimeDilation(float NewTimeDilation)
{
	TimeDilation = FMath::Max(NewTimeDilation, 0.001f);
}

void UBBSpeedCommandStub::Execute()
{
	Executions++;
}

int UBBSpeedCommandStub::GetNumExecutions() const
{
	return Executions;
}