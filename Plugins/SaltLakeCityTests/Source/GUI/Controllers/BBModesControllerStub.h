// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "GUI/Controllers/Interfaces/IBBModesController.h"
#include "BBModesControllerStub.generated.h"

/**
 * 
 */

class UIBBGameModeCommand;

UCLASS(NotBlueprintable)

class UBBModesControllerStub : public UIBBModesController
{
	GENERATED_BODY()

	public:
		UBBModesControllerStub();

		virtual void Initialize(UIBBModesWidget * ModesView, UIBBModesModel * ModesModel, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;

		void SetViewCommands(UIBBGameModeCommand * NewBuildModeCommand, UIBBGameModeCommand * NewPlayModeCommand);
		
		EBBGameMode GetActiveGameMode() const;

	protected:
		UPROPERTY()
		UIBBModesModel * Model;

		UPROPERTY()
		UIBBModesWidget * View;

		UPROPERTY()
		UIBBGameModeCommand * BuildModeCommand;

		UPROPERTY()
		UIBBGameModeCommand * PlayModeCommand;

		EBBGameMode ActiveGameMode;

		void InitializeModel(UIBBModesModel * NewModel);

		void FinalizeModel();

		void InitializeView(UIBBModesWidget * NewView);

		void FinalizeView();

		UFUNCTION()
		void UpdateMode(EBBGameMode NewGameMode);
};