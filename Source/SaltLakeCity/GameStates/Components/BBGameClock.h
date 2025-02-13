// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "GameStates/Components/Interfaces/IBBGameClock.h"
#include "BBGameClock.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBGameClock : public UIBBGameClock
{
	GENERATED_BODY()

	public:
		UBBGameClock();

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

	protected:
		FDateTime Clock;

		FNumberFormattingOptions NumberFormat;

		float TimeUnit;

		int CurrentDay;

		int CurrentMinute;

		virtual void TickClock(float DeltaTime);

		void BroadcastEventIfDateChanged();

		void BroadcastEventIfTimeChanged();
};