// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBSelectionWidget.h"
#include "BBSelectionWidgetStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBSelectionWidgetStub : public UIBBSelectionWidget
{
	GENERATED_BODY()
	
	public:
		UBBSelectionWidgetStub(const FObjectInitializer & ObjectInitializer);

		virtual EBBWidget GetType() const override;

		FText GetDisplayName();

		virtual void SetDisplayName(FText NewDisplayName) override;

	protected:
		FText DisplayName;
};