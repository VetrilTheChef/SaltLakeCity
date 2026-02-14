// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "IBBWidget.generated.h"

/**
*
*/

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
		UIBBWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void NativePreConstruct() override { Super::NativePreConstruct(); };

		virtual void NativeOnInitialized() override { Super::NativeOnInitialized(); };

		virtual void BeginDestroy() override { Super::BeginDestroy(); };

		virtual EBBWidget GetType() const PURE_VIRTUAL(UIBBWidget::GetType, return EBBWidget::None; );

		virtual void AddToScreen(int32 ZOrder = 0) PURE_VIRTUAL(UIBBWidget::AddToScreen, );
};