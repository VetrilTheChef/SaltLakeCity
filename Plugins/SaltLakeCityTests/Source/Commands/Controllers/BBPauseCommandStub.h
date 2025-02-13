// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/Controllers/Interfaces/IBBPauseCommand.h"
#include "BBPauseCommandStub.generated.h"

/**
*
*/

UCLASS(NotBlueprintable)

class UBBPauseCommandStub : public UIBBPauseCommand
{
	GENERATED_BODY()

	public:
		UBBPauseCommandStub();

		virtual AIBBPlayerController * GetController();

		virtual void SetController(AIBBPlayerController * NewController) override;

		virtual void Execute() override;

		int GetNumExecutions() const;

	protected:
		UPROPERTY()
		AIBBPlayerController * Controller;

		int Executions;
};