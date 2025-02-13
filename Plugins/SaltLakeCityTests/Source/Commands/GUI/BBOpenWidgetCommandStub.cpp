// SaltLakeCity 4.27

#include "BBOpenWidgetCommandStub.h"

UBBOpenWidgetCommandStub::UBBOpenWidgetCommandStub() :
	Super()
{
	HUD = nullptr;
	Specification = nullptr;
	PopUp = false;

	Executions = 0;
}

void UBBOpenWidgetCommandStub::SetHUD(AIBBHUD * NewHUD)
{
	HUD = NewHUD;
}

void UBBOpenWidgetCommandStub::SetSpecification(UIBBWidgetSpecification * NewSpecification)
{
	Specification = NewSpecification;
}

bool UBBOpenWidgetCommandStub::GetPopUp()
{
	return PopUp;
}

void UBBOpenWidgetCommandStub::SetPopUp(bool NewPopUp)
{
	PopUp = NewPopUp;
}

void UBBOpenWidgetCommandStub::Execute()
{
	Executions++;
}

int UBBOpenWidgetCommandStub::GetNumExecutions() const
{
	return Executions;
}