// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/Targets/Interfaces/IBBTargetSpecification.h"
#include "BBTargetSpecificationStub.generated.h"

/**
 * 
 */

class UIBBGUIModel;

UCLASS(NotBlueprintable)

class UBBTargetSpecificationStub : public UIBBTargetSpecification
{
	GENERATED_BODY()

	public:
		UBBTargetSpecificationStub();

		UObject * GetTarget() const ;

		virtual void SetTarget(UObject * NewTarget) override;

		virtual bool Evaluate(const UObject * Object) const override;

	protected:
		UPROPERTY()
		UObject * Target;
};