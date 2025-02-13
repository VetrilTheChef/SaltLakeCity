// SaltLakeCity 4.27

#include "BBJobModelStub.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"
#include "Engine/DataTable.h"
#include "GUI/Data/BBJobRow.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Widgets/Interfaces/IBBJobWidget.h"

UBBJobModelStub::UBBJobModelStub() :
	Super()
{
	View = nullptr;
	HUD = nullptr;

	WorkComponent = nullptr;
	WidgetSpecification = nullptr;
	Target = TScriptInterface<IBBWidgetTarget>();
	CurrentJob = EBBJob::None;
	Jobs.Empty();
	DisplayName = FText::FromString("");
}

TScriptInterface<IBBWidgetTarget> UBBJobModelStub::GetWidgetTarget() const
{
	return Target;
}

void UBBJobModelStub::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewTarget)
{
	Target = NewTarget;
}

UIBBWidget * UBBJobModelStub::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBJobModelStub::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return WidgetSpecification;
}

void UBBJobModelStub::SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification)
{
	WidgetSpecification = NewWidgetSpecification;
}

UDataTable * UBBJobModelStub::GetDataTable() const
{
	return nullptr;
}

void UBBJobModelStub::Initialize(UIBBJobWidget * NewView, AIBBHUD * NewHUD, UDataTable * Table)
{
	View = NewView;
	HUD = NewHUD;

	if (IsValid(HUD))
	{
		HUD->OnConsumerUpdate().AddUObject(this, & UBBJobModelStub::UpdateConsumer);
	}
}

void UBBJobModelStub::Finalize()
{
	if (IsValid(HUD))
	{
		HUD->OnConsumerUpdate().RemoveAll(this);
	}

	HUD = nullptr;
	View = nullptr;
}

void UBBJobModelStub::AddJob(FText NewName, FText NewTooltip, EBBJob NewJob)
{
	Jobs.Emplace(FBBJobRow(NewName, NewTooltip, NewJob));
}

int UBBJobModelStub::GetNumJobs() const
{
	return Jobs.Num();
}

EBBJob UBBJobModelStub::GetJob(int Index) const
{
	if (Jobs.IsValidIndex(Index))
	{
		return Jobs[Index].Job;
	}

	return EBBJob::None;
}

const FText UBBJobModelStub::GetJobName(int Index) const
{
	if (Jobs.IsValidIndex(Index))
	{
		return Jobs[Index].Name;
	}

	return FText::FromString("");
}

const FText UBBJobModelStub::GetJobTooltip(int Index) const
{
	if (Jobs.IsValidIndex(Index))
	{
		return Jobs[Index].Tooltip;
	}

	return FText::FromString("");
}

UIBBWorkComponent * UBBJobModelStub::GetWorkComponent() const
{
	return WorkComponent;
}

void UBBJobModelStub::SetWorkComponent(UIBBWorkComponent * NewWorkComponent)
{
	WorkComponent = NewWorkComponent;
}

const FText UBBJobModelStub::GetDisplayName() const
{
	return DisplayName;
}

void UBBJobModelStub::SetDisplayName(FText NewDisplayName)
{
	DisplayName = NewDisplayName;
}

EBBJob UBBJobModelStub::GetCurrentJob() const
{
	return CurrentJob;
}

void UBBJobModelStub::SetCurrentJob(EBBJob NewCurrentJob)
{
	CurrentJob = NewCurrentJob;
}

const FText UBBJobModelStub::FindJobName(EBBJob JobType)
{
	for (FBBJobRow & Job : Jobs)
	{
		if (Job.Job == JobType)
			return Job.Name;
	}

	return FText::FromString("");
}

void UBBJobModelStub::BroadcastConsumerUpdate(UIBBWorkComponent * NewWorkComponent)
{
	UpdateConsumer(NewWorkComponent);
}


void UBBJobModelStub::UpdateConsumer(UIBBWorkComponent * NewWorkComponent)
{
	WorkComponent = NewWorkComponent;

	OnTargetUpdate().Broadcast(GetWidgetTarget());
	OnConsumerUpdate().Broadcast();
}