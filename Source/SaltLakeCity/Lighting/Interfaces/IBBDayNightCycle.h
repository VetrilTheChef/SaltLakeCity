// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Lighting/Interfaces/IBBLightingCycle.h"
#include "IBBDayNightCycle.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UIBBDayNightCycle : public UIBBLightingCycle
{
	GENERATED_BODY()

	public:
		UIBBDayNightCycle() : Super() { };

		virtual void Initialize(const AIBBLevelScriptActor * LevelScriptActor, const UIBBGameClock * NewGameClock) override PURE_VIRTUAL(UIBBDayNightCycle::Initialize, );

		virtual void Finalize() override PURE_VIRTUAL(UIBBDayNightCycle::Finalize, );

		virtual void Tick() override PURE_VIRTUAL(UIBBDayNightCycle::Tick, );

		virtual double GetFractionalYear(const int Year, const int DayOfYear, const int Hour) const PURE_VIRTUAL(UIBBDayNightCycle::GetFractionalYear, return NAN; );

		virtual double GetEquationOfTime(const double FractionalYear) const PURE_VIRTUAL(UIBBDayNightCycle::GetEquationOfTime, return NAN; );

		virtual double GetDeclination(const double FractionalYear) const PURE_VIRTUAL(UIBBDayNightCycle::GetDeclination, return NAN; );

		virtual double GetLocalTime(const double Hour, const double Minute, const double Second) const PURE_VIRTUAL(UIBBDayNightCycle::GetLocalTime, return NAN; );

		virtual double GetTimeOffset(const double Longitude, const double LocalTime, const double EquationOfTime) const PURE_VIRTUAL(UIBBDayNightCycle::GetTimeOffset, return NAN; );

		virtual double GetTrueSolarTime(const double LocalTime, const double TimeOffset) const PURE_VIRTUAL(UIBBDayNightCycle::GetTrueSolarTime, return NAN; );

		virtual double GetHourAngle(const double TrueSolarTime) const PURE_VIRTUAL(UIBBDayNightCycle::GetHourAngle, return NAN; );

		virtual double GetElevation(const double Latitude, const double Declination, const double HourAngle) const PURE_VIRTUAL(UIBBDayNightCycle::GetZenith, return NAN; );

		virtual double GetAzimuth(const double Latitude, const double Declination, const double HourAngle, const double Elevation) const PURE_VIRTUAL(UIBBDayNightCycle::GetAzimuth, return NAN; );
};