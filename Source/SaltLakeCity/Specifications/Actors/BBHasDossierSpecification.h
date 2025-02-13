// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Specifications/Actors/BBActorSpecification.h"
#include "BBHasDossierSpecification.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBHasDossierSpecification : public UBBActorSpecification
{
	GENERATED_BODY()

	public:
		UBBHasDossierSpecification();

		virtual bool Evaluate(UObject * Object) override;
};