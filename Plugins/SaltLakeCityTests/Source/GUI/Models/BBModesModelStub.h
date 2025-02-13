// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBModesModel.h"
#include "BBModesModelStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBModesModelStub : public UIBBModesModel
{
	GENERATED_BODY()

	public:
		UBBModesModelStub();

		virtual UIBBWidget * GetWidget() const override;

		void SetWidget(UIBBModesWidget * NewWidget);

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		void SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification);

		virtual void Initialize(UIBBModesWidget * NewView, AIBBGameMode * NewGameMode);

		virtual void Finalize();

		void UpdateActiveGameMode(EBBGameMode NewGameMode);

	protected:
		UPROPERTY()
		UIBBModesWidget * View;

		UPROPERTY()
		AIBBGameMode * GameMode;

		UPROPERTY()
		UIBBWidgetSpecification * WidgetSpecification;
};