// SaltLakeCity 4.26

#include "BBProgressModel.h"
#include "Actors/Components/Interfaces/IBBProgressComponent.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBProgressModel::UBBProgressModel() :
	Super()
{
	View = nullptr;
	Component = nullptr;
}

UIBBWidget * UBBProgressModel::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBProgressModel::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	UIBBWidgetSpecification * ProgressWidgetSpecification = nullptr;

	WidgetSpecificationFactory->NewProgressWidgetSpecification(ProgressWidgetSpecification, this);

	return ProgressWidgetSpecification;
}

void UBBProgressModel::Initialize(UIBBProgressWidget * NewView, UIBBProgressComponent * NewProgressComponent)
{
	InitializeView(NewView);
	InitializeComponent(NewProgressComponent);
}

void UBBProgressModel::Finalize()
{
	FinalizeComponent();
	FinalizeView();
}



void UBBProgressModel::InitializeView(UIBBProgressWidget * NewView)
{
	FinalizeView();

	verifyf(IsValid(NewView), TEXT("New Progress View is invalid."));

	View = NewView;
}

void UBBProgressModel::InitializeComponent(UIBBProgressComponent * NewProgressComponent)
{
	FinalizeComponent();

	verifyf(IsValid(NewProgressComponent), TEXT("New Progress Component is invalid."));

	Component = NewProgressComponent;

	Component->OnProgressUpdate().AddUObject(this, & UBBProgressModel::UpdateProgress);

	UpdateProgress(Component->GetProgress());
}

void UBBProgressModel::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBProgressModel::FinalizeComponent()
{
	if (IsValid(Component))
	{
		Component->OnProgressUpdate().RemoveAll(this);
	}

	Component = nullptr;
}

void UBBProgressModel::UpdateProgress(float NewProgress)
{
	verifyf(IsValid(View), TEXT("Progress View is invalid."));

	View->SetProgress(NewProgress);
}