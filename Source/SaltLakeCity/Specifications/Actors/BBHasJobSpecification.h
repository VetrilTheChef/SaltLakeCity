// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Specifications/Actors/BBActorSpecification.h"
#include "BBHasJobSpecification.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBHasJobSpecification : public UBBActorSpecification
{
	GENERATED_BODY()

	public:
		UBBHasJobSpecification();

		virtual bool Evaluate(UObject * Object) override;
};
