// SaltLakeCity 4.27

#include "BBSetJobCommandStub.h"

UBBSetJobCommandStub::UBBSetJobCommandStub() :
	Super()
{
	WorkComponent = nullptr;
	Job = EBBJob::None;
	Executions = 0;
}

UIBBWorkComponent * UBBSetJobCommandStub::GetWorkComponent() const
{
	return WorkComponent;
}

void UBBSetJobCommandStub::SetWorkComponent(UIBBWorkComponent * NewWorkComponent)
{
	WorkComponent = NewWorkComponent;
}

EBBJob UBBSetJobCommandStub::GetJob() const
{
	return Job;
}

void UBBSetJobCommandStub::SetJob(EBBJob NewJob)
{
	Job = NewJob;
}

void UBBSetJobCommandStub::Execute()
{
	Executions++;
}

int UBBSetJobCommandStub::GetNumExecutions() const
{
	return Executions;
}