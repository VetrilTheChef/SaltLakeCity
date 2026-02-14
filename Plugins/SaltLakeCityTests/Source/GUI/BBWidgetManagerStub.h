// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Interfaces/IBBWidgetManager.h"
#include "BBWidgetManagerStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBWidgetManagerStub : public UIBBWidgetManager
{
	GENERATED_BODY()
	
	public:
		UBBWidgetManagerStub();

		virtual void Initialize(
			const UIBBGameInstance* GameInstance,
			const AIBBGameState* GameState,
			AIBBGameMode* GameMode,
			AIBBHUD* NewHUD,
			APlayerController* PlayerController
		) override;

		virtual void Finalize() override;

		virtual const UIBBWidgetFactory* GetWidgetFactory() const override;

		virtual void SetWidgetFactory(
			UIBBWidgetFactory* NewWidgetFactory
		) override;

		virtual const UIBBWidgetSpecificationFactory* GetWidgetSpecificationFactory() const override;

		virtual void SetWidgetSpecificationFactory(
			UIBBWidgetSpecificationFactory* NewWidgetSpecificationFactory
		) override;

		virtual UIBBModelPool* GetModelPool() const override;

		virtual void SetModelPool(
			UIBBModelPool* NewModelPool
		) override;

		virtual UIBBWidget* GetWidget(
			UIBBWidgetSpecification* Specification
		) override;

		void SetWidget(
			UIBBWidget* NewWidget
		);

	private:
		UPROPERTY()
		UIBBWidgetFactory* WidgetFactory;

		UPROPERTY()
		UIBBWidgetSpecificationFactory* WidgetSpecificationFactory;

		UPROPERTY()
		UIBBModelPool* ModelPool;

		UPROPERTY()
		UIBBWidget* Widget;
};