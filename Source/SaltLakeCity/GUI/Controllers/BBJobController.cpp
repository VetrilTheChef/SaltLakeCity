// SaltLakeCity 4.27

#include "BBJobController.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Commands/GUI/Interfaces/IBBCloseWidgetCommand.h"
#include "Commands/Jobs/Interfaces/IBBSetJobCommand.h"
#include "Commands/Metacommands/Interfaces/IBBCompositeCommand.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Models/Interfaces/IBBJobModel.h"
#include "GUI/Widgets/Interfaces/IBBJobWidget.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBJobController::UBBJobController() :
	Super()
{
	Model = nullptr;
	View = nullptr;
	SetJobCommand = nullptr;
}

void UBBJobController::Initialize(UIBBJobWidget * JobView, UIBBJobModel * JobModel, const UIBBWidgetFactory * WidgetFactory, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory)
{
	InitializeModel(JobModel);
	InitializeView(JobView, JobModel, WidgetFactory, WidgetSpecificationFactory, CommandFactory);
}

void UBBJobController::Finalize()
{
	FinalizeModel();
	FinalizeView();
}



void UBBJobController::InitializeModel(UIBBJobModel * JobModel)
{
	verifyf(IsValid(JobModel), TEXT("Job Model is invalid."));

	FinalizeModel();

	Model = JobModel;

	Model->OnConsumerUpdate().AddUObject(this, & UBBJobController::UpdateConsumer);
}

void UBBJobController::FinalizeModel()
{
	if (IsValid(Model))
	{
		Model->OnConsumerUpdate().RemoveAll(this);
	}

	Model = nullptr;
}

void UBBJobController::InitializeView(UIBBJobWidget * JobView, UIBBJobModel * JobModel, const UIBBWidgetFactory * WidgetFactory, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory)
{
	FinalizeView();

	View = JobView;

	verifyf(IsValid(View), TEXT("Job View is invalid."));

	View->OnJobUpdate().AddUObject(this, & UBBJobController::SetJob);

	verifyf(IsValid(JobModel), TEXT("Job Model is invalid."));
	verifyf(IsValid(WidgetFactory), TEXT("Widget Factory is invalid."));
	verifyf(IsValid(CommandFactory), TEXT("Command Factory is invalid."));

	CreateTitle(* View, JobModel, * WidgetFactory);
	CreateCommands(* View, * Model, WidgetSpecificationFactory, * CommandFactory);
	AddJobs(* View, * JobModel);
}

void UBBJobController::FinalizeView()
{
	if (IsValid(View))
	{
		ClearJobs(* View);
		DestroyCommands(* View);
		DestroyTitle(* View);

		View->OnJobUpdate().RemoveAll(this);

		View->MarkPendingKill();
	}

	View = nullptr;
}

void UBBJobController::CreateTitle(UIBBJobWidget & JobView, UIBBJobModel * JobModel, const UIBBWidgetFactory & WidgetFactory)
{
	WidgetFactory.NewTitleWidget(JobView.GetTitle(), JobModel);

	verifyf(IsValid(JobView.GetTitle()), TEXT("Title Widget is invalid."));
}

void UBBJobController::DestroyTitle(UIBBJobWidget & JobView)
{
	UIBBTitleWidget * TitleWidget = JobView.GetTitle();

	if (IsValid(TitleWidget))
	{
		TitleWidget->MarkPendingKill();
	}
}

void UBBJobController::CreateCommands(UIBBJobWidget & JobView, UIBBJobModel & JobModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory & CommandFactory)
{
	UIBBCompositeCommand * CompositeCommand = nullptr;

	CommandFactory.NewCompositeCommand(CompositeCommand, this);

	verifyf(IsValid(CompositeCommand), TEXT("Composite Command is invalid."));
	
	CommandFactory.NewSetJobCommand(SetJobCommand, this, JobModel.GetWorkComponent(), EBBJob::None);

	verifyf(IsValid(SetJobCommand), TEXT("Set Work Command is invalid."));
	
	CompositeCommand->Add(SetJobCommand);

	UIBBWidgetSpecification * CloseSpecification = JobModel.GetWidgetSpecification(WidgetSpecificationFactory);

	UIBBCloseWidgetCommand * CloseCommand = nullptr;

	CommandFactory.NewCloseWidgetCommand(CloseCommand, this, CloseSpecification);

	verifyf(IsValid(CloseCommand), TEXT("Close Command is invalid."));

	CompositeCommand->Add(CloseCommand);

	JobView.SetAcceptCommand(CompositeCommand);
	JobView.SetCancelCommand(CloseCommand);
}

void UBBJobController::DestroyCommands(UIBBJobWidget & JobView)
{
	JobView.SetAcceptCommand(nullptr);
	JobView.SetCancelCommand(nullptr);

	if (IsValid(SetJobCommand))
	{
		SetJobCommand->MarkPendingKill();
	}

	SetJobCommand = nullptr;
}

void UBBJobController::AddJobs(UIBBJobWidget & JobView, UIBBJobModel & JobModel)
{
	for (int Index = 0; Index < JobModel.GetNumJobs(); Index++)
	{
		JobView.AddJob(JobModel.GetJob(Index), JobModel.GetJobName(Index), JobModel.GetJobTooltip(Index));
	}
}

void UBBJobController::ClearJobs(UIBBJobWidget & JobView)
{
	JobView.ClearJobs();
}

void UBBJobController::UpdateConsumer()
{
	verifyf(IsValid(Model), TEXT("Job Model is invalid."));
	verifyf(IsValid(View), TEXT("Job View is invalid."));
	verifyf(IsValid(SetJobCommand), TEXT("Set Job Command is invalid."));

	EBBJob Job = Model->GetCurrentJob();

	View->SetDisplayName(Model->GetDisplayName());
	View->SetJob(Job);

	SetJobCommand->SetWorkComponent(Model->GetWorkComponent());
	SetJobCommand->SetJob(Job);
}

void UBBJobController::SetJob(EBBJob Job)
{
	verifyf(IsValid(SetJobCommand), TEXT("Set Work Command is invalid."));

	SetJobCommand->SetJob(Job);
}