// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "IBBGameModeState.generated.h"

/**
*
*/

class AIBBGameState;
class AIBBPlayerController;
class UIBBWidgetSpecificationFactory;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UIBBGameModeState : public UObject
{
	GENERATED_BODY()

	public:
		UIBBGameModeState() : Super() { };

		virtual void Initialize(AIBBPlayerController * NewController, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, AIBBGameState * NewGameState) PURE_VIRTUAL(UIBBGameModeState::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBGameModeState::Finalize, );

		virtual void Activate() PURE_VIRTUAL(UIBBGameModeState::Activate, );

		virtual void Deactivate() PURE_VIRTUAL(UIBBGameModeState::Deactivate, );
};