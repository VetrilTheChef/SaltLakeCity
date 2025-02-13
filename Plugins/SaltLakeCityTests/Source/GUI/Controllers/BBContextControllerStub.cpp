// SaltLakeCity 4.26

#include "BBContextControllerStub.h"
#include "GUI/Models/Interfaces/IBBContextModel.h"
#include "GUI/Widgets/Interfaces/IBBContextRowWidget.h"
#include "GUI/Widgets/Interfaces/IBBContextWidget.h"

UBBContextControllerStub::UBBContextControllerStub() :
	Super()
{
	Model = nullptr;
	View = nullptr;
	RowWidgets.Empty();

	OnMouseLeaveCalls = 0;
	OnRowClickCalls = 0;
}

void UBBContextControllerStub::Initialize(UIBBContextWidget * ContextView, UIBBContextModel * ContextModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory)
{
	InitializeModel(ContextModel);
	InitializeView(ContextView);
}

void UBBContextControllerStub::Finalize()
{
	FinalizeView();
	FinalizeModel();
}

void UBBContextControllerStub::AddRow(UIBBContextRowWidget * NewRowWidget)
{
	if (IsValid(NewRowWidget))
	{
		NewRowWidget->OnClicked().AddUObject(this, &UBBContextControllerStub::ClickRow);

		if (IsValid(View))
		{
			View->AddRow(NewRowWidget);
		}
	}
}

void UBBContextControllerStub::ClearRows()
{
	for (UIBBContextRowWidget * & RowWidget : RowWidgets)
	{
		if (IsValid(RowWidget))
		{
			RowWidget->OnClicked().RemoveAll(this);
		}
	}

	if (IsValid(View))
	{
		View->ClearRows();
	}

	RowWidgets.Empty();
}

int UBBContextControllerStub::GetNumMouseLeaveExecutions()
{
	return OnMouseLeaveCalls;
}

int UBBContextControllerStub::GetNumRowClickExecutions()
{
	return OnRowClickCalls;
}



void UBBContextControllerStub::InitializeModel(UIBBContextModel * ContextModel)
{
	Model = ContextModel;
}

void UBBContextControllerStub::InitializeView(UIBBContextWidget * ContextView)
{
	View = ContextView;

	if (IsValid(View))
	{
		View->OnMouseLeave().AddUObject(this, &UBBContextControllerStub::LeaveMouse);
	}
}

void UBBContextControllerStub::FinalizeModel()
{
	Model = nullptr;
}

void UBBContextControllerStub::FinalizeView()
{
	ClearRows();

	if (IsValid(View))
	{
		View->OnMouseLeave().RemoveAll(this);
	}

	View = nullptr;
}

void UBBContextControllerStub::LeaveMouse(const FPointerEvent & MouseEvent)
{
	OnMouseLeaveCalls++;
}

void UBBContextControllerStub::ClickRow()
{
	OnRowClickCalls++;
}