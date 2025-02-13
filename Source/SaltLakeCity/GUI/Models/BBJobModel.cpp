// SaltLakeCity 4.27

#include "BBJobModel.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"
#include "Engine/DataTable.h"
#include "GUI/Data/BBJobRow.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI//Interfaces/IBBWidgetTarget.h"
#include "GUI/Widgets/Interfaces/IBBJobWidget.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBJobModel::UBBJobModel() :
	Super()
{
	View = nullptr;
	HUD = nullptr;
	Component = nullptr;
	Jobs.Empty();
}

TScriptInterface<IBBWidgetTarget> UBBJobModel::GetWidgetTarget() const
{
	return TScriptInterface<IBBWidgetTarget>(nullptr);
}

UIBBWidget * UBBJobModel::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBJobModel::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	UIBBTargetedWidgetSpecification * JobWidgetSpecification = nullptr;

	WidgetSpecificationFactory->NewJobWidgetSpecification(JobWidgetSpecification, this, GetWidgetTarget());

	verifyf(IsValid(JobWidgetSpecification), TEXT("Job Widget Specification is invalid."));

	OnTargetUpdate().AddUObject(JobWidgetSpecification, & UIBBTargetedWidgetSpecification::SetWidgetTarget);

	return JobWidgetSpecification;
}

UDataTable * UBBJobModel::GetDataTable() const
{
	return TableAsset.LoadSynchronous();
}

void UBBJobModel::Initialize(UIBBJobWidget * NewView, AIBBHUD * NewHUD, UDataTable * Table)
{
	InitializeView(NewView);
	InitializeJobs(Table);
	InitializeHUD(NewHUD);
}

void UBBJobModel::Finalize()
{
	FinalizeHUD();
	FinalizeJobs();
	FinalizeView();
}

int UBBJobModel::GetNumJobs() const
{
	return Jobs.Num();
}

EBBJob UBBJobModel::GetJob(int Index) const
{
	if (Jobs.IsValidIndex(Index))
	{
		return Jobs[Index].Job;
	}

	return EBBJob::None;
}

const FText UBBJobModel::GetJobName(int Index) const
{
	if (Jobs.IsValidIndex(Index))
	{
		return Jobs[Index].Name;
	}

	return FText::FromString("");
}

const FText UBBJobModel::GetJobTooltip(int Index) const
{
	if (Jobs.IsValidIndex(Index))
	{
		return Jobs[Index].Tooltip;
	}

	return FText::FromString("");
}


UIBBWorkComponent * UBBJobModel::GetWorkComponent() const
{
	return Component;
}

const FText UBBJobModel::GetDisplayName() const
{
	verifyf(IsValid(Component), TEXT("Component is invalid."));

	TScriptInterface<IBBWidgetTarget> WidgetTarget = Component->GetWidgetTarget();

	verifyf(IsValid(WidgetTarget.GetObject()), TEXT("Widget Target is invalid."));

	return WidgetTarget->GetDisplayName(EBBDisplayName::Full);
}

EBBJob UBBJobModel::GetCurrentJob() const
{
	verifyf(IsValid(Component), TEXT("Component is invalid."));

	return Component->GetJob();
}



void UBBJobModel::InitializeView(UIBBJobWidget * NewView)
{
	FinalizeView();

	verifyf(IsValid(NewView), TEXT("New Job View is invalid."));

	View = NewView;
}

void UBBJobModel::InitializeJobs(UDataTable * Table)
{
	verifyf(IsValid(Table), TEXT("Job Data Table is invalid."));

	Jobs.Empty();

	for (const TPair<FName, uint8 *> & Iterator : Table->GetRowMap())
	{
		FBBJobRow * Row = (FBBJobRow *)Iterator.Value;

		Jobs.Add(FBBJobRow(* Row));
	}
}

void UBBJobModel::InitializeHUD(AIBBHUD * NewHUD)
{
	HUD = NewHUD;

	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	HUD->OnConsumerUpdate().AddUObject(this, & UBBJobModel::UpdateComponent);
}

void UBBJobModel::InitializeComponent(UIBBWorkComponent * NewWorkComponent)
{
	FinalizeComponent();

	Component = NewWorkComponent;

	OnTargetUpdate().Broadcast(GetWidgetTarget());
	OnConsumerUpdate().Broadcast();
}

void UBBJobModel::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBJobModel::FinalizeJobs()
{
	Jobs.Empty();
}

void UBBJobModel::FinalizeHUD()
{
	if (IsValid(HUD))
	{
		HUD->OnConsumerUpdate().RemoveAll(this);
	}

	HUD = nullptr;
}

void UBBJobModel::FinalizeComponent()
{
	if (IsValid(Component))
	{
	}

	Component = nullptr;
}

void UBBJobModel::UpdateComponent(UIBBWorkComponent * NewWorkComponent)
{
	verifyf(IsValid(NewWorkComponent), TEXT("New Work Component is invalid."));

	InitializeComponent(NewWorkComponent);
}