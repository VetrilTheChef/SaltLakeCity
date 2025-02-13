// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/BBHUD.h"
#include "GUI/Controllers/Interfaces/IBBDateTimeController.h"
#include "BBDateTimeController.generated.h"

/**
 * 
 */

class UIBBCommandFactory;
class UIBBDateTimeModel;
class UIBBDateTimeWidget;
class UBBGUIModel;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBDateTimeController : public UIBBDateTimeController
{
	GENERATED_BODY()

	public:
		UBBDateTimeController();

		virtual void Initialize(UIBBDateTimeWidget * DateTimeView, UIBBDateTimeModel * DateTimeModel, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;

		virtual float GetSlowMotionTimeDilation() override;

		virtual float GetPlayTimeDilation() override;

		virtual float GetFastForwardTimeDilation() override;

	protected:
		UPROPERTY()
		UIBBDateTimeModel * Model;

		UPROPERTY()
		UIBBDateTimeWidget * View;

		UPROPERTY(EditAnywhere, Category = "Game Speeds")
		float SlowMotionTimeDilation;

		UPROPERTY(EditAnywhere, Category = "Game Speeds")
		float PlayTimeDilation;

		UPROPERTY(EditAnywhere, Category = "Game Speeds")
		float FastForwardTimeDilation;

		virtual void InitializeModel(UIBBDateTimeModel * DateTimeModel);

		virtual void InitializeView(UIBBDateTimeWidget * DateTimeView, const UIBBCommandFactory * CommandFactory);

		virtual void FinalizeModel();

		virtual void FinalizeView();
		
		virtual void CreateCommands(UIBBDateTimeWidget & DateTimeView, const UIBBCommandFactory & CommandFactory);

		void CreatePauseCommand(UIBBDateTimeWidget & DateTimeView, const UIBBCommandFactory & CommandFactory);

		void CreateSlowMotionCommand(UIBBDateTimeWidget & DateTimeView, const UIBBCommandFactory & CommandFactory);

		void CreatePlayCommand(UIBBDateTimeWidget & DateTimeView, const UIBBCommandFactory & CommandFactory);

		void CreateFastForwardCommand(UIBBDateTimeWidget & DateTimeView, const UIBBCommandFactory & CommandFactory);
};