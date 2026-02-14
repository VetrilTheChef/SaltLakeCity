// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBModesWidget.h"
#include "BBModesWidgetStub.generated.h"

/**
*
*/

UCLASS(NotBlueprintable)

class UBBModesWidgetStub : public UIBBModesWidget
{
	GENERATED_BODY()

	public:
		UBBModesWidgetStub(const FObjectInitializer& ObjectInitializer);

		virtual EBBWidget GetType() const override;

		virtual void AddToScreen(int32 ZOrder = 0) override;

		UIBBCommand* GetPlayModeCommand() const;

		virtual void SetPlayModeCommand(UIBBCommand* Command) override;

		UIBBCommand* GetBuildModeCommand() const;

		virtual void SetBuildModeCommand(UIBBCommand* Command) override;

		EBBGameMode GetActiveMode() const;

		virtual void SetActiveMode(EBBGameMode GameMode) override;

	protected:
		TSoftObjectPtr<UIBBCommand> PlayModeCommand;

		TSoftObjectPtr<UIBBCommand> BuildModeCommand;

		EBBGameMode ActiveGameMode;
};