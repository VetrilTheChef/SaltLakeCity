// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBBuildEntryWidgetSpecification.h"
#include "BBBuildEntryWidgetSpecification.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBBuildEntryWidgetSpecification : public UIBBBuildEntryWidgetSpecification
{
	GENERATED_BODY()

	public:
		UBBBuildEntryWidgetSpecification();

		virtual void SetBuildEntry(const UIBBBuildEntry * NewBuildEntry) override;

		virtual bool Evaluate(const UIBBGUIModel * Model) const override;

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override;

	protected:
		UPROPERTY()
		const UIBBBuildEntry * BuildEntry;
};
