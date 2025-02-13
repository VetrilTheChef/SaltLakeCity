// SaltLakeCity 4.26

#include "BBDayNightCycle.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "GameStates/Components/Interfaces/IBBGameClock.h"
#include "Levels/BBLevelScriptActor.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"

UBBDayNightCycle::UBBDayNightCycle() :
	Super()
{
	LevelScriptActor = nullptr;
	GameClock = nullptr;
}

void UBBDayNightCycle::Initialize(const AIBBLevelScriptActor * NewLevelScriptActor, const UIBBGameClock * NewGameClock)
{
	verifyf(IsValid(NewLevelScriptActor), TEXT("New Level Script Actor is invalid."));

	LevelScriptActor = NewLevelScriptActor;

	verifyf(IsValid(NewGameClock), TEXT("New Game Clock is invalid."));

	GameClock = NewGameClock;
}

void UBBDayNightCycle::Finalize()
{
	LevelScriptActor = nullptr;
	GameClock = nullptr;
}

void UBBDayNightCycle::Tick()
{
	verifyf(IsValid(LevelScriptActor), TEXT("Level Script Actor is invalid."));
	verifyf(IsValid(GameClock), TEXT("Game Clock is invalid."));

	double Latitude = LevelScriptActor->GetLatitude();
	double Longitude = LevelScriptActor->GetLongitude();

	int Year = GameClock->GetYear();
	int DayOfYear = GameClock->GetDayOfYear();
	int Hour = GameClock->GetHour();
	int Minute = GameClock->GetMinute();
	int Second = GameClock->GetSecond();

	double FractionalYear = GetFractionalYear(Year, DayOfYear, Hour);
	double EquationOfTime = GetEquationOfTime(FractionalYear);
	double Declination = GetDeclination(FractionalYear);
	double LocalTime = GetLocalTime(Hour, Minute, Second);
	double TimeOffset = GetTimeOffset(Longitude, LocalTime, EquationOfTime);
	double TrueSolarTime = GetTrueSolarTime(LocalTime, TimeOffset);
	double HourAngle = GetHourAngle(TrueSolarTime);
	double Elevation = GetElevation(Latitude, Declination, HourAngle);
	double Azimuth = GetAzimuth(Latitude, Declination, HourAngle, Elevation);


	// from FRotator:
	// all angles in degrees
	// Pitch - rotation around the right axis(around Y axis), Looking up and down(0 = Straight Ahead, +Up, -Down)
	// Roll - rotation around the forward axis(around X axis), Tilting your head, 0 = Straight, +Clockwise, -CCW.
	// Yaw - rotation around the up axis(around Z axis), Running in circles 0 = East, +North, -South.

	// Y rotation (pitch) = Zenith
	// Z rotation (yaw) = Azimuth

	// ...well, in theory.
	// testing shows the azimuth maps to the Z axis, and the zenith maps to the Y axis.
	// pitch is 180° at dawn, 270° at noon, 360° at dusk

	ADirectionalLight * SunLight = LevelScriptActor->GetSunLight();

	verifyf(IsValid(SunLight), TEXT("Sun Light is invalid."));

	// also reverse the direction as the sun light points towards the ground
	//FRotator SunRotator = FRotator((float)((90.0 + Elevation) + 180.0), (float)((90.0 - Azimuth) + 180.0), 0.0f);
	FRotator SunRotator = FRotator::MakeFromEuler(FVector(0.0f, (float)Elevation + 180.0f, (float)Azimuth + 180.0f));

	SunLight->SetActorRotation(SunRotator);

	SunLight->SetBrightness(GetSunBrightness((float)(Elevation)));
	//SunLight->SetLightColor(GetSunColor(Elevation));

	ASkyLight * SkyLight = LevelScriptActor->GetSkyLight();

	verifyf(IsValid(SkyLight), TEXT("Sky Light is invalid."));

	USkyLightComponent * SkyLightComponent = SkyLight->GetLightComponent();

	verifyf(IsValid(SkyLightComponent), TEXT("Sky Light Component is invalid."));

	SkyLightComponent->SetIntensity(GetSkyBrightness(Elevation));
	SkyLightComponent->SetLightColor(GetSkyColor(Elevation));
}

// in radians - DayOfYear starts from 1 (1st of January)
double UBBDayNightCycle::GetFractionalYear(const int Year, const int DayOfYear, const int Hour) const
{
	double RadiansPerDay = (2.0 * PI) / ((double)FDateTime::DaysInYear(Year));

	double FractionalDay = (double)(DayOfYear - 1);
	double FractionalHour = ((double)(Hour) - 12.0) / 24.0;
	
	return (RadiansPerDay * (FractionalDay + FractionalHour));
}

// in minutes
double UBBDayNightCycle::GetEquationOfTime(const double FractionalYear) const
{
	double CosFY = FMath::Cos(FractionalYear);
	double SinFY = FMath::Sin(FractionalYear);
	double Cos2FY = FMath::Cos(2.0 * FractionalYear);
	double Sin2FY = FMath::Sin(2.0 * FractionalYear);

	return (229.18 * (0.000075 + (0.001868 * CosFY) - (0.032077 * SinFY) - (0.014615 * Cos2FY) - (0.040849 * Sin2FY)));
}

// in radians
double UBBDayNightCycle::GetDeclination(const double FractionalYear) const
{
	// Spencer formula
	double CosFY = FMath::Cos(FractionalYear);
	double SinFY = FMath::Sin(FractionalYear);
	double Cos2FY = FMath::Cos(2.0 * FractionalYear);
	double Sin2FY = FMath::Sin(2.0 * FractionalYear);
	double Cos3FY = FMath::Cos(3.0 * FractionalYear);
	double Sin3FY = FMath::Sin(3.0 * FractionalYear);

	return (0.006918 - (0.399912 * CosFY) + (0.070257 * SinFY) - (0.006758 * Cos2FY) + (0.000907 * Sin2FY) - (0.002697 * Cos3FY) + (0.00148  * Sin3FY));
}

// in minutes
double UBBDayNightCycle::GetLocalTime(const double Hour, const double Minute, const double Second) const
{
	return (Hour * 60.0) + Minute + (Second / 60.0);
}

// in minutes
double UBBDayNightCycle::GetTimeOffset(const double Longitude, const double LocalTime, const double EquationOfTime) const
{
	// It takes 4 minutes for the Earth to rotate 1 degree of longitude
	// Every 15 degrees of longitude is -60 minutes.

	// Timezone (in minutes) = 60.0 * mod(Longitude, 15)
	// Universal Coordinated Time (in minutes) = local time - timezone offset

	// Local Solar Time Meridian = meridian of the timezone
	// LSTM (from hours) = 15.0 * (local time - UTC)
	// LSTM (from minutes) = 15.0 * (local time - UTC) / 60.0 = (local time - UTC) / 4.0

	// Thus:
	// LSTM (from minutes) = (local time - (local time - timezone offset)) / 4.0 = timezone offset / 4.0
	// LSTM (from minutes) = timezone offset / 4.0 = 60.0 * mod(Longitude, 15) / 4.0 = 15.0 * mod(Longitude, 15)

	double LSTM = 15.0 * ((int)Longitude / 15);

	// Time Offset = 4.0 * (Longitude - LSTM) + EoT)

	return (4.0 * (Longitude - LSTM) + EquationOfTime);
}

// in minutes
double UBBDayNightCycle::GetTrueSolarTime(const double LocalTime, const double TimeOffset) const
{
	return LocalTime + TimeOffset;
}

// in radians
double UBBDayNightCycle::GetHourAngle(const double TrueSolarTime) const
{
	// 15 degrees per hour = 2PI/24 radians per hour = PI/12 radians per hour
	// PI/12 radians per hour = PI/12 radians per 60 minutes = PI/720 radians per minute
	// Hour Angle origin is 0 at 12:00
	// 12:00 = 720 in minutes
	// Hour Angle = radians per minute * (current time in minutes - noon in minutes)

	return (PI/720.0 * (TrueSolarTime - 720.0));
}

// in degrees, measured from the horizon
double UBBDayNightCycle::GetElevation(const double Latitude, const double Declination, const double HourAngle) const
{
	double LatitudeRadians = FMath::DegreesToRadians(Latitude);

	double ElevationRadians = FMath::Acos(FMath::Sin(LatitudeRadians) * FMath::Sin(Declination) + FMath::Cos(LatitudeRadians) * FMath::Cos(Declination) * FMath::Cos(HourAngle));

	return (double)(FMath::Fmod(FMath::RadiansToDegrees(ElevationRadians), 360.0f));
}

// in degrees, clockwise from North
double UBBDayNightCycle::GetAzimuth(const double Latitude, const double Declination, const double HourAngle, const double Elevation) const
{
	double LatitudeRadians = FMath::DegreesToRadians(Latitude);
	double ElevationRadians = FMath::DegreesToRadians(Elevation);

	double AzimuthRadians = PI - FMath::Acos((-1.0 * (FMath::Sin(LatitudeRadians) * FMath::Cos(ElevationRadians) - FMath::Sin(Declination))) / (FMath::Cos(LatitudeRadians) * FMath::Sin(ElevationRadians)));

	float Azimuth = (float)FMath::RadiansToDegrees(AzimuthRadians);

	Azimuth = HourAngle > 0.0 ? FMath::Fmod(Azimuth + 180.0f, 360.0f) : FMath::Fmod(540.0f - Azimuth, 360.0f);

	return (double)Azimuth;
}



// DayColor (0-85-90) = 6000K
// GoldenHour (85-90-92) = 3500K
// BlueHour = Black
// Twilight = Black
// Night = Black

float UBBDayNightCycle::GetSunBrightness(const float SolarElevationAngle) const
{
	return (SunMaxBrightness * SunBrightnessCurve->GetFloatValue(SolarElevationAngle));
}

FLinearColor UBBDayNightCycle::GetSunColor(const float SolarElevationAngle) const
{
	FLinearColor SunColor = SunColorCurve->GetLinearColorValue(SolarElevationAngle);
	SunColor.A = 1.0;

	return SunColor;
}

// DayColor (0-85-90) = 16000K
// GoldenHour (85-90-95) = 6500K ?
// BlueHour (90-95-100) = 24000K, higher intensity
// TwilightColor (95-100-105) = 27000K
// NightColor (100-105-above) = 27000K, low intensity
float UBBDayNightCycle::GetSkyBrightness(const float SolarElevationAngle) const
{
	return (SkyMaxBrightness * SkyBrightnessCurve->GetFloatValue(SolarElevationAngle));
}

FLinearColor UBBDayNightCycle::GetSkyColor(const float SolarElevationAngle) const
{
	FLinearColor SkyColor = SkyColorCurve->GetLinearColorValue(SolarElevationAngle);
	SkyColor.A = 1.0f;

	return SkyColor;
}