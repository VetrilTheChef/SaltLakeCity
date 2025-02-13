// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Specifications/Actors/BBActorSpecification.h"
#include "BBHasBuildableSurfaceSpecification.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBHasBuildableSurfaceSpecification : public UBBActorSpecification
{
	GENERATED_BODY()

	public:
		UBBHasBuildableSurfaceSpecification();

		virtual bool Evaluate(UObject * Object) override;
};