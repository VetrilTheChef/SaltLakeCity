// SaltLakeCity 5.7

#include "BBContextController.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Commands/GUI/Interfaces/IBBOpenWidgetCommand.h"
#include "GUI/Models/Interfaces/IBBContextModel.h"
#include "GUI/Widgets/Interfaces/IBBContextRowWidget.h"
#include "GUI/Widgets/Interfaces/IBBContextWidget.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBContextController::UBBContextController() :
	Super()
{
	Model = nullptr;
	View = nullptr;
}

void UBBContextController::Initialize(
	UIBBContextWidget* ContextView,
	UIBBContextModel* ContextModel,
	const UIBBWidgetSpecificationFactory* WidgetSpecificationFactory,
	const UIBBCommandFactory* CommandFactory
)
{
	InitializeModel(ContextModel);
	InitializeView(ContextView, *ContextModel, WidgetSpecificationFactory, CommandFactory);
}

void UBBContextController::Finalize()
{
	FinalizeModel();
	FinalizeView();
}



void UBBContextController::InitializeModel(UIBBContextModel* ContextModel)
{
	FinalizeModel();

	verifyf(IsValid(ContextModel), TEXT("Context Model is invalid."));

	Model = ContextModel;

	Model->OnContextUpdate().AddUObject(this, &UBBContextController::UpdateContext);
}

void UBBContextController::FinalizeModel()
{
	if (IsValid(Model))
	{
		Model->OnContextUpdate().RemoveAll(this);
	}

	Model = nullptr;
}

void UBBContextController::InitializeView(
	UIBBContextWidget* ContextView,
	UIBBContextModel& ContextModel,
	const UIBBWidgetSpecificationFactory* WidgetSpecificationFactory,
	const UIBBCommandFactory* CommandFactory
)
{
	FinalizeView();

	verifyf(IsValid(ContextView), TEXT("Context View is invalid."));

	View = ContextView;

	View->OnMouseLeave().AddUObject(this, &UBBContextController::LeaveMouse);

	verifyf(IsValid(CommandFactory), TEXT("Command Factory is invalid."));

	CreateRows(*View, ContextModel, WidgetSpecificationFactory, *CommandFactory);
}

void UBBContextController::FinalizeView()
{
	if (IsValid(View))
	{
		View->OnMouseLeave().RemoveAll(this);

		DestroyRows(*View);

		View->MarkAsGarbage();
	}

	View = nullptr;
}

void UBBContextController::CreateRows(
	UIBBContextWidget& ContextView,
	UIBBContextModel& ContextModel,
	const UIBBWidgetSpecificationFactory* WidgetSpecificationFactory,
	const UIBBCommandFactory& CommandFactory
)
{
	int Rows = ContextModel.GetNumRows();

	for (int RowIndex = 0; RowIndex < Rows; RowIndex++)
	{
		FBBContextRowData RowData = ContextModel.GetRowData(RowIndex);
		
		UIBBContextRowWidget* RowWidget = CreateWidget<UIBBContextRowWidget>(
			&ContextView,
			ContextView.GetRowWidgetClass().LoadSynchronous()
		);

		verifyf(IsValid(RowWidget), TEXT("Row Widget is invalid."));

		UIBBOpenWidgetCommand* RowCommand = nullptr;

		CommandFactory.NewOpenWidgetCommand(
			RowCommand,
			RowWidget,
			ContextModel.GetRowWidgetSpecification(WidgetSpecificationFactory, RowIndex),
			true
		);

		verifyf(IsValid(RowCommand), TEXT("Row Command is invalid."));

		RowWidget->SetRowName(RowData.Name);
		RowWidget->SetRowIcon(RowData.Icon);
		RowWidget->SetRowTooltip(RowData.Tooltip);
		RowWidget->SetCommand(RowCommand);

		RowWidget->OnClicked().AddUObject(this, &UBBContextController::ClickRow);

		RowWidgets.Emplace(RowWidget, RowData.ContextType);

		ContextView.AddRow(RowWidget);
	}
}

void UBBContextController::DestroyRows(UIBBContextWidget& ContextView)
{
	ContextView.ClearRows();

	for (TPair<UIBBContextRowWidget*, EBBContext>& RowWidget : RowWidgets)
	{
		if (IsValid(RowWidget.Key))
		{
			RowWidget.Key->OnClicked().RemoveAll(this);

			RowWidget.Key->MarkAsGarbage();
		}
	}

	RowWidgets.Empty();
}

void UBBContextController::UpdateContext()
{
	verifyf(IsValid(Model), TEXT("Context Model is invalid."));

	for (TPair<UIBBContextRowWidget*, EBBContext>& RowWidget : RowWidgets)
	{
		verifyf(IsValid(RowWidget.Key), TEXT("Row Widget is invalid."));

		RowWidget.Key->SetVisibility(Model->GetRowVisibility(RowWidget.Value) ?
			ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UBBContextController::LeaveMouse(const FPointerEvent & MouseEvent)
{
	CloseView();
}

void UBBContextController::ClickRow()
{
	CloseView();
}

void UBBContextController::CloseView()
{
	verifyf(IsValid(View), TEXT("Context View is invalid."));

	View->RemoveFromParent();
}