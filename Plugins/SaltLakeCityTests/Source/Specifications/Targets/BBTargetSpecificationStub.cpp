// SaltLakeCity 4.25

#include "BBTargetSpecificationStub.h"

UBBTargetSpecificationStub::UBBTargetSpecificationStub() :
	Super()
{
	Target = nullptr;
}

UObject * UBBTargetSpecificationStub::GetTarget() const
{
	return Target;
}

void UBBTargetSpecificationStub::SetTarget(UObject * NewTarget)
{
	Target = NewTarget;
}

bool UBBTargetSpecificationStub::Evaluate(const UObject * Object) const
{
	return (IsValid(Object) &&
			(Object == Target));
}