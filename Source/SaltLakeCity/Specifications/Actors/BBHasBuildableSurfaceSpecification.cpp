// SaltLakeCity 4.25

#include "BBHasBuildableSurfaceSpecification.h"
//#include "Actors/Interfaces/BBHasBuildableSurface.h"
#include "Runtime/Landscape/Classes/Landscape.h"

UBBHasBuildableSurfaceSpecification::UBBHasBuildableSurfaceSpecification() :
	Super()
{
}

bool UBBHasBuildableSurfaceSpecification::Evaluate(UObject * Object)
{
	if (IsValid(Object))
	{
		//return (Object->IsA<ALandscape>() || Object->Implements<UBBHasBuildableSurface>());
	}

	return false;
}