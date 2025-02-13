// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBSelectionWidget.h"
#include "BBSelectionWidget.generated.h"

/**
 * 
 */

class UProgressBar;
class UTextBlock;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBSelectionWidget : public UIBBSelectionWidget
{
	GENERATED_BODY()
	
	public:
		UBBSelectionWidget(const FObjectInitializer & ObjectInitializer);

		virtual EBBWidget GetType() const override;

		virtual void SetDisplayName(FText NewDisplayName) override;

	protected:
		UPROPERTY(meta = (BindWidget))
		UTextBlock * DisplayNameText;
};