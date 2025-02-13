// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Data/BBContextRowData.h"
#include "IBBWidgetSpecificationFactory.generated.h"

/**
 * 
 */

Expose_TNameOf(UIBBWidgetSpecificationFactory)

class IBBWidgetTarget;
class UIBBTargetedWidgetSpecification;
class UIBBWidgetSpecification;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBWidgetSpecificationFactory : public UObject
{
	GENERATED_BODY()

	public:
		UIBBWidgetSpecificationFactory() : Super() { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); };

		virtual void BeginDestroy() override { Super::BeginDestroy(); };
		
		virtual bool NewBuildWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const PURE_VIRTUAL(UIBBWidgetSpecificationFactory::NewBuildWidgetSpecification, return false; );

		virtual bool NewContextWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const PURE_VIRTUAL(UIBBWidgetSpecificationFactory::NewContextWidgetSpecification, return false; );

		virtual bool NewDateTimeWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const PURE_VIRTUAL(UIBBWidgetSpecificationFactory::NewDateTimeWidgetSpecification, return false; );

		virtual bool NewDossierWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const PURE_VIRTUAL(UIBBWidgetSpecificationFactory::NewDossierWidgetSpecification, return false; );

		virtual bool NewJobWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const PURE_VIRTUAL(UIBBWidgetSpecificationFactory::NewJobWidgetSpecification, return false; );

		virtual bool NewModesWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const PURE_VIRTUAL(UIBBWidgetSpecificationFactory::NewModesWidgetSpecification, return false; );

		virtual bool NewProgressWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const PURE_VIRTUAL(UIBBWidgetSpecificationFactory::NewProgressWidgetSpecification, return false; );

		virtual bool NewSelectionWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const PURE_VIRTUAL(UIBBWidgetSpecificationFactory::NewSelectionWidgetSpecification, return false; );

		virtual bool NewTitleWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const PURE_VIRTUAL(UIBBWidgetSpecificationFactory::NewTitleWidgetSpecification, return false; );
};