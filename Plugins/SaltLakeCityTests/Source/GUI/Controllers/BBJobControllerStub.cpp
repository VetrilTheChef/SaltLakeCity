// SaltLakeCity 4.27

#include "BBJobControllerStub.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Actors/Interfaces/IBBWorkable.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Commands/GUI/Interfaces/IBBCloseWidgetCommand.h"
#include "Commands/Jobs/Interfaces/IBBSetJobCommand.h"
#include "Commands/Metacommands/Interfaces/IBBCompositeCommand.h"
#include "GUI/Models/Interfaces/IBBJobModel.h"
#include "GUI/Widgets/Interfaces/IBBJobWidget.h"

UBBJobControllerStub::UBBJobControllerStub() :
	Super()
{
	Model = nullptr;
	View = nullptr;

	WorkComponent = nullptr;
	AcceptCommand = nullptr;
	CancelCommand = nullptr;
}

void UBBJobControllerStub::Initialize(UIBBJobWidget * JobView, UIBBJobModel * JobModel, const UIBBWidgetFactory * WidgetFactory, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory)
{
	InitializeModel(JobModel);
	InitializeView(JobView);
}

void UBBJobControllerStub::Finalize()
{
	FinalizeModel();
	FinalizeView();
}

void UBBJobControllerStub::SetViewCommands(UIBBCompositeCommand * NewAcceptCommand, UIBBCloseWidgetCommand * NewCancelCommand)
{
	AcceptCommand = NewAcceptCommand;
	CancelCommand = NewCancelCommand;
}

UIBBWorkComponent * UBBJobControllerStub::GetWorkComponent()
{
	return WorkComponent;
}

void UBBJobControllerStub::SetWorkComponent(UIBBWorkComponent * NewWorkComponent)
{
	WorkComponent = NewWorkComponent;
}



void UBBJobControllerStub::InitializeModel(UIBBJobModel * JobModel)
{
	Model = JobModel;

	if (IsValid(Model))
	{
		Model->OnConsumerUpdate().AddUObject(this, & UBBJobControllerStub::UpdateConsumer);
	}
}

void UBBJobControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
		Model->OnConsumerUpdate().RemoveAll(this);
	}

	Model = nullptr;
}

void UBBJobControllerStub::InitializeView(UIBBJobWidget * JobView)
{
	View = JobView;

	if (IsValid(View))
	{
		View->SetAcceptCommand(AcceptCommand);
		View->SetCancelCommand(CancelCommand);
	}
}

void UBBJobControllerStub::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBJobControllerStub::UpdateConsumer()
{
	if (IsValid(View) && IsValid(Model))
	{
		View->SetDisplayName(Model->GetDisplayName());
		View->SetJob(Model->GetCurrentJob());
	}
}