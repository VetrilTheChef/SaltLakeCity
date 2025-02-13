// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Levels/Interfaces/IBBLevelScriptActor.h"
#include "BBLevelScriptActorStub.generated.h"

/**
 * 
 */

UCLASS()

class ABBLevelScriptActorStub : public AIBBLevelScriptActor
{
	GENERATED_BODY()
	
	public:
		ABBLevelScriptActorStub();

		virtual void PostInitializeComponents() override;

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(const UIBBGameClock * NewGameClock) override;

		virtual void Finalize() override;

		virtual const float GetLatitude() const override;

		void SetLatitude(float NewLatitude);

		virtual const float GetLongitude() const override;

		void SetLongitude(float NewLongitude);

		virtual FVector GetLevelBounds() const override;

		void SetLevelBounds(FVector NewLevelBounds);

		virtual ALandscape * GetLandscape() const override;

		void SetLandscape(ALandscape * NewLandscape);

		virtual ADirectionalLight * GetSunLight() const override;

		virtual void SetSunLight(ADirectionalLight * NewSunLight);

		virtual ASkyLight * GetSkyLight() const override;

		virtual void SetSkyLight(ASkyLight * NewSkyLight);

		virtual const UIBBLightingCycle * GetLightingCycle() const override;

		virtual void SetLightingCycle(UIBBLightingCycle * NewLightingCycle) override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Level Settings", meta = (ClampMin = "-90.0", ClampMax = "90.0"))
		float Latitude;

		UPROPERTY(EditDefaultsOnly, Category = "Level Settings", meta = (ClampMin = "-180.0", ClampMax = "180.0"))
		float Longitude;

		UPROPERTY(EditDefaultsOnly, Category = "Level Settings")
		TSoftObjectPtr<ALandscape> Landscape;

		UPROPERTY(EditDefaultsOnly, Category = "Level Settings")
		FVector LevelBounds;

		UPROPERTY(EditDefaultsOnly, Category = "Level Settings")
		TSoftObjectPtr<ADirectionalLight> SunLight;

		UPROPERTY(EditDefaultsOnly, Category = "Level Settings")
		TSoftObjectPtr<ASkyLight> SkyLight;

		UPROPERTY()
		UIBBLightingCycle * LightingCycle;

		UPROPERTY()
		const UIBBGameClock * GameClock;
};