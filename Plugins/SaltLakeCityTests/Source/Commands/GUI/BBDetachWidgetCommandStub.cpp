// SaltLakeCity 4.27

#include "BBDetachWidgetCommandStub.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"

UBBDetachWidgetCommandStub::UBBDetachWidgetCommandStub() :
	Super()
{
	HUD = nullptr;
	Component = nullptr;
	Specification = nullptr;

	Executions = 0;
}

AIBBHUD * UBBDetachWidgetCommandStub::GetHUD() const
{
	return HUD;
}

void UBBDetachWidgetCommandStub::SetHUD(AIBBHUD * NewHUD)
{
	HUD = NewHUD;
}

UIBBWidgetComponent * UBBDetachWidgetCommandStub::GetWidgetComponent()
{
	return Component;
}

void UBBDetachWidgetCommandStub::SetWidgetComponent(UIBBWidgetComponent * NewComponent)
{
	Component = NewComponent;
}

UIBBWidgetSpecification * UBBDetachWidgetCommandStub::GetSpecification()
{
	return Specification;
}

void UBBDetachWidgetCommandStub::SetSpecification(UIBBWidgetSpecification * NewSpecification)
{
	Specification = NewSpecification;
}

void UBBDetachWidgetCommandStub::Execute()
{
	Executions++;

	if (IsValid(Component))
	{
		Component->SetWidget(nullptr);
	}
}

int UBBDetachWidgetCommandStub::GetNumExecutions() const
{
	return Executions;
}