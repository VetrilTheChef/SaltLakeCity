// SaltLakeCity 5.7

#include "BBWidgetManager.h"
#include "Abilities/Data/BBAbilityData.h"
#include "Actors/BBActor.h"
#include "Actors/Interfaces/IBBContextualizable.h"
#include "Actors/Interfaces/IBBSelectable.h"
#include "Actors/Interfaces/IBBWorkable.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "GUI/Components/Interfaces/IBBModelPool.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "GUI/Models/Interfaces/IBBBuildModel.h"
#include "GUI/Widgets/Interfaces/IBBBuildWidget.h"
#include "GUI/Widgets/Interfaces/IBBContextWidget.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"
#include "GUI/Widgets/Interfaces/IBBJobWidget.h"
#include "GUI/Widgets/Interfaces/IBBModesWidget.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"

UBBWidgetManager::UBBWidgetManager() :
	Super()
{
	WidgetCategories.Empty();

	ModelPool = nullptr;
	WidgetFactory = nullptr;
	WidgetSpecificationFactory = nullptr;
}

void UBBWidgetManager::Initialize(
	const UIBBGameInstance* NewGameInstance,
	const AIBBGameState* NewGameState,
	AIBBGameMode* NewGameMode,
	AIBBHUD* NewHUD,
	APlayerController* NewPlayerController
)
{
	CreateModelPool(NewGameInstance);
	CreateWidgetFactory(NewGameInstance, NewGameState, NewGameMode, NewHUD, NewPlayerController);
	CreateWidgetSpecificationFactory();
	CreateWidgets();
}

void UBBWidgetManager::Finalize()
{
	DestroyWidgets();
	DestroyWidgetSpecificationFactory();
	DestroyWidgetFactory();
	DestroyModelPool();
}

const UIBBWidgetFactory* UBBWidgetManager::GetWidgetFactory() const
{
	return WidgetFactory;
}

void UBBWidgetManager::SetWidgetFactory(UIBBWidgetFactory* NewWidgetFactory)
{
	verifyf(IsValid(NewWidgetFactory), TEXT("New Widget Factory is invalid."));

	WidgetFactory = NewWidgetFactory;
}

const UIBBWidgetSpecificationFactory* UBBWidgetManager::GetWidgetSpecificationFactory() const
{
	return WidgetSpecificationFactory;
}

void UBBWidgetManager::SetWidgetSpecificationFactory(UIBBWidgetSpecificationFactory* NewWidgetSpecificationFactory)
{
	verifyf(IsValid(NewWidgetSpecificationFactory), TEXT("New Widget Specification Factory is invalid."));

	WidgetSpecificationFactory = NewWidgetSpecificationFactory;
}

UIBBModelPool* UBBWidgetManager::GetModelPool() const
{
	return ModelPool;
}

void UBBWidgetManager::SetModelPool(UIBBModelPool* NewModelPool)
{
	verifyf(IsValid(NewModelPool), TEXT("New Model Pool is invalid."));

	ModelPool = NewModelPool;
}

UIBBWidget* UBBWidgetManager::GetWidget(UIBBWidgetSpecification* Specification)
{
	verifyf(IsValid(Specification), TEXT("Widget Specification is invalid."));

	UIBBWidget * Widget = nullptr;

	if (!EvaluateModelPool(Widget, *Specification))
	{
		Widget = NewWidgetFromSpecification(*Specification);
	}

	return Widget;
}



void UBBWidgetManager::CreateModelPool(const UIBBGameInstance* NewGameInstance)
{
	DestroyModelPool();

	verifyf(!ModelPoolClass.IsNull(), TEXT("Model Pool class is null."));

	UIBBModelPool * NewModelPool = NewObject<UIBBModelPool>(this, ModelPoolClass.LoadSynchronous());

	SetModelPool(NewModelPool);

	NewModelPool->Initialize(NewGameInstance);
}

void UBBWidgetManager::CreateWidgetFactory(
	const UIBBGameInstance* NewGameInstance,
	const AIBBGameState* NewGameState,
	AIBBGameMode* NewGameMode,
	AIBBHUD* NewHUD,
	APlayerController* NewPlayerController
)
{
	DestroyWidgetFactory();

	verifyf(!WidgetFactoryClass.IsNull(), TEXT("Widget Factory class is null."));

	UIBBWidgetFactory * NewWidgetFactory = NewObject<UIBBWidgetFactory>(this, WidgetFactoryClass.LoadSynchronous());

	verifyf(IsValid(NewWidgetFactory), TEXT("New Widget Factory is invalid."));

	NewWidgetFactory->Initialize(NewGameInstance, NewGameState, NewGameMode, NewHUD, NewPlayerController);

	SetWidgetFactory(NewWidgetFactory);
}

void UBBWidgetManager::CreateWidgetSpecificationFactory()
{
	DestroyWidgetSpecificationFactory();

	verifyf(!WidgetSpecificationFactoryClass.IsNull(), TEXT("Widget Specification Factory class is null."));

	UIBBWidgetSpecificationFactory * NewWidgetSpecificationFactory =
		NewObject<UIBBWidgetSpecificationFactory>(this, WidgetSpecificationFactoryClass.LoadSynchronous());

	verifyf(IsValid(NewWidgetSpecificationFactory), TEXT("New Widget Specification Factory is invalid."));

	SetWidgetSpecificationFactory(NewWidgetSpecificationFactory);
}

void UBBWidgetManager::DestroyModelPool()
{
	if (IsValid(ModelPool))
	{
		ModelPool->MarkAsGarbage();
	}

	ModelPool = nullptr;
}

void UBBWidgetManager::DestroyWidgetFactory()
{
	if (IsValid(WidgetFactory))
	{
		WidgetFactory->Finalize();
		WidgetFactory->MarkAsGarbage();
	}

	WidgetFactory = nullptr;
}

void UBBWidgetManager::DestroyWidgetSpecificationFactory()
{
	if (IsValid(WidgetSpecificationFactory))
	{
		WidgetSpecificationFactory->MarkAsGarbage();
	}

	WidgetSpecificationFactory = nullptr;
}

void UBBWidgetManager::AddWidgetToMap(EBBWidget WidgetType, UIBBWidget* Widget)
{
	verifyf(IsValid(Widget), TEXT("Widget is invalid."));

	FBBWidgetCategory * WidgetCategory = WidgetCategories.Find(WidgetType);

	verifyf(WidgetCategory, TEXT("Widget Category is null."));

	WidgetCategory->Widgets.Emplace(Widget);
}

void UBBWidgetManager::RemoveWidgetFromMap(UIBBWidget* Widget)
{
	for (TPair<EBBWidget, FBBWidgetCategory> & WidgetCategoryPair : WidgetCategories)
	{
		if (WidgetCategoryPair.Value.Widgets.Remove(Widget) > 0)
		{
			Widget->RemoveFromParent();
			Widget->MarkAsGarbage();

			Widget = nullptr;

			break;
		}
	}
}

bool UBBWidgetManager::EvaluateModelPool(UIBBWidget*& Widget, UIBBWidgetSpecification& Specification)
{
	verifyf(IsValid(ModelPool), TEXT("Model Pool is invalid."));

	UIBBGUIModel * Model = ModelPool->GetModel(Specification);

	if (IsValid(Model))
	{
		Widget = Model->GetWidget();

		return true;
	}

	return false;
}

UIBBWidget* UBBWidgetManager::NewWidgetFromSpecification(UIBBWidgetSpecification& Specification)
{
	verifyf(IsValid(WidgetFactory), TEXT("Widget Builder is invalid."));

	UIBBWidget * Widget = nullptr;

	Specification.CreateWidget(Widget, * WidgetFactory);

	return Widget;
}

void UBBWidgetManager::CreateWidgets()
{
	WidgetCategories.Emplace(EBBWidget::Build, FBBWidgetCategory());
	WidgetCategories.Emplace(EBBWidget::BuildEntry, FBBWidgetCategory());
	WidgetCategories.Emplace(EBBWidget::Context, FBBWidgetCategory());
	WidgetCategories.Emplace(EBBWidget::DateTime, FBBWidgetCategory());
	WidgetCategories.Emplace(EBBWidget::Dossier, FBBWidgetCategory());
	WidgetCategories.Emplace(EBBWidget::Job, FBBWidgetCategory());
	WidgetCategories.Emplace(EBBWidget::Modes, FBBWidgetCategory());
	WidgetCategories.Emplace(EBBWidget::Progress, FBBWidgetCategory());
	WidgetCategories.Emplace(EBBWidget::Selection, FBBWidgetCategory());
	WidgetCategories.Emplace(EBBWidget::Title, FBBWidgetCategory());

	UIBBBuildWidget* BuildWidget = nullptr;
	WidgetFactory->NewBuildWidget(BuildWidget);
	AddWidgetToMap(EBBWidget::Build, BuildWidget);

	UIBBContextWidget* ContextWidget = nullptr;
	WidgetFactory->NewContextWidget(ContextWidget);
	AddWidgetToMap(EBBWidget::Context, ContextWidget);

	UIBBDateTimeWidget* DateTimeWidget = nullptr;
	WidgetFactory->NewDateTimeWidget(DateTimeWidget);
	AddWidgetToMap(EBBWidget::DateTime, DateTimeWidget);
	DateTimeWidget->AddToScreen(0);

	UIBBJobWidget* JobWidget = nullptr;
	WidgetFactory->NewJobWidget(JobWidget);
	AddWidgetToMap(EBBWidget::Job, JobWidget);

	UIBBModesWidget * ModesWidget = nullptr;
	WidgetFactory->NewModesWidget(ModesWidget);
	AddWidgetToMap(EBBWidget::Modes, ModesWidget);
	ModesWidget->AddToScreen(0);
}

void UBBWidgetManager::DestroyWidgets()
{
	for (TPair<EBBWidget, FBBWidgetCategory> & WidgetCategoryPair : WidgetCategories)
	{
		for (UIBBWidget * & Widget : WidgetCategoryPair.Value.Widgets)
		{
			if (IsValid(Widget))
			{
				Widget->RemoveFromParent();
			}

			Widget = nullptr;
		}

		WidgetCategoryPair.Value.Widgets.Empty();
	}

	WidgetCategories.Empty();
}