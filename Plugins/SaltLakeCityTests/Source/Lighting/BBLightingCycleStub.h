// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Lighting/Interfaces/IBBLightingCycle.h"
#include "BBLightingCycleStub.generated.h"

/**
 * 
 */

UCLASS(Abstract, NotBlueprintable)

class UBBLightingCycleStub : public UIBBLightingCycle
{
	GENERATED_BODY()

	public:
		UBBLightingCycleStub();

		virtual void Initialize(const AIBBLevelScriptActor * LevelScriptActor, const UIBBGameClock * NewGameClock) override;

		virtual void Finalize() override;

		virtual void Tick() override;

		const AIBBLevelScriptActor * GetLevelScriptActor() const;

		const UIBBGameClock * GetGameClock() const;

		int GetNumTicks() const;

	protected:
		UPROPERTY()
		const AIBBLevelScriptActor * CurrentLevelScriptActor;

		UPROPERTY()
		const UIBBGameClock * GameClock;

		int Ticks;
};