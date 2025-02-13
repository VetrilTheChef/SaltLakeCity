// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "GUI/Models/Interfaces/IBBModesModel.h"
#include "BBModesModel.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBModesModel : public UIBBModesModel
{
	GENERATED_BODY()

	public:
		UBBModesModel();

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual void Initialize(UIBBModesWidget * NewView, AIBBGameMode * NewGameMode) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBModesWidget * View;

		UPROPERTY()
		AIBBGameMode * GameMode;

		void InitializeView(UIBBModesWidget * NewView);

		void FinalizeView();

		void InitializeGameMode(AIBBGameMode * NewGameMode);

		void FinalizeGameMode();

		UFUNCTION()
		void UpdateMode(EBBGameMode NewGameMode);
};