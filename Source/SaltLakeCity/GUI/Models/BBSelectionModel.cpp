// SaltLakeCity 4.26

#include "BBSelectionModel.h"
#include "Actors/Components/Interfaces/IBBSelectionComponent.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI//Interfaces/IBBWidgetTarget.h"
#include "GUI/Widgets/Interfaces/IBBSelectionWidget.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBSelectionModel::UBBSelectionModel() :
	Super()
{
	View = nullptr;
	HUD = nullptr;
	Component = nullptr;
}

UIBBWidget * UBBSelectionModel::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBSelectionModel::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	UIBBWidgetSpecification * SelectionWidgetSpecification = nullptr;

	WidgetSpecificationFactory->NewSelectionWidgetSpecification(SelectionWidgetSpecification, this);

	return SelectionWidgetSpecification;
}

void UBBSelectionModel::Initialize(UIBBSelectionWidget * NewView, AIBBHUD * NewHUD)
{
	InitializeView(NewView);
	InitializeHUD(NewHUD);
}

void UBBSelectionModel::Finalize()
{
	FinalizeHUD();
	FinalizeView();
}



void UBBSelectionModel::InitializeView(UIBBSelectionWidget * NewView)
{
	FinalizeView();

	verifyf(IsValid(NewView), TEXT("New Selection View is invalid."));

	View = NewView;
}

void UBBSelectionModel::InitializeHUD(AIBBHUD * NewHUD)
{
	FinalizeHUD();

	verifyf(IsValid(NewHUD), TEXT("New HUD is invalid."));

	HUD = NewHUD;

	HUD->OnSelectionUpdate().AddUObject(this, & UBBSelectionModel::UpdateComponent);
}

void UBBSelectionModel::InitializeComponent(UIBBSelectionComponent * NewSelectionComponent)
{
	FinalizeComponent();

	Component = NewSelectionComponent;

	Component->OnWidgetTargetUpdate().AddUObject(this, & UBBSelectionModel::UpdateWidgetTarget);

	UpdateWidgetTarget(Component->GetWidgetTarget());
}

void UBBSelectionModel::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBSelectionModel::FinalizeHUD()
{
	if (IsValid(HUD))
	{
		HUD->OnSelectionUpdate().RemoveAll(this);
	}

	HUD = nullptr;
}

void UBBSelectionModel::FinalizeComponent()
{
	if (IsValid(Component))
	{
		Component->OnWidgetTargetUpdate().RemoveAll(this);
	}

	Component = nullptr;
}

void UBBSelectionModel::UpdateComponent(UIBBSelectionComponent * NewSelectionComponent)
{
	verifyf(IsValid(NewSelectionComponent), TEXT("New Selection Component is invalid."));

	InitializeComponent(NewSelectionComponent);
}

void UBBSelectionModel::UpdateWidgetTarget(const TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	verifyf(IsValid(NewWidgetTarget.GetObject()), TEXT("New Widget Target is invalid."));

	View->SetDisplayName(NewWidgetTarget->GetDisplayName(EBBDisplayName::Short));
}