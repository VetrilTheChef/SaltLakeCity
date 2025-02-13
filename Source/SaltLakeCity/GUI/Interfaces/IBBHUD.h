// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "IBBHUD.generated.h"

/**
 * 
 */

Expose_TNameOf(AIBBHUD)

class AIBBGameMode;
class AIBBGameState;
class AIBBPlayerController;
class IBBWidgetTarget;
class UIBBCommandFactory;
class UIBBContextComponent;
class UIBBGameInstance;
class UIBBModelPool;
class UIBBProgressComponent;
class UIBBSelectionComponent;
class UIBBSpecificationFactory;
class UIBBWidget;
class UIBBWidgetFactory;
class UIBBWidgetComponent;
class UIBBWidgetSpecification;
class UIBBWidgetSpecificationFactory;
class UIBBWorkComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBHUD : public AHUD
{
	GENERATED_BODY()
	
	public:
		AIBBHUD() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay();  };
		
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize(UIBBGameInstance * NewGameInstance, AIBBGameMode * NewGameMode, AIBBGameState * NewGameState, APlayerController * NewPlayerController) PURE_VIRTUAL(AIBBHUD::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(AIBBHUD::Finalize, );

		virtual const UIBBWidgetFactory * GetWidgetFactory() const PURE_VIRTUAL(AIBBHUD::GetWidgetFactory, return nullptr; );

		virtual void SetWidgetFactory(UIBBWidgetFactory * NewWidgetFactory) PURE_VIRTUAL(AIBBHUD::SetWidgetFactory, );
		
		virtual const UIBBWidgetSpecificationFactory * GetWidgetSpecificationFactory() const PURE_VIRTUAL(AIBBHUD::GetWidgetSpecificationFactory, return nullptr; );

		virtual void SetWidgetSpecificationFactory(UIBBWidgetSpecificationFactory * NewWidgetSpecificationFactory) PURE_VIRTUAL(AIBBHUD::SetWidgetSpecificationFactory, );

		virtual UIBBModelPool * GetModelPool() const PURE_VIRTUAL(AIBBHUD::GetModelPool, return nullptr; );

		virtual void SetModelPool(UIBBModelPool * NewModelPool) PURE_VIRTUAL(AIBBHUD::SetModelPool, );

		virtual void CloseWidget(UIBBWidgetSpecification * Specification) PURE_VIRTUAL(AIBBHUD::CloseWidget, );

		virtual void OpenWidget(UIBBWidgetSpecification * Specification, bool PopUp) PURE_VIRTUAL(AIBBHUD::OpenWidget, );

		virtual void AttachWidget(UIBBWidgetSpecification * Specification, UIBBWidgetComponent * WidgetComponent) PURE_VIRTUAL(AIBBHUD::AttachWidget, );

		virtual void DetachWidget(UIBBWidgetComponent * WidgetComponent) PURE_VIRTUAL(AIBBHUD::DetachWidget, );

		virtual UObject * GetWidgetTarget(UIBBWidget * Widget) PURE_VIRTUAL(AIBBHUD::GetWidgetTarget, return nullptr; );

		virtual bool ConvertToPIEViewportSpace(FVector2D & Position) PURE_VIRTUAL(AIBBHUD::ConvertToPIEViewportSpace, return false; );

		DECLARE_EVENT_OneParam(AIBBHUD, FBBContextUpdate, UIBBContextComponent *);

		FBBContextUpdate & OnContextUpdate() { return UpdateContext; };

		DECLARE_EVENT_OneParam(AIBBHUD, FBBProgressUpdate, UIBBProgressComponent *);

		FBBProgressUpdate & OnProgressUpdate() { return UpdateProgress; };

		DECLARE_EVENT_OneParam(AIBBHUD, FBBSelectionUpdate, UIBBSelectionComponent *);

		FBBSelectionUpdate & OnSelectionUpdate() { return UpdateSelection; };

		DECLARE_EVENT_OneParam(AIBBHUD, FBBWidgetTargetUpdate, TScriptInterface<IBBWidgetTarget> &&);

		FBBWidgetTargetUpdate & OnWidgetTargetUpdate() { return UpdateWidgetTarget; };

		DECLARE_EVENT_OneParam(AIBBHUD, FBBConsumerUpdate, UIBBWorkComponent *);

		FBBConsumerUpdate & OnConsumerUpdate() { return ConsumerUpdate; };

		UFUNCTION()
		virtual void UpdateActiveMode(EBBGameMode NewActiveMode) PURE_VIRTUAL(AIBBHUD::UpdateActiveMode, );

	protected:
		FBBContextUpdate UpdateContext;

		FBBProgressUpdate UpdateProgress;

		FBBSelectionUpdate UpdateSelection;

		FBBWidgetTargetUpdate UpdateWidgetTarget;

		FBBConsumerUpdate ConsumerUpdate;
};