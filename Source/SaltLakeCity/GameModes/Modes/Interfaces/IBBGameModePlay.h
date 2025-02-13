// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Modes/Interfaces/IBBGameModeState.h"
#include "IBBGameModePlay.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UIBBGameModePlay : public UIBBGameModeState
{
	GENERATED_BODY()

	public:
		UIBBGameModePlay() : Super() { };

		virtual void Initialize(AIBBPlayerController * NewController, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, AIBBGameState * NewGameState) override PURE_VIRTUAL(UIBBGameModePlay::Initialize, );

		virtual void Finalize() override PURE_VIRTUAL(UIBBGameModePlay::Finalize, );

		virtual void Activate() override PURE_VIRTUAL(UIBBGameModePlay::Activate, );

		virtual void Deactivate() override PURE_VIRTUAL(UIBBGameModePlay::Deactivate, );
};