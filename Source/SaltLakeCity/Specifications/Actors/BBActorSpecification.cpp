// SaltLakeCity 4.25

#include "BBActorSpecification.h"

UBBActorSpecification::UBBActorSpecification() :
	Super()
{
}

bool UBBActorSpecification::Evaluate(UObject * Object)
{
	if (IsValid(Object))
	{
		return Object->IsA<AActor>();
	}
	
	return false;
}