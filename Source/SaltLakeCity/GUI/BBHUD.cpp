// SaltLakeCity 4.27

#include "BBHUD.h"
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

ABBHUD::ABBHUD() :
	Super()
{
	HUDColor = FLinearColor(0.984314, 0.333333, 0.0, 1.0);

	WidgetCategories.Empty();

	ModelPool = nullptr;
	WidgetFactory = nullptr;
	WidgetSpecificationFactory = nullptr;

	ContextWidget = nullptr;
	JobWidget = nullptr;

	GameState = nullptr;
}

void ABBHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ABBHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Finalize();

	Super::EndPlay(EndPlayReason);
}

void ABBHUD::Initialize(UIBBGameInstance * NewGameInstance, AIBBGameMode * NewGameMode, AIBBGameState * NewGameState, APlayerController * NewPlayerController)
{
	CreateModelPool(NewGameInstance);
	CreateWidgetFactory(NewGameInstance, NewGameState, NewGameMode, NewPlayerController);
	CreateWidgetSpecificationFactory();
	CreateWidgets();

	Subscribe(NewGameState);
}

void ABBHUD::Finalize()
{
	Unsubscribe(GameState);

	DestroyWidgets();
	DestroyWidgetSpecificationFactory();
	DestroyWidgetFactory();
	DestroyModelPool();
}

const UIBBWidgetFactory * ABBHUD::GetWidgetFactory() const
{
	return WidgetFactory;
}

void ABBHUD::SetWidgetFactory(UIBBWidgetFactory * NewWidgetFactory)
{
	verifyf(IsValid(NewWidgetFactory), TEXT("New Widget Factory is invalid."));

	WidgetFactory = NewWidgetFactory;
}

const UIBBWidgetSpecificationFactory * ABBHUD::GetWidgetSpecificationFactory() const
{
	return WidgetSpecificationFactory;
}

void ABBHUD::SetWidgetSpecificationFactory(UIBBWidgetSpecificationFactory * NewWidgetSpecificationFactory)
{
	verifyf(IsValid(NewWidgetSpecificationFactory), TEXT("New Widget Specification Factory is invalid."));

	WidgetSpecificationFactory = NewWidgetSpecificationFactory;
}

UIBBModelPool * ABBHUD::GetModelPool() const
{
	return ModelPool;
}

void ABBHUD::SetModelPool(UIBBModelPool * NewModelPool)
{
	verifyf(IsValid(NewModelPool), TEXT("New Model Pool is invalid."));

	ModelPool = NewModelPool;
}

void ABBHUD::CloseWidget(UIBBWidgetSpecification * Specification)
{
	verifyf(IsValid(Specification), TEXT("Widget Specification is invalid."));

	UIBBWidget * Widget = GetWidget(* Specification);

	if (IsValid(Widget))
	{
		Widget->RemoveFromViewport();
	}
}

void ABBHUD::OpenWidget(UIBBWidgetSpecification * Specification, bool PopUp)
{
	verifyf(IsValid(Specification), TEXT("Widget Specification is invalid."));

	UIBBWidget * Widget = GetWidget(* Specification);

 	verifyf(IsValid(Widget), TEXT("Widget is invalid."));

	ShowWidget(Widget, PopUp);
}

void ABBHUD::AttachWidget(UIBBWidgetSpecification * Specification, UIBBWidgetComponent * WidgetComponent)
{
	verifyf(IsValid(Specification), TEXT("Widget Specification is invalid."));
	verifyf(IsValid(WidgetComponent), TEXT("WidgetComponent is invalid."));

	UIBBWidget * Widget = GetWidget(* Specification);

	verifyf(IsValid(Widget), TEXT("Widget is invalid."));

	WidgetComponent->SetWidget(Widget);
}

void ABBHUD::DetachWidget(UIBBWidgetComponent * WidgetComponent)
{
	verifyf(IsValid(WidgetComponent), TEXT("WidgetComponent is invalid."));

	UIBBWidget * Widget = Cast<UIBBWidget>(WidgetComponent->GetWidget());

	WidgetComponent->SetWidget(nullptr);

	RemoveWidgetFromMap(Widget);
}

bool ABBHUD::ConvertToPIEViewportSpace(FVector2D & Position)
{
	#if WITH_EDITOR

	UWorld * World = GetWorld();

	if (IsValid(World))
	{
		UGameViewportClient * GameViewport = World->GetGameViewport();

		if (IsValid(GameViewport))
		{
			if (GameViewport->bIsPlayInEditorViewport)
			{
				FIntPoint IntPosition = FIntPoint::ZeroValue;
				IntPosition.X = FMath::RoundToInt(Position.X);
				IntPosition.Y = FMath::RoundToInt(Position.Y);

				Position = GameViewport->Viewport->VirtualDesktopPixelToViewport(IntPosition);

				FVector2D ViewportSize = FVector2D::ZeroVector;
				GameViewport->GetViewportSize(ViewportSize);

				Position *= ViewportSize;

				return true;
			}
		}
	}

	#endif

	return false;
}

void ABBHUD::UpdateActiveMode(EBBGameMode NewActiveMode)
{
	if (NewActiveMode == EBBGameMode::Build)
	{
		UIBBBuildModel * Model = nullptr;

		ModelPool->GetBuildModel(Model);

		verifyf(IsValid(Model), TEXT("Build Model is invalid."));

		UIBBWidget * Widget = Model->GetWidget();

		verifyf(IsValid(Widget), TEXT("Build Widget is invalid."));

		Widget->AddToViewport(0);
	}
}



void ABBHUD::CreateModelPool(UIBBGameInstance * NewGameInstance)
{
	DestroyModelPool();

	verifyf(!ModelPoolClass.IsNull(), TEXT("Model Pool class is null."));

	UIBBModelPool * NewModelPool = NewObject<UIBBModelPool>(this, ModelPoolClass.LoadSynchronous());

	verifyf(IsValid(NewModelPool), TEXT("New Model Pool is invalid."));

	NewModelPool->Initialize(NewGameInstance);

	SetModelPool(NewModelPool);
}

void ABBHUD::CreateWidgetFactory(const UIBBGameInstance * NewGameInstance, const AIBBGameState * NewGameState, AIBBGameMode * NewGameMode, APlayerController * NewPlayerController)
{
	DestroyWidgetFactory();

	verifyf(!WidgetFactoryClass.IsNull(), TEXT("Widget Factory class is null."));

	UIBBWidgetFactory * NewWidgetFactory = NewObject<UIBBWidgetFactory>(this, WidgetFactoryClass.LoadSynchronous());

	verifyf(IsValid(NewWidgetFactory), TEXT("New Widget Factory is invalid."));

	NewWidgetFactory->Initialize(NewGameInstance, NewGameState, NewGameMode, this, NewPlayerController);

	SetWidgetFactory(NewWidgetFactory);
}

void ABBHUD::CreateWidgetSpecificationFactory()
{
	DestroyWidgetSpecificationFactory();

	verifyf(!WidgetSpecificationFactoryClass.IsNull(), TEXT("Widget Specification Factory class is null."));

	UIBBWidgetSpecificationFactory * NewWidgetSpecificationFactory = NewObject<UIBBWidgetSpecificationFactory>(this, WidgetSpecificationFactoryClass.LoadSynchronous());

	verifyf(IsValid(NewWidgetSpecificationFactory), TEXT("New Widget Specification Factory is invalid."));

	//NewWidgetSpecificationFactory->Initialize();

	SetWidgetSpecificationFactory(NewWidgetSpecificationFactory);
}

void ABBHUD::DestroyModelPool()
{
	if (IsValid(ModelPool))
	{
		ModelPool->MarkPendingKill();
	}

	ModelPool = nullptr;
}

void ABBHUD::DestroyWidgetFactory()
{
	if (IsValid(WidgetFactory))
	{
		WidgetFactory->Finalize();
		WidgetFactory->MarkPendingKill();
	}

	WidgetFactory = nullptr;
}

void ABBHUD::DestroyWidgetSpecificationFactory()
{
	if (IsValid(WidgetSpecificationFactory))
	{
		WidgetSpecificationFactory->MarkPendingKill();
	}

	WidgetSpecificationFactory = nullptr;
}

void ABBHUD::AddWidgetToViewport(UIBBWidget & Widget, int32 ZOrder)
{
	Widget.SetVisibility(ESlateVisibility::Visible);
	Widget.AddToViewport(ZOrder);
}

void ABBHUD::AddWidgetToMap(EBBWidget WidgetType, UIBBWidget * Widget)
{
	verifyf(IsValid(Widget), TEXT("Widget is invalid."));

	FBBWidgetCategory * WidgetCategory = WidgetCategories.Find(WidgetType);

	verifyf(WidgetCategory, TEXT("Widget Category is null."));

	WidgetCategory->Widgets.Emplace(Widget);
}

void ABBHUD::RemoveWidgetFromMap(UIBBWidget * Widget)
{
	for (TPair<EBBWidget, FBBWidgetCategory> & WidgetCategoryPair : WidgetCategories)
	{
		if (WidgetCategoryPair.Value.Widgets.Remove(Widget) > 0)
		{
			Widget->RemoveFromViewport();
			Widget->MarkPendingKill();

			Widget = nullptr;

			break;
		}
	}
}

UIBBWidget * ABBHUD::GetWidget(UIBBWidgetSpecification & Specification)
{
	UIBBWidget * Widget = nullptr;

	if (!EvaluateModelPool(Widget, Specification))
	{
		Widget = NewWidgetFromSpecification(Specification);
	}

	return Widget;
}

bool ABBHUD::EvaluateModelPool(UIBBWidget * & Widget, UIBBWidgetSpecification & Specification)
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

UIBBWidget * ABBHUD::NewWidgetFromSpecification(UIBBWidgetSpecification & Specification)
{
	verifyf(IsValid(WidgetFactory), TEXT("Widget Builder is invalid."));

	UIBBWidget * Widget = nullptr;

	Specification.CreateWidget(Widget, * WidgetFactory);

	return Widget;
}

void ABBHUD::CreateWidgets()
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

	UIBBBuildWidget * BuildWidget = nullptr;
	WidgetFactory->NewBuildWidget(BuildWidget);
	AddWidgetToMap(EBBWidget::Build, BuildWidget);

	ContextWidget = nullptr;
	WidgetFactory->NewContextWidget(ContextWidget);
	AddWidgetToMap(EBBWidget::Context, ContextWidget);

	UIBBDateTimeWidget * DateTimeWidget = nullptr;
	WidgetFactory->NewDateTimeWidget(DateTimeWidget);
	AddWidgetToMap(EBBWidget::DateTime, DateTimeWidget);
	DateTimeWidget->AddToViewport(0);

	JobWidget = nullptr;
	WidgetFactory->NewJobWidget(JobWidget);
	AddWidgetToMap(EBBWidget::Job, JobWidget);

	UIBBModesWidget * ModesWidget = nullptr;
	WidgetFactory->NewModesWidget(ModesWidget);
	AddWidgetToMap(EBBWidget::Modes, ModesWidget);
	ModesWidget->AddToViewport(0);
}

void ABBHUD::DestroyWidgets()
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

void ABBHUD::Subscribe(AIBBGameState * NewGameState)
{
	Unsubscribe(GameState);

	verifyf(IsValid(NewGameState), TEXT("New Game State is invalid."));

	GameState = NewGameState;

	GameState->OnConsumerUpdate().AddUObject(this, & ABBHUD::UpdateConsumer);
	GameState->OnContextUpdate().AddUObject(this, & ABBHUD::UpdateContext);
	GameState->OnSelectionUpdate().AddUObject(this, & ABBHUD::UpdateSelection);
}

void ABBHUD::Unsubscribe(AIBBGameState * SubscribedGameState)
{
	if (IsValid(GameState))
	{
		GameState->OnSelectionUpdate().RemoveAll(this);
		GameState->OnContextUpdate().RemoveAll(this);
		GameState->OnConsumerUpdate().RemoveAll(this);
	}
}

void ABBHUD::ShowWidget(UIBBWidget * Widget, bool PopUp)
{
	verifyf(IsValid(Widget), TEXT("Widget is invalid."));

	HideWidget(Widget);

	if (PopUp) Widget->SetPositionInViewport(GetPopUpCoordinates(Widget), false);

	Widget->AddToViewport(0);
}

void ABBHUD::HideWidget(UIBBWidget * Widget)
{
	Widget->RemoveFromViewport();
}

FVector2D ABBHUD::GetPopUpCoordinates(UIBBWidget * Widget)
{
	verifyf(IsValid(Widget), TEXT("Widget is invalid."));

	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	FVector2D Position = UWidgetLayoutLibrary::GetMousePositionOnViewport(World);

	FVector2D WidgetSize = Widget->GetDesiredSize();

	FVector2D ViewportSize;

	World->GetGameViewport()->GetViewportSize(ViewportSize);

	Position.X = FMath::Min(Position.X, ViewportSize.X - WidgetSize.X);

	Position.Y = FMath::Min(Position.Y, ViewportSize.Y - WidgetSize.Y);

	//ConvertToPIEViewportSpace(Position);

	return Position;
}

void ABBHUD::UpdateConsumer(TScriptInterface<IBBWorkable> Workable)
{
	verifyf(IsValid(Workable.GetObject()), TEXT("Workable is invalid."));

	OnConsumerUpdate().Broadcast(Workable->GetWorkComponent());
}

void ABBHUD::UpdateContext(TScriptInterface<IBBContextualizable> Contextualizable)
{
	verifyf(IsValid(Contextualizable.GetObject()), TEXT("Contextualizable is invalid."));

	OnContextUpdate().Broadcast(Contextualizable->GetContextComponent());
}

void ABBHUD::UpdateSelection(TScriptInterface<IBBSelectable> Selectable)
{
	verifyf(IsValid(Selectable.GetObject()), TEXT("Selectable is invalid."));

	OnSelectionUpdate().Broadcast(Selectable->GetSelectionComponent());
}