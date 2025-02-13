// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Data/BBContextRowData.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"
#include "BBWidgetSpecificationFactory.generated.h"

/**
 *
 */

class UIBBBuildWidgetSpecification;
class UIBBContextWidgetSpecification;
class UIBBDateTimeWidgetSpecification;
class UIBBDossierWidgetSpecification;
class UIBBJobWidgetSpecification;
class UIBBModesWidgetSpecification;
class UIBBProgressWidgetSpecification;
class UIBBSelectionWidgetSpecification;
class UIBBTitleWidgetSpecification;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBWidgetSpecificationFactory : public UIBBWidgetSpecificationFactory
{
	GENERATED_BODY()

	public:
		UBBWidgetSpecificationFactory();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

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
		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBBuildWidgetSpecification> BuildWidgetSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBContextWidgetSpecification> ContextWidgetSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBDateTimeWidgetSpecification> DateTimeWidgetSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBDossierWidgetSpecification> DossierWidgetSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBJobWidgetSpecification> JobWidgetSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBModesWidgetSpecification> ModesWidgetSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBProgressWidgetSpecification> ProgressWidgetSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBSelectionWidgetSpecification> SelectionWidgetSpecificationClass;

		UPROPERTY(EditDefaultsOnly, Category = "Classes")
		TSoftClassPtr<UIBBTitleWidgetSpecification> TitleWidgetSpecificationClass;
};