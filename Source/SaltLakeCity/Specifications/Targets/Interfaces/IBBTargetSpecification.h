// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IBBTargetSpecification.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBTargetSpecification : public UObject
{
	GENERATED_BODY()

	public:
		UIBBTargetSpecification() : Super() { };

		virtual void SetTarget(UObject * NewTarget) PURE_VIRTUAL(UIBBTargetSpecification::SetTarget, );

		virtual bool Evaluate(const UObject * Object) const PURE_VIRTUAL(UIBBTargetSpecification::Evaluate, return false; );
};