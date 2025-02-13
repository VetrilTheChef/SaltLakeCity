// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "SaltLakeCity/GUI/Models/Interfaces/IBBDateTimeModel.h"
#include "BBDateTimeModelStub.generated.h"

/**
 * 
 */

class UIBBDateTimeWidget;
class UIBBWidget;

UCLASS(NotBlueprintable)

class UBBDateTimeModelStub : public UIBBDateTimeModel
{
	GENERATED_BODY()

	public:
		UBBDateTimeModelStub();
		
		virtual UIBBWidget * GetWidget() const override;

		virtual void Initialize(UIBBDateTimeWidget * NewView, UIBBGameClock * NewGameClock) override;

		virtual void Finalize() override;

		void BroadcastDateUpdate(FText NewDate);

		void BroadcastTimeUpdate(FText NewTime);

	protected:
		UPROPERTY()
		UIBBDateTimeWidget * View;

		UPROPERTY()
		FText Date;

		UPROPERTY()
		FText Time;

		UFUNCTION()
		void UpdateDate(FText NewDate);

		UFUNCTION()
		void UpdateTime(FText NewTime);
};