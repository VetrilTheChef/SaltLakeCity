// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
//#include "Actors/Interfaces/BBHasInventory.h"
#include "Specifications/Actors/BBActorSpecification.h"
#include "BBHasInventorySpecification.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBHasInventorySpecification : public UBBActorSpecification
{
	GENERATED_BODY()

	public:
		UBBHasInventorySpecification();

		virtual bool Evaluate(UObject * Object) override;
};
