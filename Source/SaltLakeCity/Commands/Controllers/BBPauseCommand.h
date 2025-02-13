// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/Controllers/Interfaces/IBBPauseCommand.h"
#include "BBPauseCommand.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBPauseCommand : public UIBBPauseCommand
{
	GENERATED_BODY()

	public:
		UBBPauseCommand();

		virtual void SetController(AIBBPlayerController * NewController) override;

		virtual void Execute() override;

	protected:
		UPROPERTY()
		AIBBPlayerController * Controller;
};