// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"
#include "BBDateTimeWidgetStub.generated.h"

/**
 * 
 */

class UIBBCommand;

UCLASS(NotBlueprintable)

class UBBDateTimeWidgetStub : public UIBBDateTimeWidget
{
	GENERATED_BODY()
	
	public:
		UBBDateTimeWidgetStub(const FObjectInitializer & ObjectInitializer);

		virtual void NativeDestruct() override;

		virtual void NativeOnInitialized() override;

		virtual EBBWidget GetType() const override;

		virtual void SetPauseCommand(UIBBCommand * Command) override;

		virtual void SetSlowMotionCommand(UIBBCommand * Command) override;

		virtual void SetPlayCommand(UIBBCommand * Command) override;

		virtual void SetFastForwardCommand(UIBBCommand * Command) override;

		FText GetDate();

		virtual void SetDate(FText Date) override;

		FText GetTime();

		virtual void SetTime(FText Time) override;

		void ClickPauseButton();

		void ClickSlowMotionButton();

		void ClickPlayButton();

		void ClickFastForwardButton();

	protected:
		UPROPERTY()
		UIBBCommand * PauseCommand;

		UPROPERTY()
		UIBBCommand * SlowMotionCommand;

		UPROPERTY()
		UIBBCommand * PlayCommand;

		UPROPERTY()
		UIBBCommand * FastForwardCommand;

		UPROPERTY()
		FText DateText;

		UPROPERTY()
		FText TimeText;
};