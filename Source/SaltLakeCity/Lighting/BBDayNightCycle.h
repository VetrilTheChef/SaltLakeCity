// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Lighting/Interfaces/IBBDayNightCycle.h"
#include "BBDayNightCycle.generated.h"

/**
*
*/

class UCurveFloat;
class UCurveLinearColor;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBDayNightCycle : public UIBBDayNightCycle
{
	GENERATED_BODY()

	public:
		UBBDayNightCycle();

		virtual void Initialize(const AIBBLevelScriptActor * LevelScriptActor, const UIBBGameClock * NewGameClock) override;

		virtual void Finalize() override;

		virtual void Tick() override;

		virtual double GetFractionalYear(const int Year, const int DayOfYear, const int Hour) const override;

		virtual double GetEquationOfTime(const double FractionalYear) const override;

		virtual double GetDeclination(const double FractionalYear) const override;

		virtual double GetLocalTime(const double Hour, const double Minute, const double Second) const override;

		virtual double GetTimeOffset(const double Longitude, const double LocalTime, const double EquationOfTime) const override;

		virtual double GetTrueSolarTime(const double LocalTime, const double TimeOffset) const override;

		virtual double GetHourAngle(const double TrueSolarTime) const override;

		virtual double GetElevation(const double Latitude, const double Declination, const double HourAngle) const override;

		virtual double GetAzimuth(const double Latitude, const double Declination, const double HourAngle, const double Elevation) const override;

	protected:
		UPROPERTY(Category = "Sun Settings", EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float SunMaxBrightness;

		UPROPERTY(Category = "Sun Settings", EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UCurveFloat * SunBrightnessCurve;

		UPROPERTY(Category = "Sun Settings", EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UCurveLinearColor * SunColorCurve;

		UPROPERTY(Category = "Sky Settings", EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float SkyMaxBrightness;

		UPROPERTY(Category = "Sky Settings", EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UCurveFloat * SkyBrightnessCurve;

		UPROPERTY(Category = "Sky Settings", EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UCurveLinearColor * SkyColorCurve;

		//UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		//BBSkySphere SkySphere;

		UPROPERTY()
		const AIBBLevelScriptActor * LevelScriptActor;

		UPROPERTY()
		const UIBBGameClock * GameClock;

		float GetSunBrightness(const float SolarElevationAngle) const;

		FLinearColor GetSunColor(const float SolarElevationAngle) const;

		float GetSkyBrightness(const float SolarElevationAngle) const;

		FLinearColor GetSkyColor(const float SolarElevationAngle) const;
};