// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/GameModes/Interfaces/IBBGameModeCommand.h"
#include "BBGameModeCommand.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBGameModeCommand : public UIBBGameModeCommand
{
	GENERATED_BODY()

	public:
		UBBGameModeCommand();

		virtual void SetGameMode(AIBBGameMode * NewGameMode) override;

		virtual void SetActiveGameMode(EBBGameMode NewActiveGameMode) override;

		virtual void Execute() override;

	protected:
		UPROPERTY()
		AIBBGameMode * GameMode;

		UPROPERTY()
		EBBGameMode ActiveGameMode;
};