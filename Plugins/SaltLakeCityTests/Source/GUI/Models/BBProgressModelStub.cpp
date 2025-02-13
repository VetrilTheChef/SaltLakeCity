// SaltLakeCity 4.26

#include "BBProgressModelStub.h"
#include "Actors/Components/Interfaces/IBBProgressComponent.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"

UBBProgressModelStub::UBBProgressModelStub() :
	Super()
{
	View = nullptr;
	Component = nullptr;

	WidgetSpecification = nullptr;
	Progress = 0.0f;
}

UIBBWidget * UBBProgressModelStub::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBProgressModelStub::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return WidgetSpecification;
}

void UBBProgressModelStub::SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification)
{
	WidgetSpecification = NewWidgetSpecification;
}

void UBBProgressModelStub::Initialize(UIBBProgressWidget * NewView, UIBBProgressComponent * NewProgressComponent)
{
	View = NewView;
	Component = NewProgressComponent;

	if (IsValid(Component))
	{
		Component->OnProgressUpdate().AddUObject(this, &UBBProgressModelStub::UpdateProgress);
	}
}

void UBBProgressModelStub::Finalize()
{
	if (IsValid(Component))
	{
		Component->OnProgressUpdate().RemoveAll(this);
	}

	Component = nullptr;
	View = nullptr;
}

float UBBProgressModelStub::GetProgress()
{
	return Progress;
}

void UBBProgressModelStub::SetProgress(float NewPercent)
{
	Progress = NewPercent;

	if (IsValid(View))
	{
		View->SetProgress(Progress);
	}
}

UIBBProgressComponent * UBBProgressModelStub::GetComponent() const
{
	return Component;
}



void UBBProgressModelStub::UpdateProgress(float NewProgress)
{
	Progress = NewProgress;
}