// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Levels/Interfaces/IBBLevelScriptActor.h"
#include "BBLevelScriptActor.generated.h"

/**
 * 
 */

class UIBBLightingCycle;

UCLASS()

class SALTLAKECITY_API ABBLevelScriptActor : public AIBBLevelScriptActor
{
	GENERATED_BODY()
	
	public:
		ABBLevelScriptActor();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Tick(float DeltaSeconds) override;

		virtual void Initialize(const UIBBGameClock * NewGameClock) override;

		virtual void Finalize() override;

		virtual const float GetLatitude() const override;

		virtual const float GetLongitude() const override;

		virtual FVector GetLevelBounds() const override;

		virtual ALandscape * GetLandscape() const override;

		virtual ADirectionalLight * GetSunLight() const override;

		virtual ASkyLight * GetSkyLight() const override;

		virtual const UIBBLightingCycle * GetLightingCycle() const override;

		virtual void SetLightingCycle(UIBBLightingCycle * NewLightingCycle) override;

		virtual ULevel * GetPreviewLevel() const override;

		virtual void SetPreviewLevel(ULevel * NewPreviewLevel) override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Level Actors")
		TSoftObjectPtr<UWorld> PreviewSublevel;

		UPROPERTY(EditDefaultsOnly, Category = "Level Actors")
		TSoftObjectPtr<ALandscape> Landscape;

		UPROPERTY(EditDefaultsOnly, Category = "Level Actors")
		TSoftObjectPtr<ADirectionalLight> SunLight;

		UPROPERTY(EditDefaultsOnly, Category = "Level Actors")
		TSoftObjectPtr<ASkyLight> SkyLight;

		UPROPERTY(Category = "Lighting Cycle", EditDefaultsOnly, BlueprintReadWrite)
		TSoftClassPtr<UIBBLightingCycle> LightingCycleClass;

		UPROPERTY(EditDefaultsOnly, Category = "World Position", meta = (ClampMin = "-90.0", ClampMax = "90.0"))
		float Latitude;

		UPROPERTY(EditDefaultsOnly, Category = "World Position", meta = (ClampMin = "-180.0", ClampMax = "180.0"))
		float Longitude;

		UPROPERTY()
		UIBBLightingCycle * LightingCycle;

		UPROPERTY()
		ULevel * PreviewLevel;
		
		TArray<AActor *> PreviewActors;

		void CreateLightingCycle();

		void DestroyLightingCycle();

		void InitializeLightingCycle(const UIBBGameClock * NewGameClock);

		UFUNCTION(BlueprintCallable)
		void InitializePreviewLevel();

		void InitializePreviewActors(ULevelStreaming * StreamingPreviewLevel);

		void FinalizeLightingCycle();

		void FinalizePreviewLevel();

		void FinalizePreviewActors();

		void TickLightingCycle();
};