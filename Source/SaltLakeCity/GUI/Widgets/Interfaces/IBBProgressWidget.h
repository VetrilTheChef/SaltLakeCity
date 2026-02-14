// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBProgressWidget.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBProgressWidget : public UIBBWidget
{
	GENERATED_BODY()
	
	public:
		UIBBProgressWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { };

		virtual EBBWidget GetType() const override
			PURE_VIRTUAL(UIBBProgressWidget::GetType, return EBBWidget::None; );

		virtual void AddToScreen(int32 ZOrder = 0)
			PURE_VIRTUAL(UIBBProgressWidget::AddToScreen, );

		virtual void SetProgress(float NewProgress)
			PURE_VIRTUAL(UIBBProgressWidget::SetProgress, );
};