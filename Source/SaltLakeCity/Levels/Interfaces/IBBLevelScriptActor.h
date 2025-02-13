// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "IBBLevelScriptActor.generated.h"

/**
 * 
 */

class ADirectionalLight;
class ALandscape;
class ASkyLight;
class UIBBGameClock;
class UIBBLightingCycle;
class ULevel;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
	public:
		AIBBLevelScriptActor() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Tick(float DeltaSeconds) override { Super::Tick(DeltaSeconds); };

		virtual void Initialize(const UIBBGameClock * NewGameClock) PURE_VIRTUAL(AIBBLevelScriptActor::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(AIBBLevelScriptActor::Finalize, );

		virtual const float GetLatitude() const PURE_VIRTUAL(AIBBLevelScriptActor::GetLatitude, return 0.0f; );

		virtual const float GetLongitude() const PURE_VIRTUAL(AIBBLevelScriptActor::GetLongitude, return 0.0f; );

		virtual FVector GetLevelBounds() const PURE_VIRTUAL(AIBBLevelScriptActor::GetLevelBounds, return FVector(0.0f); );

		virtual ALandscape * GetLandscape() const PURE_VIRTUAL(AIBBLevelScriptActor::GetLandscape, return nullptr; );

		virtual ADirectionalLight * GetSunLight() const PURE_VIRTUAL(AIBBLevelScriptActor::GetSunLight, return nullptr; );

		virtual ASkyLight * GetSkyLight() const PURE_VIRTUAL(AIBBLevelScriptActor::GetSkyLight, return nullptr; );

		virtual const UIBBLightingCycle * GetLightingCycle() const PURE_VIRTUAL(AIBBLevelScriptActor::GetLightingCycle, return nullptr; );

		virtual void SetLightingCycle(UIBBLightingCycle * NewLightingCycle) PURE_VIRTUAL(AIBBLevelScriptActor::SetLightingCycle, );

		virtual ULevel * GetPreviewLevel() const PURE_VIRTUAL(AIBBLevelScriptActor::GetPreviewLevel, return nullptr; );

		virtual void SetPreviewLevel(ULevel * NewPreviewLevel) PURE_VIRTUAL(AIBBLevelScriptActor::SetPreviewLevel, );
};