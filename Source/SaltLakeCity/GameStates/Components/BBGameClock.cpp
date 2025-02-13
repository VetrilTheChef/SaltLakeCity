// SaltLakeCity 4.24

#include "BBGameClock.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "Engine/World.h"

UBBGameClock::UBBGameClock() :
	Super()
{
	SetTimeUnit(0.0);

	NumberFormat.SetUseGrouping(true);
	NumberFormat.SetMinimumIntegralDigits(2);
	NumberFormat.SetMaximumIntegralDigits(2);

	CurrentDay = -1;
	CurrentMinute = -1;
}

void UBBGameClock::Initialize(int NewYear, int NewMonth, int NewDay, int NewHour, int NewMinute, float NewTimeUnit)
{
	Clock = FDateTime(NewYear, NewMonth, NewDay, NewHour, NewMinute);

	SetTimeUnit(NewTimeUnit);
}

int UBBGameClock::GetYear() const
{
	return Clock.GetYear();
}

int UBBGameClock::GetMonth() const
{
	return Clock.GetMonth();
}

int UBBGameClock::GetDay() const
{
	return Clock.GetDay();
}

int UBBGameClock::GetDayOfYear() const
{
	return Clock.GetDayOfYear();
}

int UBBGameClock::GetHour() const
{
	return Clock.GetHour();
}

int UBBGameClock::GetMinute() const
{
	return Clock.GetMinute();
}

int UBBGameClock::GetSecond() const
{
	return Clock.GetSecond();
}

float UBBGameClock::GetTimeUnit() const
{
	return TimeUnit;
}

void UBBGameClock::SetTimeUnit(float NewTimeUnit)
{
	TimeUnit = FMath::Max(NewTimeUnit, 0.0f);
}

void UBBGameClock::Tick(float DeltaSeconds)
{
	TickClock(DeltaSeconds);

	BroadcastEventIfDateChanged();
	BroadcastEventIfTimeChanged();
}



void UBBGameClock::TickClock(float DeltaSeconds)
{
	int Seconds = (DeltaSeconds * TimeUnit) / 1;
	int Milliseconds = ((DeltaSeconds * TimeUnit - Seconds) * 1000.0) / 1;

	Clock += FTimespan(0, 0, 0, Seconds, Milliseconds);
}

void UBBGameClock::BroadcastEventIfDateChanged()
{
	int Day = Clock.GetDay();

	if (CurrentDay != Day)
	{
		CurrentDay = Day;

		FText Date = FText::Format(NSLOCTEXT("BBDateText", "DateFormatString", "{0}-{1}-{2}"), FText::AsNumber(Day, &NumberFormat), FText::AsNumber(Clock.GetMonth(), &NumberFormat), FText::AsNumber(Clock.GetYear(), &NumberFormat));

		OnDateUpdate.Broadcast(Date);
	}
}

void UBBGameClock::BroadcastEventIfTimeChanged()
{
	int Minute = Clock.GetMinute();

	if (CurrentMinute != Minute)
	{
		CurrentMinute = Minute;

		FText Time = FText::Format(NSLOCTEXT("BBTimeText", "TimeFormatString", "{0}:{1}"), FText::AsNumber(Clock.GetHour(), &NumberFormat), FText::AsNumber(Minute, &NumberFormat));

		OnTimeUpdate.Broadcast(Time);
	}
}