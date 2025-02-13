// SaltLakeCity 4.26

#include "BBTitleController.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Commands/GUI/Interfaces/IBBCloseWidgetCommand.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Models/Interfaces/IBBTitleModel.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"

UBBTitleController::UBBTitleController() :
	Super()
{
	Model = nullptr;
	View = nullptr;

	CloseSpecification = nullptr;
	CloseCommand = nullptr;
}

void UBBTitleController::Initialize(UIBBTitleWidget * TitleView, UIBBTitleModel * TitleModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory)
{
	InitializeModel(TitleModel);
	InitializeView(TitleView, * TitleModel, WidgetSpecificationFactory, CommandFactory);
}

void UBBTitleController::Finalize()
{
	FinalizeModel();
	FinalizeView();
}



void UBBTitleController::GetPosition(FVector2D NewPosition)
{
	verifyf(IsValid(Model), TEXT("Title Model is invalid."));
	
	Model->SetPosition(NewPosition);
}

void UBBTitleController::GetParentWidget(UIBBWidget * & NewWidget)
{
	verifyf(IsValid(Model), TEXT("Title Model is invalid."));

	NewWidget = Model->GetParentWidget();
}

void UBBTitleController::InitializeModel(UIBBTitleModel * TitleModel)
{
	FinalizeModel();

	verifyf(IsValid(TitleModel), TEXT("Title Model is invalid."));

	Model = TitleModel;
}

void UBBTitleController::FinalizeModel()
{
	Model = nullptr;
}

void UBBTitleController::InitializeView(UIBBTitleWidget * TitleView, UIBBTitleModel & TitleModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory)
{
	FinalizeView();

	View = TitleView;

	verifyf(IsValid(View), TEXT("Title View is invalid."));

	View->OnDragged.AddDynamic(this, &UBBTitleController::GetPosition);
	View->OnDragDetected.AddDynamic(this, &UBBTitleController::GetParentWidget);

	verifyf(IsValid(CommandFactory), TEXT("Command Factory is invalid."));

	CreateCommands(* View, TitleModel, WidgetSpecificationFactory, * CommandFactory);
}

void UBBTitleController::FinalizeView()
{
	if (IsValid(View))
	{
		View->OnDragged.RemoveDynamic(this, &UBBTitleController::GetPosition);
		View->OnDragDetected.RemoveDynamic(this, &UBBTitleController::GetParentWidget);
	}

	View = nullptr;
}

void UBBTitleController::CreateCommands(UIBBTitleWidget & TitleView, UIBBTitleModel & TitleModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory & CommandFactory)
{
	CreateCloseCommand(TitleView, TitleModel, WidgetSpecificationFactory, CommandFactory);
}

void UBBTitleController::CreateCloseCommand(UIBBTitleWidget & TitleView, UIBBTitleModel & TitleModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory & CommandFactory)
{
	CloseSpecification = TitleModel.GetParentWidgetSpecification(WidgetSpecificationFactory);

	if (CommandFactory.NewCloseWidgetCommand(CloseCommand, this, CloseSpecification))
	{
		TitleView.SetCloseCommand(CloseCommand);
	}
}

void UBBTitleController::DestroyCommands()
{
	DestroyCloseCommand();
}

void UBBTitleController::DestroyCloseCommand()
{
	if (IsValid(CloseCommand))
	{
		CloseCommand->MarkPendingKill();
	}

	CloseCommand = nullptr;

	if (IsValid(CloseSpecification))
	{
		CloseSpecification->MarkPendingKill();
	}

	CloseSpecification = nullptr;
}