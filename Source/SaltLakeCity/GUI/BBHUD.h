// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBContextualizable.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "BBHUD.generated.h"

/**
 * 
 */

class IBBSelectable;
class IBBWorkable;
class UIBBBuildWidget;
class UIBBBuildEntryWidget;
class UIBBCommandFactory;
class UIBBContextWidget;
class UIBBContextRowWidget;
class UIBBDossierWidget;
class UIBBGameModeCommand;
class UIBBJobWidget;

USTRUCT(BlueprintType)

struct FBBWidgetCategory
{
	GENERATED_BODY()

	public:
		UPROPERTY()
		TArray<UIBBWidget *> Widgets;

		FBBWidgetCategory()
		{
			Widgets.Empty();
		}

		~FBBWidgetCategory()
		{
			Widgets.Empty();
		}
};

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API ABBHUD : public AIBBHUD
{
	GENERATED_BODY()
	
	public:
		ABBHUD();

		virtual void BeginPlay() override;
		
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(UIBBGameInstance * GameInstance, AIBBGameMode * GameMode, AIBBGameState * GameState, APlayerController * PlayerController) override;

		virtual void Finalize() override;

		virtual const UIBBWidgetFactory * GetWidgetFactory() const override;

		virtual void SetWidgetFactory(UIBBWidgetFactory * NewWidgetFactory) override;

		virtual const UIBBWidgetSpecificationFactory * GetWidgetSpecificationFactory() const override;

		virtual void SetWidgetSpecificationFactory(UIBBWidgetSpecificationFactory * NewWidgetSpecificationFactory) override;

		virtual UIBBModelPool * GetModelPool() const override;

		virtual void SetModelPool(UIBBModelPool * NewModelPool) override;

		virtual void CloseWidget(UIBBWidgetSpecification * Specification) override;

		virtual void OpenWidget(UIBBWidgetSpecification * Specification, bool PopUp) override;

		virtual void AttachWidget(UIBBWidgetSpecification * Specification, UIBBWidgetComponent * WidgetComponent) override;

		virtual void DetachWidget(UIBBWidgetComponent * WidgetComponent) override;

		virtual bool ConvertToPIEViewportSpace(FVector2D & Position) override;

		virtual void UpdateActiveMode(EBBGameMode NewActiveMode) override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "HUD Colors")
		FLinearColor HUDColor;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBModelPool> ModelPoolClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBWidgetFactory> WidgetFactoryClass;

		UPROPERTY(EditAnywhere, Category = "Classes")
		TSoftClassPtr<UIBBWidgetSpecificationFactory> WidgetSpecificationFactoryClass;

		UPROPERTY()
		UIBBModelPool * ModelPool;

		UPROPERTY()
		UIBBWidgetFactory * WidgetFactory;

		UPROPERTY()
		UIBBWidgetSpecificationFactory * WidgetSpecificationFactory;

		UPROPERTY()
		UIBBContextWidget * ContextWidget;

		UPROPERTY()
		UIBBJobWidget * JobWidget;

		UPROPERTY()
		TMap<EBBWidget, FBBWidgetCategory> WidgetCategories;

		UPROPERTY()
		AIBBGameState * GameState;

		FDelegateHandle OnLandscapeClickedHandle;

		void CreateModelPool(UIBBGameInstance * NewGameInstance);

		void CreateWidgetFactory(const UIBBGameInstance * NewGameInstance, const AIBBGameState * NewGameState, AIBBGameMode * NewGameMode, APlayerController * NewPlayerController);

		void CreateWidgetSpecificationFactory();

		void DestroyModelPool();

		void DestroyWidgetFactory();

		void DestroyWidgetSpecificationFactory();

		void AddWidgetToViewport(UIBBWidget & Widget, int32 ZOrder = -1);

		void AddWidgetToMap(EBBWidget WidgetType, UIBBWidget * Widget);

		void RemoveWidgetFromMap(UIBBWidget * Widget);

		UIBBWidget * GetWidget(UIBBWidgetSpecification & Specification);

		bool EvaluateModelPool(UIBBWidget * & Widget, UIBBWidgetSpecification & Specification);

		UIBBWidget * NewWidgetFromSpecification(UIBBWidgetSpecification & Specification);

		void CreateWidgets();

		void DestroyWidgets();

		void Subscribe(AIBBGameState * NewGameState);

		void Unsubscribe(AIBBGameState * SubscribedGameState);

		void ShowWidget(UIBBWidget * Widget, bool PopUp);

		void HideWidget(UIBBWidget * Widget);

		FVector2D GetPopUpCoordinates(UIBBWidget * Widget);

		UFUNCTION()
		void UpdateConsumer(TScriptInterface<IBBWorkable> Workable);

		UFUNCTION()
		void UpdateContext(TScriptInterface<IBBContextualizable> Contextualizable);

		UFUNCTION()
		void UpdateSelection(TScriptInterface<IBBSelectable> Selectable);
};