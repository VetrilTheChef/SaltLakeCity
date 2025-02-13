// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "BBGameModeStub.generated.h"

/**
*
*/

UCLASS(NotBlueprintable)

class ABBGameModeStub : public AIBBGameMode
{
	GENERATED_BODY()

	public:
		ABBGameModeStub();

		virtual void BeginPlay() override;
		
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize() override;

		virtual void Finalize() override;

		EBBGameMode GetMode();

		virtual void SetMode(EBBGameMode NewGameMode) override;

		void BroadcastActiveModeUpdate();

	protected:
		EBBGameMode GameMode;
};