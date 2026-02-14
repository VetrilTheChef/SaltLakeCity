// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"
#include "BBDateTimeWidget.generated.h"

/**
 * 
 */

class UTextBlock;
class UBBButton;
class UIBBCommand;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBDateTimeWidget : public UIBBDateTimeWidget
{
	GENERATED_BODY()
	
	public:
		UBBDateTimeWidget(const FObjectInitializer& ObjectInitializer);

		virtual EBBWidget GetType() const override;

		virtual void AddToScreen(int32 ZOrder = 0) override;

		virtual void SetPauseCommand(UIBBCommand* Command) override;

		virtual void SetSlowMotionCommand(UIBBCommand* Command) override;

		virtual void SetPlayCommand(UIBBCommand* Command) override;

		virtual void SetFastForwardCommand(UIBBCommand* Command) override;

		virtual void SetDate(FText Date) override;

		virtual void SetTime(FText Time) override;
	
	protected:
		UPROPERTY(meta = (BindWidget))
		UTextBlock* DateText;

		UPROPERTY(meta = (BindWidget))
		UTextBlock* TimeText;

		UPROPERTY(meta = (BindWidget))
		UBBButton* PauseButton;

		UPROPERTY(meta = (BindWidget))
		UBBButton* SlowMotionButton;

		UPROPERTY(meta = (BindWidget))
		UBBButton* PlayButton;

		UPROPERTY(meta = (BindWidget))
		UBBButton* FastForwardButton;
};