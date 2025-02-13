// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameStates/Components/BBGameClockStub.h"
#include "Levels/BBLevelScriptActorStub.h"
#include "Lighting/BBDayNightCycle.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBDayNightCycleSpec, "SaltLakeCity.Lighting.DayNightCycle", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBLevelScriptActorStub * LevelScriptActor = nullptr;

	UPROPERTY()
	TArray<UClass *> DayNightCycleClasses;

	// SUT
	UPROPERTY()
	UBBDayNightCycle * DayNightCycle = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBDayNightCycleSpec)

void UBBDayNightCycleSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBDayNightCycle>(FString(TEXT("/Game/Lighting/DayNight")), DayNightCycleClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		ULevel * CurrentLevel = TestWorld->GetCurrentLevel();

		UTEST_TRUE("Current Level is valid", IsValid(CurrentLevel))

		LevelScriptActor =  TestWorld->SpawnActor<ABBLevelScriptActorStub>(ABBLevelScriptActorStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Level Script Actor is valid", IsValid(LevelScriptActor))

		CurrentLevel->LevelScriptActor = LevelScriptActor;

		return true;
	});

	AfterEach([this]()
	{
		DayNightCycle = nullptr;
		
		TestWorld->DestroyActor(LevelScriptActor);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & DayNightCycleClass : DayNightCycleClasses)
	{
		Describe("[" + DayNightCycleClass->GetName() + "]", [this, DayNightCycleClass]()
		{
			It("Given a new tick, expect the day night cycle to update its sunlight.", [this, DayNightCycleClass]()
			{
				struct FBBTickTestCase
				{
					public:
						FBBTickTestCase() :
							Latitude(0.0),
							Longitude(0.0),
							DateTime(FDateTime()),
							Azimuth(0.0),
							Zenith(0.0)
						{};

						FBBTickTestCase(double NewLatitude, double NewLongitude, FDateTime NewDateTime, double NewAzimuth, double NewZenith) :
							Latitude(NewLatitude),
							Longitude(NewLongitude),
							DateTime(NewDateTime),
							Azimuth(NewAzimuth),
							Zenith(NewZenith)
						{};

						double Latitude = 0.0f;

						double Longitude = 0.0f;

						FDateTime DateTime = FDateTime();

						double Azimuth = 0.0f;

						double Zenith = 0.0f;
				};

				TArray<FBBTickTestCase> TestCases;

				TestCases.Emplace(FBBTickTestCase(40.0, -100.0, FDateTime(2022, 8, 25, 6, 0, 0, 0), 30.044912, 18.575628));
				TestCases.Emplace(FBBTickTestCase(60.0, 30.0, FDateTime(2022, 4, 5, 12, 30, 0, 0), 57.035748, 27.949980));
				TestCases.Emplace(FBBTickTestCase(-35.0, -55.0, FDateTime(2022, 11, 19, 16, 07, 0, 0), 101.552757, 56.241100));
				TestCases.Emplace(FBBTickTestCase(9.0, 120.0, FDateTime(2022, 6, 13, 9, 27, 0, 0), 87.418111, 146.753693));
				TestCases.Emplace(FBBTickTestCase(-72.0, 57.0, FDateTime(2022, 12, 25, 18, 15, 0, 0), 52.792908, 136.349243));

				float MaxError = 0.1f;

				FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
				SpawnParameters.bNoFail = true;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				DayNightCycle = NewObject<UBBDayNightCycle>(TestWorld, DayNightCycleClass);

				UTEST_TRUE("Day Night Cycle is valid", IsValid(DayNightCycle))

				ASkyLight * SkyLight = TestWorld->SpawnActor<ASkyLight>(ASkyLight::StaticClass(), SpawnParameters);

				UTEST_TRUE("Sky Light is valid", IsValid(SkyLight))

				ADirectionalLight * SunLight = TestWorld->SpawnActor<ADirectionalLight>(ADirectionalLight::StaticClass(), SpawnParameters);

				UTEST_TRUE("Sun Light is valid", IsValid(SunLight))

				const TSet<UActorComponent *> Components = SunLight->GetComponents();

				for (UActorComponent * const & Component : Components)
				{
					USceneComponent * SceneComponent = Cast<USceneComponent>(Component);

					if (IsValid(SceneComponent))
					{
						SceneComponent->SetMobility(EComponentMobility::Movable);
					}
				}

				LevelScriptActor->SetSkyLight(SkyLight);
				LevelScriptActor->SetSunLight(SunLight);

				UBBGameClockStub * GameClock = NewObject<UBBGameClockStub>(LevelScriptActor, UBBGameClockStub::StaticClass());

				UTEST_TRUE("Game Clock is valid", IsValid(GameClock))

				for (FBBTickTestCase & TestCase : TestCases)
				{
					LevelScriptActor->SetLatitude(TestCase.Latitude);
					LevelScriptActor->SetLongitude(TestCase.Longitude);

					GameClock->Initialize(TestCase.DateTime.GetYear(),
						TestCase.DateTime.GetMonth(),
						TestCase.DateTime.GetDay(),
						TestCase.DateTime.GetHour(),
						TestCase.DateTime.GetMinute(),
						1.0f);

					DayNightCycle->Initialize(LevelScriptActor, GameClock);

					DayNightCycle->Tick();

					FRotator SunRotator = SunLight->GetActorRotation();
					//FRotator ResultRotator = FRotator::MakeFromEuler(FVector(0.0f, (float)(-(TestCase.Zenith + 90.0)), (float)(90.0 - TestCase.Azimuth))); 
					FRotator ResultRotator = FRotator::MakeFromEuler(FVector(0.0f, ((float)TestCase.Zenith + 180.0f), ((float)TestCase.Azimuth + 180.0f)));

					TEST_TRUE(SunRotator.Equals(ResultRotator, MaxError));
					
					DayNightCycle->Finalize();
				}

				TestWorld->DestroyActor(SkyLight);
				TestWorld->DestroyActor(SunLight);

				return true;
			});

			It("Given a new date, expect the day night cycle to return the fractional year.", [this, DayNightCycleClass]()
			{
				struct FBBFractionalYearTestCase
				{
					public:
						FBBFractionalYearTestCase() :
							Year(0),
							DayOfYear(0),
							Hour(0),
							Result(0.0)
						{};

						FBBFractionalYearTestCase(int NewYear, int NewDayOfYear, int Hour, double NewResult) :
							Year(NewYear),
							DayOfYear(NewDayOfYear),
							Hour(Hour),
							Result(NewResult)
						{};

						int Year = 0;

						int DayOfYear = 0;

						int Hour = 0;

						double Result = 0.0;
				};

				TArray<FBBFractionalYearTestCase> TestCases;
				TestCases.Emplace(FBBFractionalYearTestCase(2022, 15, 5, 0.23597807831084474885844748858441));
				TestCases.Emplace(FBBFractionalYearTestCase(2010, 171, 16, 2.9292841088799086757990867579901));
				TestCases.Emplace(FBBFractionalYearTestCase(2018, 296, 8, 5.0753218301748858447488584474873));
				TestCases.Emplace(FBBFractionalYearTestCase(2000, 46, 22, 0.77967577238501821493624772313297));
				TestCases.Emplace(FBBFractionalYearTestCase(2031, 261, 0, 4.467086540182191780821917808218));

				double MaxError = 0.000001;

				DayNightCycle = NewObject<UBBDayNightCycle>(TestWorld, DayNightCycleClass);

				UTEST_TRUE("Day Night Cycle is valid", IsValid(DayNightCycle))

				for (FBBFractionalYearTestCase & TestCase : TestCases)
				{
					TEST_TRUE(FMath::IsNearlyEqual(DayNightCycle->GetFractionalYear(TestCase.Year, TestCase.DayOfYear, TestCase.Hour), TestCase.Result, MaxError))
				}

				return true;
			});

			It("Given a new fractional year, expect the day night cycle to return the equation of time.", [this, DayNightCycleClass]()
			{
				struct FBBEquationOfTimeTestCase
				{
				public:
					FBBEquationOfTimeTestCase() :
						FractionalYear(0),
						Result(0.0)
					{};

					FBBEquationOfTimeTestCase(double NewFractionalYear, double NewResult) :
						FractionalYear(NewFractionalYear),
						Result(NewResult)
					{};

					double FractionalYear = 0.0;

					double Result = 0.0;
				};
				
				TArray<FBBEquationOfTimeTestCase> TestCases;
				TestCases.Emplace(FBBEquationOfTimeTestCase(2.6952461562814207650273224043716, 1.2565935416));
				TestCases.Emplace(FBBEquationOfTimeTestCase(4.7166925318301369863013698630137, 10.5637304786));
				TestCases.Emplace(FBBEquationOfTimeTestCase(1.527878394325136612021857923497, -4.2548771629));
				TestCases.Emplace(FBBEquationOfTimeTestCase(5.9226746746311475409836065573761, 6.5312090926));
				TestCases.Emplace(FBBEquationOfTimeTestCase(4.1716230316967213114754098360649, -0.2560104107));

				double MaxError = 0.75;

				DayNightCycle = NewObject<UBBDayNightCycle>(TestWorld, DayNightCycleClass);

				UTEST_TRUE("Day Night Cycle is valid", IsValid(DayNightCycle))

				for (FBBEquationOfTimeTestCase & TestCase : TestCases)
				{
					TEST_TRUE(FMath::IsNearlyEqual(DayNightCycle->GetEquationOfTime(TestCase.FractionalYear), TestCase.Result, MaxError))
				}

				return true;
			});

			It("Given a new fractional year, expect the day night cycle to return the declination.", [this, DayNightCycleClass]()
			{
				struct FBBDeclinationTestCase
				{
				public:
					FBBDeclinationTestCase() :
						Latitude(0.0),
						Longitude(0.0),
						FractionalYear(0),
						Result(0.0)
					{};

					FBBDeclinationTestCase(double NewLatitude, double NewLongitude, double NewFractionalYear, double NewResult) :
						Latitude(NewLatitude),
						Longitude(NewLongitude),
						FractionalYear(NewFractionalYear),
						Result(NewResult)
					{};

					double Latitude = 0.0;

					double Longitude = 0.0;

					double FractionalYear = 0.0;

					double Result = 0.0;
				};
				
				TArray<FBBDeclinationTestCase> TestCases;
				TestCases.Emplace(FBBDeclinationTestCase(40.0, -100.0, 4.6464011893545662100456621004555, -0.03822271)); // Sep 28 2022, 10:00, DoY 271, EOT 9.38
				TestCases.Emplace(FBBDeclinationTestCase(-56.0, 73.0, 2.276578785892465753424657534246, 0.32375858)); // May 13 2013, 18:00, DoY 133, EOT 3.66
				TestCases.Emplace(FBBDeclinationTestCase(19.0, -36.0, 0.06866869187978142076502732240436, -0.39479348)); // Jan 5 2040 LEAP, 12:00, DoY 5, EOT -5.19
				TestCases.Emplace(FBBDeclinationTestCase(74.0, 80.0, 5.6649083966536529680365296803638, -0.36529741)); // Nov 26 2006, 14:00, DoY 330, EOT 12.8
				TestCases.Emplace(FBBDeclinationTestCase(-30.0, -47, 4.1278232239480593607305936073049, 0.1638864)); // Aug 29 2019, 07:00, DoY 241, EOT -1.05

				double MaxError = 0.01;

				DayNightCycle = NewObject<UBBDayNightCycle>(TestWorld, DayNightCycleClass);

				UTEST_TRUE("Day Night Cycle is valid", IsValid(DayNightCycle))

				for (FBBDeclinationTestCase & TestCase : TestCases)
				{
					TEST_TRUE(FMath::IsNearlyEqual(DayNightCycle->GetDeclination(TestCase.FractionalYear), TestCase.Result, MaxError))
				}

				return true;
			});

			It("Given a new longitude, local time and equation of time, expect the day night cycle to return the time offset.", [this, DayNightCycleClass]()
			{
				struct FBBTimeOffsetTestCase
				{
					public:
						FBBTimeOffsetTestCase() :
							Longitude(0.0),
							LocalTime(0.0),
							EquationOfTime(0.0),
							Result(0.0)
						{};

						FBBTimeOffsetTestCase(double NewLongitude, double NewLocalTime, double NewEquationOfTime, double NewResult) :
							Longitude(NewLongitude),
							LocalTime(NewLocalTime),
							EquationOfTime(NewEquationOfTime),
							Result(NewResult)
						{};

						double Longitude = 0.0;

						double LocalTime = 0.0;

						double EquationOfTime = 0.0;

						double Result = 0.0;
				};

				TArray<FBBTimeOffsetTestCase> TestCases;
				TestCases.Emplace(FBBTimeOffsetTestCase(34.0, 575.0, -9.73, 6.27));
				TestCases.Emplace(FBBTimeOffsetTestCase(-64.4, 832.0, -6.54, -24.14));
				TestCases.Emplace(FBBTimeOffsetTestCase(0.0, 0.0, -13.15, -13.15));
				TestCases.Emplace(FBBTimeOffsetTestCase(-111.3, 1127.0, 1.44, -23.76));
				TestCases.Emplace(FBBTimeOffsetTestCase(121.3, 1321.0, 12.3, 17.5));

				double MaxError = 0.01;

				DayNightCycle = NewObject<UBBDayNightCycle>(TestWorld, DayNightCycleClass);

				UTEST_TRUE("Day Night Cycle is valid", IsValid(DayNightCycle))

				for (FBBTimeOffsetTestCase & TestCase : TestCases)
				{
					TEST_TRUE(FMath::IsNearlyEqual(DayNightCycle->GetTimeOffset(TestCase.Longitude, TestCase.LocalTime, TestCase.EquationOfTime), TestCase.Result, MaxError))
				}

				return true;
			});

			It("Given a new local time and time offset, expect the day night cycle to return the true solar time.", [this, DayNightCycleClass]()
			{
				struct FBBTrueSolarTimeTestCase
				{
				public:
					FBBTrueSolarTimeTestCase() :
						LocalTime(0.0),
						TimeOffset(0.0),
						Result(0.0)
					{};

					FBBTrueSolarTimeTestCase(double NewLocalTime, double NewTimeOffset, double NewResult) :
						LocalTime(NewLocalTime),
						TimeOffset(NewTimeOffset),
						Result(NewResult)
					{};

					double LocalTime = 0.0;

					double TimeOffset = 0.0;

					double Result = 0.0;
				};

				TArray<FBBTrueSolarTimeTestCase> TestCases;
				TestCases.Emplace(FBBTrueSolarTimeTestCase(723.7, -6.54, 717.16)); // 12:03:46
				TestCases.Emplace(FBBTrueSolarTimeTestCase(326.2, 11.81, 338.01)); // 05:26:12
				TestCases.Emplace(FBBTrueSolarTimeTestCase(1215.85, -20.63, 1195.22)); // 20:15:51
				TestCases.Emplace(FBBTrueSolarTimeTestCase(638.07, 0.0, 638.07)); // 10:38:04
				TestCases.Emplace(FBBTrueSolarTimeTestCase(1022.05, 23.42, 1045.47)); // 17:02:30

				double MaxError = 0.01;

				DayNightCycle = NewObject<UBBDayNightCycle>(TestWorld, DayNightCycleClass);

				UTEST_TRUE("Day Night Cycle is valid", IsValid(DayNightCycle))

				for (FBBTrueSolarTimeTestCase & TestCase : TestCases)
				{
					TEST_TRUE(FMath::IsNearlyEqual(DayNightCycle->GetTrueSolarTime(TestCase.LocalTime, TestCase.TimeOffset), TestCase.Result, MaxError))
				}

				return true;
			});

			It("Given a new true solar time, expect the day night cycle to return the hour angle.", [this, DayNightCycleClass]()
			{
				struct FBBHourAngleTestCase
				{
				public:
					FBBHourAngleTestCase() :
						TrueSolarTime(0.0),
						Result(0.0)
					{};

					FBBHourAngleTestCase(double NewTrueSolarTime, double NewResult) :
						TrueSolarTime(NewTrueSolarTime),
						Result(NewResult)
					{};

					double TrueSolarTime = 0.0;

					double Result = 0.0;
				};

				TArray<FBBHourAngleTestCase> TestCases;
				TestCases.Emplace(FBBHourAngleTestCase(0.0, -3.1415927));
				TestCases.Emplace(FBBHourAngleTestCase(360.0, -1.5707964));
				TestCases.Emplace(FBBHourAngleTestCase(720.0, 0.0));
				TestCases.Emplace(FBBHourAngleTestCase(1080.0, 1.5707964));
				TestCases.Emplace(FBBHourAngleTestCase(1440.0, 3.1415927));

				double MaxError = 0.001;

				DayNightCycle = NewObject<UBBDayNightCycle>(TestWorld, DayNightCycleClass);

				UTEST_TRUE("Day Night Cycle is valid", IsValid(DayNightCycle))

				for (FBBHourAngleTestCase & TestCase : TestCases)
				{
					TEST_TRUE(FMath::IsNearlyEqual(DayNightCycle->GetHourAngle(TestCase.TrueSolarTime), TestCase.Result, MaxError))
				}

				return true;
			});

			It("Given a new latitude, declination, and hour angle, expect the day night cycle to return the elevation.", [this, DayNightCycleClass]()
			{
				struct FBBElevationTestCase
				{
					public:
						FBBElevationTestCase() :
							Latitude(0.0),
							Declination(0.0),
							HourAngle(0.0),
							Result(0.0)
						{};

						FBBElevationTestCase(double NewLatitude, double NewDeclination, double NewHourAngle, double NewResult) :
							Latitude(NewLatitude),
							Declination(NewDeclination),
							HourAngle(NewHourAngle),
							Result(NewResult)
						{};

						double Latitude = 0.0;

						double Declination = 0.0;

						double HourAngle = 0.0;

						double Result = 0.0;
				};

				TArray<FBBElevationTestCase> TestCases;
				TestCases.Emplace(FBBElevationTestCase(123.1, 0.21, 2.9, 46.11416));
				TestCases.Emplace(FBBElevationTestCase(-47.5, -0.35, 0.0, 27.44645));
				TestCases.Emplace(FBBElevationTestCase(15.7, -0.8, -1.4, 94.59533));
				TestCases.Emplace(FBBElevationTestCase(0.0, 0.09, 0.7, 40.38155));
				TestCases.Emplace(FBBElevationTestCase(-152.6, 0.38, -3.0, 49.79427));

				double MaxError = 0.01;

				DayNightCycle = NewObject<UBBDayNightCycle>(TestWorld, DayNightCycleClass);

				UTEST_TRUE("Day Night Cycle is valid", IsValid(DayNightCycle))

				for (FBBElevationTestCase & TestCase : TestCases)
				{
					TEST_TRUE(FMath::IsNearlyEqual(DayNightCycle->GetElevation(TestCase.Latitude, TestCase.Declination, TestCase.HourAngle), TestCase.Result, MaxError))
				}

				return true;
			});

			It("Given a new latitude, declination, hour angle, and elevation, expect the day night cycle to return the azimuth.", [this, DayNightCycleClass]()
			{
				struct FBBAzimuthTestCase
				{
				public:
					FBBAzimuthTestCase() :
						Latitude(0.0),
						Declination(0.0),
						HourAngle(0.0),
						Elevation(0.0),
						Result(0.0)
					{};

					FBBAzimuthTestCase(double NewLatitude, double NewDeclination, double NewHourAngle, double NewElevation, double NewResult) :
						Latitude(NewLatitude),
						Declination(NewDeclination),
						HourAngle(NewHourAngle),
						Elevation(NewElevation),
						Result(NewResult)
					{};

					double Latitude = 0.0;

					double Declination = 0.0;

					double HourAngle = 0.0;

					double Elevation = 0.0;

					double Result = 0.0;
				};

				TArray<FBBAzimuthTestCase> TestCases;
				TestCases.Emplace(FBBAzimuthTestCase(123.1, 0.21, 1.0, 46.11416, 341.05928));
				TestCases.Emplace(FBBAzimuthTestCase(-47.5, -0.35, -1.0, 27.44645, 0.0));
				TestCases.Emplace(FBBAzimuthTestCase(15.7, -0.8, 1.0, 94.59533, 223.5339));
				TestCases.Emplace(FBBAzimuthTestCase(0.0, 0.09, -1.0, 40.38155, 82.02578));
				TestCases.Emplace(FBBAzimuthTestCase(-152.6, 0.38, 1.0, 49.79427, 189.8804));

				double MaxError = 0.01;

				DayNightCycle = NewObject<UBBDayNightCycle>(TestWorld, DayNightCycleClass);

				UTEST_TRUE("Day Night Cycle is valid", IsValid(DayNightCycle))

				for (FBBAzimuthTestCase & TestCase : TestCases)
				{
					TEST_TRUE(FMath::IsNearlyEqual(DayNightCycle->GetAzimuth(TestCase.Latitude, TestCase.Declination, TestCase.HourAngle, TestCase.Elevation), TestCase.Result, MaxError))
				}

				return true;
			});
		});
	}
}