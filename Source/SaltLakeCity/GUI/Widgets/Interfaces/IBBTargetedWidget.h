// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Interfaces/IBBWidgetTarget.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBTargetedWidget.generated.h"

/**
*
*/

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBTargetedWidget : public UIBBWidget, public IBBWidgetTarget
{
	GENERATED_BODY()

	public:
		//UIBBTargetedWidget(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void NativePreConstruct() override { Super::NativePreConstruct(); };

		virtual void NativeOnInitialized() override { Super::NativeOnInitialized(); };

		virtual void BeginDestroy() override { Super::BeginDestroy(); };

		virtual EBBWidget GetType() const override PURE_VIRTUAL(UIBBTargetedWidget::GetType, return EBBWidget::None; );

		DECLARE_DERIVED_EVENT(UIBBTargetedWidget, IBBWidgetTarget::FBBWidgetTargetUpdate, FBBWidgetTargetUpdate);

		virtual FBBWidgetTargetUpdate & OnWidgetTargetUpdate() final override { return WidgetTargetUpdate; };

	protected:
		FBBWidgetTargetUpdate WidgetTargetUpdate;
};