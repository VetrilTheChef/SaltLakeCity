// SaltLakeCity 4.27

#include "BBSpecification.h"

UBBSpecification::UBBSpecification() :
	Super()
{
}

bool UBBSpecification::Evaluate(UObject * Object)
{
	return IsValid(Object);
}