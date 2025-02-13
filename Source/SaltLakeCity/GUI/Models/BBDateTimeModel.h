// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBDateTimeModel.h"
#include "BBDateTimeModel.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBDateTimeModel : public UIBBDateTimeModel
{
	GENERATED_BODY()

	public:
		UBBDateTimeModel();

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual void Initialize(UIBBDateTimeWidget * NewView, UIBBGameClock * NewGameClock) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBDateTimeWidget * View;

		UPROPERTY()
		UIBBGameClock * GameClock;

		void InitializeView(UIBBDateTimeWidget * NewView);

		void InitializeGameClock(UIBBGameClock * NewGameClock);

		void FinalizeView();

		void FinalizeGameClock();

		UFUNCTION()
		void UpdateDate(FText NewDate);

		UFUNCTION()
		void UpdateTime(FText NewTime);
};