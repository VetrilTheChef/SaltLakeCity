// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Interfaces/IBBWidgetManager.h"
#include "BBWidgetManager.generated.h"

/**
 * 
 */

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

class SALTLAKECITY_API UBBWidgetManager : public UIBBWidgetManager
{
	GENERATED_BODY()
	
	public:
		UBBWidgetManager();

		virtual void Initialize(
			const UIBBGameInstance* GameInstance,
			const AIBBGameState* GameState,
			AIBBGameMode* GameMode,
			AIBBHUD* NewHUD,
			APlayerController* PlayerController
		) override;

		virtual void Finalize() override;

		virtual const UIBBWidgetFactory * GetWidgetFactory() const override;

		virtual void SetWidgetFactory(
			UIBBWidgetFactory * NewWidgetFactory
		) override;

		virtual const UIBBWidgetSpecificationFactory * GetWidgetSpecificationFactory() const override;

		virtual void SetWidgetSpecificationFactory(
			UIBBWidgetSpecificationFactory * NewWidgetSpecificationFactory
		) override;

		virtual UIBBModelPool * GetModelPool() const override;

		virtual void SetModelPool(UIBBModelPool * NewModelPool) override;

		UIBBWidget * GetWidget(UIBBWidgetSpecification * Specification);

	protected:
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
		TMap<EBBWidget, FBBWidgetCategory> WidgetCategories;

		void CreateModelPool(const UIBBGameInstance* NewGameInstance);

		void CreateWidgetFactory(
			const UIBBGameInstance* NewGameInstance,
			const AIBBGameState* NewGameState,
			AIBBGameMode* NewGameMode,
			AIBBHUD* NewHUD,
			APlayerController* NewPlayerController
		);

		void CreateWidgetSpecificationFactory();

		void DestroyModelPool();

		void DestroyWidgetFactory();

		void DestroyWidgetSpecificationFactory();

		void AddWidgetToMap(EBBWidget WidgetType, UIBBWidget* Widget);

		void RemoveWidgetFromMap(UIBBWidget* Widget);

		bool EvaluateModelPool(UIBBWidget*& Widget, UIBBWidgetSpecification& Specification);

		UIBBWidget* NewWidgetFromSpecification(UIBBWidgetSpecification& Specification);

		void CreateWidgets();

		void DestroyWidgets();
};