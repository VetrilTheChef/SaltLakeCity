// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"
#include "BBProgressWidget.generated.h"

/**
 * 
 */

class UProgressBar;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBProgressWidget : public UIBBProgressWidget
{
	GENERATED_BODY()
	
	public:
		UBBProgressWidget(const FObjectInitializer& ObjectInitializer);

		virtual EBBWidget GetType() const override;

		virtual void AddToScreen(int32 ZOrder = 0) override;

		virtual void SetProgress(float NewPercent) override;

	protected:
		UPROPERTY(meta = (BindWidget))
		UProgressBar* ProgressBar;
};