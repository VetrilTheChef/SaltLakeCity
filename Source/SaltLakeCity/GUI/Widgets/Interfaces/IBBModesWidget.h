// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBModesWidget.generated.h"

/**
 * 
 */

class UIBBCommand;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBModesWidget : public UIBBWidget
{
	GENERATED_BODY()
	
	public:
		UIBBModesWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void NativeOnInitialized() override
			{ Super::NativeOnInitialized(); };

		virtual void NativeDestruct() override
			{ Super::NativeDestruct(); };

		virtual EBBWidget GetType() const
			PURE_VIRTUAL(UIBBModesWidget::GetType, return EBBWidget::None; );

		virtual void AddToScreen(int32 ZOrder = 0)
			PURE_VIRTUAL(UIBBModesWidget::AddToScreen, );

		virtual void SetPlayModeCommand(UIBBCommand* Command)
			PURE_VIRTUAL(UIBBModesWidget::SetPlayModeCommand, );

		virtual void SetBuildModeCommand(UIBBCommand* Command)
			PURE_VIRTUAL(UIBBModesWidget::SetBuildModeCommand, );

		virtual void SetActiveMode(EBBGameMode GameMode)
			PURE_VIRTUAL(UIBBModesWidget::SetActiveMode, );
};