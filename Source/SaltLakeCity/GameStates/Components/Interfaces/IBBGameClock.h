// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "IBBGameClock.generated.h"

/**
*
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIBBGameClock_DateUpdate, FText, NewDate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIBBGameClock_TimeUpdate, FText, NewTime);

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBGameClock : public UObject
{
	GENERATED_BODY()

	public:
		UIBBGameClock() : Super() { };

		virtual void Initialize(int NewYear, int NewMonth, int NewDay, int NewHour, int NewMinute, float NewTimeUnit) PURE_VIRTUAL(UIBBGameClock::Initialize, );

		virtual int GetYear() const PURE_VIRTUAL(UIBBGameClock::GetYear, return -1;);

		virtual int GetMonth() const PURE_VIRTUAL(UIBBGameClock::GetMonth, return -1;);

		virtual int GetDay() const PURE_VIRTUAL(UIBBGameClock::GetDay, return -1;);

		virtual int GetDayOfYear() const PURE_VIRTUAL(UIBBGameClock::GetDayOfYear, return -1;);

		virtual int GetHour() const PURE_VIRTUAL(UIBBGameClock::GetHour, return -1;);

		virtual int GetMinute() const PURE_VIRTUAL(UIBBGameClock::GetMinute, return -1;);

		virtual int GetSecond() const PURE_VIRTUAL(UIBBGameClock::GetSecond, return -1;);

		virtual float GetTimeUnit() const PURE_VIRTUAL(UIBBGameClock::GetTimeUnit, return 1.0;);

		virtual void SetTimeUnit(float NewTimeUnit) PURE_VIRTUAL(UIBBGameClock::SetTimeUnit, );

		virtual void Tick(float DeltaTime) PURE_VIRTUAL(UIBBGameClock::Tick, );

		FIBBGameClock_DateUpdate OnDateUpdate;

		FIBBGameClock_TimeUpdate OnTimeUpdate;
};