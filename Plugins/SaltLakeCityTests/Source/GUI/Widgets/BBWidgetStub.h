// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "BBWidgetStub.generated.h"

/**
*
*/

class ULocalPlayer;

UCLASS(NotBlueprintable)

class UBBWidgetStub : public UIBBWidget
{
	GENERATED_BODY()

	public:
		UBBWidgetStub(const FObjectInitializer& ObjectInitializer);

		virtual void AddToScreen(int32 ZOrder = 0) override;

		virtual EBBWidget GetType() const override;

		virtual FVector2D GetPositionInViewport(bool bRemoveDPIScale = true);

		bool IsInViewport();

		void SetIsInViewport(bool IsInViewport);

	protected:
		bool InViewport;
};