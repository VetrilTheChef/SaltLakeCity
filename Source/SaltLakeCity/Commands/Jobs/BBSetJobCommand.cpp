// SaltLakeCity 4.27

#include "BBSetJobCommand.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"

UBBSetJobCommand::UBBSetJobCommand() :
	Super()
{
	WorkComponent = nullptr;
	Job = EBBJob::None;
}

UIBBWorkComponent * UBBSetJobCommand::GetWorkComponent() const
{
	return WorkComponent;
}

void UBBSetJobCommand::SetWorkComponent(UIBBWorkComponent * NewWorkComponent)
{
	WorkComponent = NewWorkComponent;
}

EBBJob UBBSetJobCommand::GetJob() const
{
	return Job;
}

void UBBSetJobCommand::SetJob(EBBJob NewJob)
{
	Job = NewJob;
}

void UBBSetJobCommand::Execute()
{
	verifyf(IsValid(WorkComponent), TEXT("Work Component is invalid."));

	WorkComponent->SetJob(Job);
}