// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/GameModes/Interfaces/IBBGameModeCommand.h"
#include "BBGameModeCommandStub.generated.h"

/**
 *
 */

UCLASS(NotBlueprintable)

class  UBBGameModeCommandStub : public UIBBGameModeCommand
{
	GENERATED_BODY()

	public:
		UBBGameModeCommandStub();

		AIBBGameMode * GetGameMode();

		void SetGameMode(AIBBGameMode * NewGameMode) override;

		EBBGameMode GetActiveGameMode();

		void SetActiveGameMode(EBBGameMode NewActiveGameMode) override;

		virtual void Execute() override;

		int GetNumExecutions() const;

	protected:
		UPROPERTY()
		AIBBGameMode * GameMode;

		UPROPERTY()
		EBBGameMode ActiveGameMode;

		int Executions;
};