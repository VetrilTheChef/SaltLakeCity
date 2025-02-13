// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Modes/Interfaces/IBBGameModeState.h"
#include "IBBGameModeBuild.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UIBBGameModeBuild : public UIBBGameModeState
{
	GENERATED_BODY()

	public:
		UIBBGameModeBuild() : Super() { };

		virtual void Initialize(AIBBPlayerController * NewController, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, AIBBGameState * NewGameState) override PURE_VIRTUAL(UIBBGameModeBuild::Initialize, );

		virtual void Finalize() override PURE_VIRTUAL(UIBBGameModeBuild::Finalize, );

		virtual void Activate() override PURE_VIRTUAL(UIBBGameModeBuild::Activate, );

		virtual void Deactivate() override PURE_VIRTUAL(UIBBGameModeBuild::Deactivate, );
};