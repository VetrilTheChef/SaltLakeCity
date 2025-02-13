// SaltLakeCity 4.27

#include "BBJobWidgetStub.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/BBTitleWidgetStub.h"

UBBJobWidgetStub::UBBJobWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	DisplayName = FText::FromString("");

	SelectedJob = EBBJob::None;

	Jobs.Empty();

	Title = nullptr;

	AcceptCommand = nullptr;
	CancelCommand = nullptr;
}

void UBBJobWidgetStub::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBBJobWidgetStub::BeginDestroy()
{
	if (IsValid(Title))
	{
		Title->MarkPendingKill();
	}

	Title = nullptr;

	Super::BeginDestroy();
}

EBBWidget UBBJobWidgetStub::GetType() const
{
	return EBBWidget::Job;
}

FText UBBJobWidgetStub::GetDisplayName()
{
	return DisplayName;
}

void UBBJobWidgetStub::SetDisplayName(FText NewDisplayName)
{
	DisplayName = NewDisplayName;
}

void UBBJobWidgetStub::AddJob(EBBJob Job, FText NewJobName, FText NewJobTooltip)
{
	FString NewJobNameString = NewJobName.ToString();

	Jobs.Emplace(FBBJob(Job, NewJobName, NewJobTooltip));
}

int UBBJobWidgetStub::GetNumJobs()
{
	return Jobs.Num();
}

EBBJob UBBJobWidgetStub::GetJob(int Index)
{
	return Jobs.IsValidIndex(Index) ? Jobs[Index].Job : EBBJob::None;
}

FText UBBJobWidgetStub::GetJobName(int Index)
{
	return Jobs.IsValidIndex(Index) ? Jobs[Index].Name : FText::FromString("");
}

FText UBBJobWidgetStub::GetJobTooltip(int Index)
{
	return Jobs.IsValidIndex(Index) ? Jobs[Index].Tooltip : FText::FromString("");
}

void UBBJobWidgetStub::ClearJobs()
{
	Jobs.Empty();
}

EBBJob UBBJobWidgetStub::GetJob()
{
	return SelectedJob;
}

void UBBJobWidgetStub::SetJob(EBBJob Job)
{
	SelectedJob = Job;

	OnJobUpdate().Broadcast(SelectedJob);
}

FText UBBJobWidgetStub::GetSelectedJobName()
{
	for (FBBJob & Job : Jobs)
	{
		if (Job.Job == SelectedJob)
			return Job.Name;
	}

	return FText::FromString("");
}

UIBBTitleWidget * & UBBJobWidgetStub::GetTitle()
{
	return Title;
}

UIBBCommand * UBBJobWidgetStub::GetAcceptCommand()
{
	return AcceptCommand;
}

void UBBJobWidgetStub::SetAcceptCommand(UIBBCommand * NewAcceptCommand)
{
	AcceptCommand = NewAcceptCommand;
}

UIBBCommand * UBBJobWidgetStub::GetCancelCommand()
{
	return CancelCommand;
}

void UBBJobWidgetStub::SetCancelCommand(UIBBCommand * NewCancelCommand)
{
	CancelCommand = NewCancelCommand;
}