// SaltLakeCity 4.26

#include "BBGameClockStub.h"

UBBGameClockStub::UBBGameClockStub()
{
	Year = -1;
	Month = -1;
	Day = -1;
	Hour = -1;
	Minute = -1;
	Second = -1;

	TimeUnit = 0.0f;
};

void UBBGameClockStub::Initialize(int NewYear, int NewMonth, int NewDay, int NewHour, int NewMinute, float NewTimeUnit)
{
	Year = NewYear;
	Month = NewMonth;
	Day = NewDay;
	DayOfYear = FDateTime(Year, Month, Day).GetDayOfYear();
	Hour = NewHour;
	Minute = NewMinute;
	Second = 0;

	TimeUnit = NewTimeUnit;
}

int UBBGameClockStub::GetYear() const
{
	return Year;
}

int UBBGameClockStub::GetMonth() const
{
	return Month;
}

int UBBGameClockStub::GetDay() const
{
	return Day;
}

int UBBGameClockStub::GetDayOfYear() const
{
	return DayOfYear;
}

int UBBGameClockStub::GetHour() const
{
	return Hour;
}

int UBBGameClockStub::GetMinute() const
{
	return Minute;
}

int UBBGameClockStub::GetSecond() const
{
	return Second;
}

float UBBGameClockStub::GetTimeUnit() const
{
	return TimeUnit;
}

void UBBGameClockStub::SetTimeUnit(float NewTimeUnit)
{
	TimeUnit = NewTimeUnit;
}

void UBBGameClockStub::Tick(float DeltaTime)
{
}

void UBBGameClockStub::UpdateDate(FText NewDate)
{
	OnDateUpdate.Broadcast(NewDate);
}

void UBBGameClockStub::UpdateTime(FText NewTime)
{
	OnTimeUpdate.Broadcast(NewTime);
}