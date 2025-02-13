// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BBSpecification.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBSpecification : public UObject
{
	GENERATED_BODY()

	public:
		UBBSpecification();

		virtual bool Evaluate(UObject * Object);
};
