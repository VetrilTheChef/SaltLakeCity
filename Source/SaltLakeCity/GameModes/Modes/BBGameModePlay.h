// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Modes/Interfaces/IBBGameModePlay.h"
#include "BBGameModePlay.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBGameModePlay : public UIBBGameModePlay
{
	GENERATED_BODY()

	public:
		UBBGameModePlay();

		virtual void Initialize(AIBBPlayerController * NewController, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, AIBBGameState * NewGameState) override;

		virtual void Finalize() override;

		virtual void Activate() override;

		virtual void Deactivate() override;

	protected:
		UPROPERTY()
		AIBBPlayerController * Controller;

		UPROPERTY()
		AIBBGameState * GameState;

		UPROPERTY()
		UInputComponent * InputComponent;

		void CreateInputComponent(AIBBPlayerController * PlayerController);

		void DestroyInputComponent();

		void PushInputComponent();

		void PopInputComponent();
};