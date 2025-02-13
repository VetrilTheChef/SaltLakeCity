// SaltLakeCity 4.27

#include "BBTargetSpecification.h"
#include "GUI/Models/Interfaces/IBBTargetedModel.h"

UBBTargetSpecification::UBBTargetSpecification() :
	Super()
{
	Target = nullptr;
}

void UBBTargetSpecification::SetTarget(UObject * NewTarget)
{
	Target = NewTarget;
}

bool UBBTargetSpecification::Evaluate(const UObject * Object) const
{
	return (IsValid(Object) &&
			(Object == Target));
}