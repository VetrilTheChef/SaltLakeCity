// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Data/BBContextRowData.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"
#include "BBWidgetSpecificationFactoryStub.generated.h"

/**
 *
 */

UCLASS(NotBlueprintable)

class UBBWidgetSpecificationFactoryStub : public UIBBWidgetSpecificationFactory
{
	GENERATED_BODY()

	public:
		UBBWidgetSpecificationFactoryStub();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		void AddWidgetSpecification(UIBBWidgetSpecification * WidgetSpecification);

		virtual bool NewBuildWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const override;

		virtual bool NewContextWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const override;

		virtual bool NewDateTimeWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const override;

		virtual bool NewDossierWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const override;

		virtual bool NewJobWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const override;

		virtual bool NewModesWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const override;

		virtual bool NewProgressWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const override;

		virtual bool NewSelectionWidgetSpecification(UIBBWidgetSpecification * & WidgetSpecification, UObject * Outer) const override;

		virtual bool NewTitleWidgetSpecification(UIBBTargetedWidgetSpecification * & WidgetSpecification, UObject * Outer, TScriptInterface<IBBWidgetTarget> WidgetTarget) const override;

	protected:
		UPROPERTY()
		mutable TArray<UIBBWidgetSpecification *> WidgetSpecifications;
};