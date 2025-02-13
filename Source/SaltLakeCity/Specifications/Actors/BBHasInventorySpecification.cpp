// SaltLakeCity 4.25

#include "BBHasInventorySpecification.h"

UBBHasInventorySpecification::UBBHasInventorySpecification() :
	Super()
{
}

bool UBBHasInventorySpecification::Evaluate(UObject * Object)
{
	if (IsValid(Object))
	{
//		return Object->Implements<UBBHasInventory>();
	}

	return false;
}