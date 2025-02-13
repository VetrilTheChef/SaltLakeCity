// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObject/NoExportTypes.h"
#include "IBBWidgetSpecificationVisitor.generated.h"

/**
 * 
 */

class UIBBTargetedWidgetSpecification;

UINTERFACE()

class SALTLAKECITY_API UBBWidgetSpecificationVisitor : public UInterface
{
	GENERATED_BODY()
};

class SALTLAKECITY_API IBBWidgetSpecificationVisitor
{
	GENERATED_BODY()

	public:
		virtual void VisitWidgetTargetSpecification(UIBBTargetedWidgetSpecification & Specification) const PURE_VIRTUAL(IBBWidgetSpecificationVisitor::VisitWidgetTargetSpecification, );
};