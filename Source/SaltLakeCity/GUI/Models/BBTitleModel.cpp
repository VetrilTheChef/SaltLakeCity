// SaltLakeCity 5.7

#include "BBTitleModel.h"
#include "GUI/BBUIStatics.h"
#include "GUI/Interfaces/IBBWidgetTarget.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBTitleModel::UBBTitleModel() :
	Super()
{
	View = nullptr;
	ParentModel = nullptr;
}

TScriptInterface<IBBWidgetTarget> UBBTitleModel::GetWidgetTarget() const
{
	return TScriptInterface<IBBWidgetTarget>(ParentModel->GetWidget());
}

UIBBWidget* UBBTitleModel::GetWidget() const
{
	return GetParentModelChecked()->GetWidget();
}

UIBBWidgetSpecification* UBBTitleModel::GetWidgetSpecification(
	const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory
)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	UIBBTargetedWidgetSpecification * TitleWidgetSpecification = nullptr;

	WidgetSpecificationFactory->NewTitleWidgetSpecification(TitleWidgetSpecification, this, GetParentModelChecked());

	verifyf(IsValid(TitleWidgetSpecification), TEXT("Title Widget Specification is invalid."));

	TitleWidgetSpecification->SetWidgetTarget(GetWidgetTarget());

	OnTargetUpdate().AddUObject(TitleWidgetSpecification, &UIBBTargetedWidgetSpecification::SetWidgetTarget);

	return TitleWidgetSpecification;
}

void UBBTitleModel::Initialize(UIBBTitleWidget* NewView, UIBBGUIModel* NewParentModel)
{
	InitializeView(NewView);
	InitializeParentModel(NewParentModel);
}

void UBBTitleModel::Finalize()
{
	FinalizeParentModel();
	FinalizeView();
}



void UBBTitleModel::InitializeView(UIBBTitleWidget* NewView)
{
	FinalizeView();

	SetTitleViewChecked(NewView);
}

void UBBTitleModel::InitializeParentModel(UIBBGUIModel* NewParentModel)
{
	FinalizeParentModel();

	SetParentModelChecked(NewParentModel);

	OnTargetUpdate().Broadcast(TScriptInterface<IBBWidgetTarget>(GetParentWidget()));
}

void UBBTitleModel::FinalizeView()
{
	if (View.IsValid())
	{
	}

	View = nullptr;
}

void UBBTitleModel::FinalizeParentModel()
{
	if (ParentModel.IsValid())
	{
	}

	ParentModel = nullptr;

	OnTargetUpdate().Broadcast(TScriptInterface<IBBWidgetTarget>(nullptr));
}

UIBBTitleWidget* UBBTitleModel::GetTitleViewChecked() const
{
	verifyf(View.IsValid(), TEXT("View is invalid."));

	return View.Get();
}

void UBBTitleModel::SetTitleViewChecked(UIBBTitleWidget* NewView)
{
	verifyf(IsValid(NewView), TEXT("New View is invalid."));

	View = NewView;
}

UIBBGUIModel* UBBTitleModel::GetParentModelChecked() const
{
	verifyf(ParentModel.IsValid(), TEXT("Parent Model is invalid."));

	return ParentModel.Get();
}

void UBBTitleModel::SetParentModelChecked(UIBBGUIModel* NewParentModel)
{
	verifyf(IsValid(NewParentModel), TEXT("New Parent Model is invalid."));

	ParentModel = NewParentModel;
}

void UBBTitleModel::SetPosition(FVector2D NewPosition)
{
	UIBBWidget* ParentWidget= GetParentWidget();

	verifyf(IsValid(ParentWidget), TEXT("Parent Widget is invalid."));

	UBBUIStatics::ConvertToPIEViewportSpace(GetWorld(), NewPosition);

	ParentWidget->SetPositionInViewport(NewPosition);
}

UIBBWidget * UBBTitleModel::GetParentWidget() const
{
	verifyf(ParentModel.IsValid(), TEXT("Parent Model is invalid."));

	return ParentModel.Get()->GetWidget();
}

UIBBWidgetSpecification * UBBTitleModel::GetParentWidgetSpecification(
	const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory
)
{
	verifyf(ParentModel.IsValid(), TEXT("Parent Model is invalid."));

	return ParentModel->GetWidgetSpecification(WidgetSpecificationFactory);
}