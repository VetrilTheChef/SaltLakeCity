// SaltLakeCity 4.27

#include "BBHasDossierSpecification.h"
//#include "Actors/Interfaces/BBHasDossier.h"

UBBHasDossierSpecification::UBBHasDossierSpecification() :
	Super()
{
}

bool UBBHasDossierSpecification::Evaluate(UObject * Object)
{
	if (IsValid(Object))
	{
		//return Object->Implements<UBBHasDossier>();
	}

	return false;
}