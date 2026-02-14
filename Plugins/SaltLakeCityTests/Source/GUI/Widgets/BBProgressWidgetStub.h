// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"
#include "BBProgressWidgetStub.generated.h"

/**
 * 
 */

class UProgressBar;

UCLASS(NotBlueprintable)

class UBBProgressWidgetStub : public UIBBProgressWidget
{
	GENERATED_BODY()
	
	public:
		UBBProgressWidgetStub(const FObjectInitializer& ObjectInitializer);

		virtual void PostInitProperties() override;

		virtual void NativeDestruct() override;

		virtual void NativeOnInitialized() override;

		virtual EBBWidget GetType() const override;

		virtual void AddToScreen(int32 ZOrder = 0) override;

		float GetProgress();

		virtual void SetProgress(float NewPercent) override;

	protected:
		friend class UBBProgressControllerSpec;

		float Progress;
};