// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "SaltLakeCity/GUI/Controllers/Interfaces/IBBDateTimeController.h"
#include "BBDateTimeControllerStub.generated.h"

/**
 * 
 */

class UIBBCommandFactory;
class UIBBDateTimeModel;
class UIBBDateTimeWidget;

UCLASS(NotBlueprintable)

class UBBDateTimeControllerStub : public UIBBDateTimeController
{
	GENERATED_BODY()

	public:
		UBBDateTimeControllerStub();

		virtual void Initialize(UIBBDateTimeWidget * DateTimeView, UIBBDateTimeModel * DateTimeModel, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;

		virtual float GetSlowMotionTimeDilation() override;

		virtual float GetPlayTimeDilation() override;

		virtual float GetFastForwardTimeDilation() override;

		FText GetDate();

		void SetDate(FText NewDate);

		FText GetTime();

		void SetTime(FText NewTime);

	protected:
		UPROPERTY()
		UIBBDateTimeModel * Model;

		UPROPERTY()
		UIBBDateTimeWidget * View;

		UPROPERTY()
		FText CurrentDate;

		UPROPERTY()
		FText CurrentTime;

		virtual void InitializeModel(UIBBDateTimeModel * DateTimeModel);

		virtual void FinalizeModel();
		
		virtual void InitializeView(UIBBDateTimeWidget * DateTimeView, const UIBBCommandFactory * CommandFactory);

		virtual void FinalizeView();
};