// SaltLakeCity 4.27

#include "BBTitleModel.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Interfaces/IBBWidgetTarget.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBTitleModel::UBBTitleModel() :
	Super()
{
	View = nullptr;
	ParentModel = nullptr;
	HUD = nullptr;
}

TScriptInterface<IBBWidgetTarget> UBBTitleModel::GetWidgetTarget() const
{
	return TScriptInterface<IBBWidgetTarget>(ParentModel->GetWidget());
}

UIBBWidget * UBBTitleModel::GetWidget() const
{
	return ParentModel->GetWidget();
}

UIBBWidgetSpecification * UBBTitleModel::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	UIBBTargetedWidgetSpecification * TitleWidgetSpecification = nullptr;

	WidgetSpecificationFactory->NewTitleWidgetSpecification(TitleWidgetSpecification, this, ParentModel);

	verifyf(IsValid(TitleWidgetSpecification), TEXT("Title Widget Specification is invalid."));

	TitleWidgetSpecification->SetWidgetTarget(GetWidgetTarget());

	OnTargetUpdate().AddUObject(TitleWidgetSpecification, & UIBBTargetedWidgetSpecification::SetWidgetTarget);

	return TitleWidgetSpecification;
}

void UBBTitleModel::Initialize(UIBBTitleWidget * NewView, UIBBGUIModel * NewParentModel, AIBBHUD * NewHUD)
{
	InitializeView(NewView);
	InitializeParentModel(NewParentModel);
	InitializeHUD(NewHUD);
}

void UBBTitleModel::Finalize()
{
	FinalizeHUD();
	FinalizeParentModel();
	FinalizeView();
}



void UBBTitleModel::InitializeView(UIBBTitleWidget * NewView)
{
	FinalizeView();

	verifyf(IsValid(NewView), TEXT("New Title View is invalid."));

	View = NewView;
}

void UBBTitleModel::InitializeParentModel(UIBBGUIModel * NewParentModel)
{
	FinalizeParentModel();

	verifyf(IsValid(NewParentModel), TEXT("New Parent Model is invalid."));

	ParentModel = NewParentModel;

	OnTargetUpdate().Broadcast(TScriptInterface<IBBWidgetTarget>(ParentModel->GetWidget()));
}

void UBBTitleModel::InitializeHUD(AIBBHUD * NewHUD)
{
	FinalizeHUD();

	verifyf(IsValid(NewHUD), TEXT("New HUD is invalid."));

	HUD = NewHUD;
}

void UBBTitleModel::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBTitleModel::FinalizeParentModel()
{
	if (IsValid(ParentModel))
	{
	}

	ParentModel = nullptr;

	OnTargetUpdate().Broadcast(TScriptInterface<IBBWidgetTarget>(nullptr));
}

void UBBTitleModel::FinalizeHUD()
{
	if (IsValid(HUD))
	{
	}

	HUD = nullptr;
}

void UBBTitleModel::SetPosition(FVector2D NewPosition)
{
	verifyf(IsValid(HUD), TEXT("HUD is invalid."));
	verifyf(IsValid(ParentModel), TEXT("Parent Model is invalid."));
	verifyf(IsValid(ParentModel->GetWidget()), TEXT("Parent Widget is invalid."));

	HUD->ConvertToPIEViewportSpace(NewPosition);

	ParentModel->GetWidget()->SetPositionInViewport(NewPosition);
}

UIBBWidget * UBBTitleModel::GetParentWidget() const
{
	return ParentModel->GetWidget();
}

UIBBWidgetSpecification * UBBTitleModel::GetParentWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(ParentModel), TEXT("Parent Model is invalid."));

	return ParentModel->GetWidgetSpecification(WidgetSpecificationFactory);
}