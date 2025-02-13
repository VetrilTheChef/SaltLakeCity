// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBDateTimeWidget.generated.h"

/**
 * 
 */

class UIBBCommand;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDateTimeWidget : public UIBBWidget
{
	GENERATED_BODY()
	
	public:
		UIBBDateTimeWidget(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) { };

		virtual EBBWidget GetType() const PURE_VIRTUAL(UBBIDateTimeWidget::GetType, return EBBWidget::None; );

		virtual void SetPauseCommand(UIBBCommand * Command) PURE_VIRTUAL(UIBBDateTimeWidget::SetPauseCommand, );

		virtual void SetSlowMotionCommand(UIBBCommand * Command) PURE_VIRTUAL(UIBBDateTimeWidget::SetSlowMotionCommand, );

		virtual void SetPlayCommand(UIBBCommand * Command) PURE_VIRTUAL(UIBBDateTimeWidget::SetPlayCommand, );

		virtual void SetFastForwardCommand(UIBBCommand * Command) PURE_VIRTUAL(UIBBDateTimeWidget::SetFastForwardCommand, );

		virtual void SetDate(FText Date) PURE_VIRTUAL(UIBBDateTimeWidget::SetDate, );

		virtual void SetTime(FText Time) PURE_VIRTUAL(UBBIDateTimeWidget::SetTime, );
};