// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GameModes/Modes/Interfaces/IBBGameModeBuild.h"
#include "BBGameModeBuild.generated.h"

/**
*
*/

class AIBBHUD;
class UIBBWidgetSpecification;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBGameModeBuild : public UIBBGameModeBuild
{
	GENERATED_BODY()

	public:
		UBBGameModeBuild();

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

		FGameplayAbilityInputBinds InputBinds = FGameplayAbilityInputBinds(FString("LMB"), FString("RMB"), FString("EBBAbility"));

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBWidgetSpecification * BuildWidgetSpecification;

		void CreateInputComponent(AIBBPlayerController * PlayerController);

		void DestroyInputComponent();

		void CreateWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory);

		void DestroyWidgetSpecification();

		void PushInputComponent();

		void PopInputComponent();

		void OpenBuildWidget();

		void CloseBuildWidget();
		
		void ToggleGrid(bool Enabled);
};