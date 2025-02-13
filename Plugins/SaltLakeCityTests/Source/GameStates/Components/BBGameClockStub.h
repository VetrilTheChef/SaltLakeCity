// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GameStates/Components/Interfaces/IBBGameClock.h"
#include "BBGameClockStub.generated.h"

UCLASS(NotBlueprintable)

class UBBGameClockStub : public UIBBGameClock
{
	GENERATED_BODY()

	public:
		UBBGameClockStub();

		virtual void Initialize(int NewYear, int NewMonth, int NewDay, int NewHour, int NewMinute, float NewTimeUnit) override;

		virtual int GetYear() const override;

		virtual int GetMonth() const override;

		virtual int GetDay() const override;

		virtual int GetDayOfYear() const override;

		virtual int GetHour() const override;

		virtual int GetMinute() const override;

		virtual int GetSecond() const override;

		virtual float GetTimeUnit() const override;

		virtual void SetTimeUnit(float NewTimeUnit) override;

		virtual void Tick(float DeltaTime) override;

		void UpdateDate(FText NewDate);

		void UpdateTime(FText NewTime);

	protected:
		UPROPERTY()
		int Year;

		UPROPERTY()
		int Month;

		UPROPERTY()
		int Day;

		UPROPERTY()
		int DayOfYear;

		UPROPERTY()
		int Hour;

		UPROPERTY()
		int Minute;

		UPROPERTY()
		int Second;

		UPROPERTY()
		float TimeUnit;
};