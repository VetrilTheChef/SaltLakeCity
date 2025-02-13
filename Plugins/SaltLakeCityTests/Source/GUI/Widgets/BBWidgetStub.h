// SaltLakeCity 4.24

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
		UBBWidgetStub(const FObjectInitializer & ObjectInitializer);

		virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;

		virtual EBBWidget GetType() const override;

		virtual FVector2D GetPositionInViewport(bool bRemoveDPIScale = true);

		bool IsInViewport();

		void SetIsInViewport(bool IsInViewport);

	protected:
		UPROPERTY()
		bool InViewport;
};