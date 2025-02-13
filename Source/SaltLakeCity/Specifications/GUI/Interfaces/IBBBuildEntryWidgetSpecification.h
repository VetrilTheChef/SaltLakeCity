// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"
#include "IBBBuildEntryWidgetSpecification.generated.h"

/**
 * 
 */

class UIBBBuildEntry;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBuildEntryWidgetSpecification : public UIBBWidgetSpecification
{
	GENERATED_BODY()

	public:
		UIBBBuildEntryWidgetSpecification() : Super() { };

		virtual void SetBuildEntry(const UIBBBuildEntry * NewBuildEntry) PURE_VIRTUAL(UIBBBuildEntryWidgetSpecification::SetBuildEntry, );

		virtual bool Evaluate(const UIBBGUIModel * Model) const override PURE_VIRTUAL(UIBBBuildEntryWidgetSpecification::Evaluate, return false; );

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const PURE_VIRTUAL(UIBBBuildEntryWidgetSpecification::CreateWidget, return false; );
};