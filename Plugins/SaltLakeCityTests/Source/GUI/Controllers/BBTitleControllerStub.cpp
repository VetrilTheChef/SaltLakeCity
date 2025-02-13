// SaltLakeCity 4.26

#include "BBTitleControllerStub.h"
#include "Commands/GUI/Interfaces/IBBCloseWidgetCommand.h"
#include "GUI/Models/Interfaces/IBBTitleModel.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"

UBBTitleControllerStub::UBBTitleControllerStub() :
	Super()
{
	Model = nullptr;
	View = nullptr;

	CloseCommand = nullptr;

	Position = FVector2D::ZeroVector;

	ParentWidget = nullptr;
}

void UBBTitleControllerStub::Initialize(UIBBTitleWidget * TitleView, UIBBTitleModel * TitleModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory)
{
	InitializeModel(TitleModel);
	InitializeView(TitleView);
}

void UBBTitleControllerStub::Finalize()
{
	FinalizeModel();
	FinalizeView();
}

void UBBTitleControllerStub::SetViewCommands(UIBBCloseWidgetCommand * NewCloseCommand)
{
	CloseCommand = NewCloseCommand;
}

void UBBTitleControllerStub::SetPosition(FVector2D NewPosition)
{
	Position = NewPosition;
}



void UBBTitleControllerStub::GetPosition(FVector2D NewPosition)
{
	Model->SetPosition(NewPosition);
}

void UBBTitleControllerStub::GetParentWidget(UIBBWidget * & NewWidget)
{
	NewWidget = IsValid(Model) ? Model->GetParentWidget() : nullptr;
}

void UBBTitleControllerStub::InitializeModel(UIBBTitleModel * TitleModel)
{
	FinalizeModel();

	Model = TitleModel;
}

void UBBTitleControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}

void UBBTitleControllerStub::InitializeView(UIBBTitleWidget * TitleView)
{
	FinalizeView();

	View = TitleView;

	if (IsValid(View))
	{
		View->OnDragged.AddDynamic(this, &UBBTitleControllerStub::GetPosition);
		View->OnDragDetected.AddDynamic(this, &UBBTitleControllerStub::GetParentWidget);

		View->SetCloseCommand(CloseCommand);
	}
}

void UBBTitleControllerStub::FinalizeView()
{
	if (IsValid(View))
	{
		View->OnDragged.RemoveDynamic(this, &UBBTitleControllerStub::GetPosition);
		View->OnDragDetected.RemoveDynamic(this, &UBBTitleControllerStub::GetParentWidget);
	}

	View = nullptr;
}