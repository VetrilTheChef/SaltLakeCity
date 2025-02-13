// SaltLakeCity 4.24

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
		UBBProgressWidgetStub(const FObjectInitializer & ObjectInitializer);

		virtual void PostInitProperties() override;

		virtual void NativeDestruct() override;

		virtual void NativeOnInitialized() override;

		virtual EBBWidget GetType() const override;

		float GetProgress();

		virtual void SetProgress(float NewPercent) override;

	protected:
		friend class UBBProgressControllerSpec;

		UPROPERTY()
		float Progress;
};