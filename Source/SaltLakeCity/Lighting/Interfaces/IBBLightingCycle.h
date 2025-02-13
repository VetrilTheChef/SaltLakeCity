// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IBBLightingCycle.generated.h"

/**
 * 
 */

class AIBBLevelScriptActor;
class UIBBGameClock;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UIBBLightingCycle : public UObject
{
	GENERATED_BODY()

	public:
		UIBBLightingCycle() : Super() { };

		virtual void Initialize(const AIBBLevelScriptActor * LevelScriptActor, const UIBBGameClock * NewGameClock) PURE_VIRTUAL(UIBBLightingCycle::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBLightingCycle::Finalize, );

		virtual void Tick() PURE_VIRTUAL(UIBBLightingCycle::Tick, );
};