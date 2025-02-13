// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/Targets/Interfaces/IBBTargetSpecification.h"
#include "BBTargetSpecification.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBTargetSpecification : public UIBBTargetSpecification
{
	GENERATED_BODY()

	public:
		UBBTargetSpecification();

		virtual void SetTarget(UObject * NewTarget);

		virtual bool Evaluate(const UObject * Object) const override;

	protected:
		UPROPERTY()
		UObject * Target;
};