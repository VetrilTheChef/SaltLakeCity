// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Includes/BBContextEnum.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "IBBSpecificationFactory.generated.h"

/**
 * 
 */

Expose_TNameOf(UIBBSpecificationFactory)

class IBBWidgetSpecificationVisitor;
class UBBHasBuildableSurfaceSpecification;
class UBBHasDossierSpecification;
class UBBHasInventorySpecification;
class UBBHasJobSpecification;
class UIBBBuildWidgetSpecification;
class UIBBContextSpecification;
class UIBBContextRowSpecification;
class UIBBContextRowModel;
class UIBBJobSpecification;
class UIBBTargetSpecification;
class UIBBWidgetSpecification;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSpecificationFactory : public UObject
{
	GENERATED_BODY()

	public:
		UIBBSpecificationFactory() : Super() { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); };

		virtual void BeginDestroy() override { Super::BeginDestroy(); };

		virtual bool NewHasBuildableSurfaceSpecification(UBBHasBuildableSurfaceSpecification * & Specification, UObject * Outer) PURE_VIRTUAL(UIBBSpecificationFactory::NewHasBuildableSurfaceSpecification, return false; );

		virtual bool NewHasDossierSpecification(UBBHasDossierSpecification * & Specification, UObject * Outer) PURE_VIRTUAL(UIBBSpecificationFactory::NewHasDossierSpecification, return false; );

		virtual bool NewHasInventorySpecification(UBBHasInventorySpecification * & Specification, UObject * Outer) PURE_VIRTUAL(UIBBSpecificationFactory::NewHasInventorySpecification, return false; );

		virtual bool NewHasJobSpecification(UBBHasJobSpecification * & Specification, UObject * Outer) PURE_VIRTUAL(UIBBSpecificationFactory::NewHasJobSpecification, return false; );

		virtual bool NewContextSpecification(UIBBContextSpecification * & Specification, UObject * Outer) const PURE_VIRTUAL(UIBBSpecificationFactory::NewContextSpecification, return false; );

		virtual bool NewContextRowSpecification(UIBBContextRowSpecification * & Specification, UObject * Outer, EBBContext ContextType, EBBWidget WidgetToOpen) const PURE_VIRTUAL(UIBBSpecificationFactory::NewContextRowSpecification, return false; );

		virtual bool NewJobSpecification(UIBBJobSpecification * & Specification, UObject * Outer) const PURE_VIRTUAL(UIBBSpecificationFactory::NewJobSpecification, return false; );

		virtual bool NewTargetSpecification(UIBBTargetSpecification * & Specification, UObject * Outer, UObject * Target) const PURE_VIRTUAL(UIBBSpecificationFactory::NewTargetSpecification, return false; );

		virtual bool NewBuildWidgetSpecification(UIBBBuildWidgetSpecification * & Specification, UObject * Outer) const PURE_VIRTUAL(UIBBSpecificationFactory::NewBuildWidgetSpecification, return false; );

		virtual bool NewWidgetSpecification(UIBBWidgetSpecification * & Specification, UObject * Outer, EBBWidget WidgetType, IBBWidgetSpecificationVisitor & Visitor) const PURE_VIRTUAL(UIBBSpecificationFactory::NewWidgetSpecification, return false; );

		virtual bool NewJobWidgetSpecification(UIBBWidgetSpecification * & Specification, UObject * Outer) const PURE_VIRTUAL(UIBBSpecificationFactory::NewJobWidgetSpecification, return false; );
};