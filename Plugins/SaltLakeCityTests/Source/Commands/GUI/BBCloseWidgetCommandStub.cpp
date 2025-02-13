// SaltLakeCity 4.27

#include "BBCloseWidgetCommandStub.h"

UBBCloseWidgetCommandStub::UBBCloseWidgetCommandStub() :
	Super()
{
	Specification = nullptr;

	Executions = 0;
}

UIBBWidgetSpecification * UBBCloseWidgetCommandStub::GetSpecification()
{
	return Specification;
}

void UBBCloseWidgetCommandStub::SetSpecification(UIBBWidgetSpecification * NewSpecification)
{
	Specification = NewSpecification;
}

void UBBCloseWidgetCommandStub::Execute()
{
	Executions++;
}

int UBBCloseWidgetCommandStub::GetNumExecutions() const
{
	return Executions;
}