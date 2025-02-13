// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBDetachWidgetCommand.h"
#include "BBDetachWidgetCommand.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBDetachWidgetCommand : public UIBBDetachWidgetCommand
{
	GENERATED_BODY()

	public:
		UBBDetachWidgetCommand();

		virtual void SetHUD(AIBBHUD * NewHUD) override;

		virtual void SetWidgetComponent(UIBBWidgetComponent * NewComponent);

		virtual void Execute() override;

	protected:
		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBWidgetComponent * Component;
};