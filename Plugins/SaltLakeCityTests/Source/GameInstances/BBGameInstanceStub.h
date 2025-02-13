// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "BBGameInstanceStub.generated.h"

/**
*
*/

UCLASS(NotBlueprintable)

class UBBGameInstanceStub : public UIBBGameInstance
{
	GENERATED_BODY()

	public:
		UBBGameInstanceStub();

		void Clone(UGameInstance * Other);

		void Unclone();

		virtual AIBBGameMode * GetGameMode() const override;

		void SetGameMode(AIBBGameMode * NewGameMode);

		virtual AIBBGameState * GetGameState() const override;

		void SetGameState(AIBBGameState * NewGameState);

		virtual AIBBHUD * GetHUD() const override;

		void SetHUD(AIBBHUD * NewHUD);

		virtual AIBBPlayerController * GetPlayerController() const override;

		void SetPlayerController(AIBBPlayerController * NewPlayerController);

		virtual const UIBBCommandFactory * GetCommandFactory() const override;

		void SetCommandFactory(UIBBCommandFactory * NewCommandFactory);

		virtual const UIBBComponentFactory * GetComponentFactory() const override;

		void SetComponentFactory(UIBBComponentFactory * NewComponentFactory);

		const UIBBSpecificationFactory * GetSpecificationFactory() const;

		void SetSpecificationFactory(UIBBSpecificationFactory * NewSpecificationFactory);

		void SetWorldContext(FWorldContext * NewWorldContext);

	protected:
		UPROPERTY()
		AIBBGameMode * GameMode;

		UPROPERTY()
		AIBBGameState * GameState;

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		AIBBPlayerController * PlayerController;

		UPROPERTY()
		UIBBCommandFactory * CommandFactory;

		UPROPERTY()
		UIBBComponentFactory * ComponentFactory;

		UPROPERTY()
		UIBBSpecificationFactory * SpecificationFactory;
};