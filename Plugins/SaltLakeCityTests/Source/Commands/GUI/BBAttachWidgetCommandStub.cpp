// SaltLakeCity 4.27

#include "BBAttachWidgetCommandStub.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBAttachWidgetCommandStub::UBBAttachWidgetCommandStub() :
	Super()
{
	Widget = nullptr;
	HUD = nullptr;
	Component = nullptr;
	Specification = nullptr;

	Executions = 0;
}

UIBBWidget * UBBAttachWidgetCommandStub::GetWidget() const
{
	return Widget;
}

void UBBAttachWidgetCommandStub::SetWidget(UIBBWidget * NewWidget)
{
	Widget = NewWidget;
}

AIBBHUD * UBBAttachWidgetCommandStub::GetHUD() const
{
	return HUD;
}

void UBBAttachWidgetCommandStub::SetHUD(AIBBHUD * NewHUD)
{
	HUD = NewHUD;
}

UIBBWidgetComponent * UBBAttachWidgetCommandStub::GetWidgetComponent() const
{
	return Component;
}

void UBBAttachWidgetCommandStub::SetWidgetComponent(UIBBWidgetComponent * NewComponent)
{
	Component = NewComponent;
}

UIBBWidgetSpecification * UBBAttachWidgetCommandStub::GetSpecification() const
{
	return Specification;
}

void UBBAttachWidgetCommandStub::SetSpecification(UIBBWidgetSpecification * NewSpecification)
{
	Specification = NewSpecification;
}

int UBBAttachWidgetCommandStub::GetNumExecutions() const
{
	return Executions;
}

void UBBAttachWidgetCommandStub::Execute()
{
	Executions++;

	if (IsValid(Component))
	{
		Component->SetWidget(Widget);
	}
}