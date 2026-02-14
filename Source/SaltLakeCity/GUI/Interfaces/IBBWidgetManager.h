// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "IBBWidgetManager.generated.h"

/**
 * 
 */

Expose_TNameOf(UIBBWidgetManager)

class AIBBGameMode;
class AIBBGameState;
class AIBBHUD;
class AIBBPlayerController;
class UIBBGameInstance;
class UIBBModelPool;
class UIBBWidget;
class UIBBWidgetFactory;
class UIBBWidgetSpecification;
class UIBBWidgetSpecificationFactory;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBWidgetManager : public UObject
{
	GENERATED_BODY()
	
	public:
		UIBBWidgetManager() : Super() { };

		virtual void Initialize(
			const UIBBGameInstance* GameInstance,
			const AIBBGameState* GameState,
			AIBBGameMode* GameMode,
			AIBBHUD* NewHUD,
			APlayerController* PlayerController
		) PURE_VIRTUAL(UIBBWidgetManager::Initialize, );

		virtual void Finalize()
			PURE_VIRTUAL(UIBBWidgetManager::Finalize, );

		virtual const UIBBWidgetFactory* GetWidgetFactory() const
			PURE_VIRTUAL(UIBBWidgetManager::GetWidgetFactory, return nullptr; );

		virtual void SetWidgetFactory(UIBBWidgetFactory* NewWidgetFactory)
			PURE_VIRTUAL(UIBBWidgetManager::SetWidgetFactory, );

		virtual const UIBBWidgetSpecificationFactory* GetWidgetSpecificationFactory() const
			PURE_VIRTUAL(UIBBWidgetManager::GetWidgetSpecificationFactory, return nullptr; );

		virtual void SetWidgetSpecificationFactory(UIBBWidgetSpecificationFactory* NewWidgetSpecificationFactory)
			PURE_VIRTUAL(UIBBWidgetManager::SetWidgetSpecificationFactory, );

		virtual UIBBModelPool* GetModelPool() const
			PURE_VIRTUAL(UIBBWidgetManager::GetModelPool, return nullptr; );

		virtual void SetModelPool(UIBBModelPool* NewModelPool)
			PURE_VIRTUAL(UIBBWidgetManager::SetModelPool, );

		virtual UIBBWidget* GetWidget(UIBBWidgetSpecification* Specification)
			PURE_VIRTUAL(UIBBWidgetManager::GetWidget, return nullptr; );
};