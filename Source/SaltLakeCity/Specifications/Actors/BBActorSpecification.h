// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/BBSpecification.h"
#include "BBActorSpecification.generated.h"

/**
 * 
 */

UCLASS(Abstract)

class SALTLAKECITY_API UBBActorSpecification : public UBBSpecification
{
	GENERATED_BODY()

	public:
		UBBActorSpecification();

		virtual bool Evaluate(UObject * Object);
};
