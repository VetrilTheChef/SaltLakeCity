// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "BBWidget.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBWidget : public UIBBWidget
{
	GENERATED_BODY()

	public:
		UBBWidget(const FObjectInitializer & ObjectInitializer);

		virtual void NativePreConstruct() override;

		virtual void NativeOnInitialized() override;

		virtual void BeginDestroy() override;

		virtual EBBWidget GetType() const override;

	protected:
		virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};