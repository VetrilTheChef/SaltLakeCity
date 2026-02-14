// SaltLakeCity 5.7

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

		void Clone(UGameInstance* Other);

		void Unclone();

		virtual AIBBGameMode* GetGameMode() const override;

		void SetGameMode(AIBBGameMode* NewGameMode);

		virtual AIBBGameState* GetGameState() const override;

		void SetGameState(AIBBGameState* NewGameState);

		virtual AIBBHUD* GetHUD() const override;

		void SetHUD(AIBBHUD* NewHUD);

		virtual AIBBPlayerController* GetPlayerController() const override;

		void SetPlayerController(AIBBPlayerController* NewPlayerController);

		virtual UIBBWidgetManager* GetWidgetManager() const override;

		void SetWidgetManager(UIBBWidgetManager* NewWidgetManager);

		virtual const UIBBCommandFactory* GetCommandFactory() const override;

		void SetCommandFactory(UIBBCommandFactory* NewCommandFactory);

		virtual const UIBBComponentFactory* GetComponentFactory() const override;

		void SetComponentFactory(UIBBComponentFactory* NewComponentFactory);

		const UIBBSpecificationFactory* GetSpecificationFactory() const;

		void SetSpecificationFactory(UIBBSpecificationFactory* NewSpecificationFactory);

		void SetWorldContext(FWorldContext* NewWorldContext);

	protected:
		TWeakObjectPtr<AIBBGameMode> GameMode;

		TWeakObjectPtr<AIBBGameState> GameState;

		TWeakObjectPtr<AIBBHUD> HUD;

		TWeakObjectPtr<AIBBPlayerController> PlayerController;

		TWeakObjectPtr<UIBBWidgetManager> WidgetManager;

		TWeakObjectPtr<UIBBCommandFactory> CommandFactory;

		TWeakObjectPtr<UIBBComponentFactory> ComponentFactory;

		TWeakObjectPtr<UIBBSpecificationFactory> SpecificationFactory;
};