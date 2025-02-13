// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "GUI/Controllers/Interfaces/IBBModesController.h"
#include "BBModesController.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBModesController : public UIBBModesController
{
	GENERATED_BODY()

	public:
		UBBModesController();

		virtual void Initialize(UIBBModesWidget * ModesView, UIBBModesModel * ModesModel, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBModesModel * Model;

		UPROPERTY()
		UIBBModesWidget * View;

		virtual void InitializeModel(UIBBModesModel * ModesModel);

		virtual void InitializeView(UIBBModesWidget * ModesView, const UIBBCommandFactory * CommandFactory);

		virtual void FinalizeModel();

		virtual void FinalizeView();
		
		virtual void CreateCommands(UIBBModesWidget & ModesView, const UIBBCommandFactory & CommandFactory);

		void CreatePlayCommand(UIBBModesWidget & ModesView, const UIBBCommandFactory & CommandFactory);

		void CreateBuildCommand(UIBBModesWidget & ModesView, const UIBBCommandFactory & CommandFactory);

		UFUNCTION()
		void UpdateMode(EBBGameMode NewGameMode);
};