// SaltLakeCity 4.27

#include "BBWidgetFactoryStub.h"
#include "GUI/Widgets/Interfaces/IBBBuildWidget.h"
#include "GUI/Widgets/Interfaces/IBBBuildEntryWidget.h"
#include "GUI/Widgets/Interfaces/IBBContextWidget.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"
#include "GUI/Widgets/Interfaces/IBBDossierWidget.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"
#include "GUI/Widgets/Interfaces/IBBJobWidget.h"
#include "GUI/Widgets/Interfaces/IBBProgressWidget.h"
#include "GUI/Widgets/Interfaces/IBBSelectionWidget.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"

UBBWidgetFactoryStub::UBBWidgetFactoryStub() :
	Super()
{
	GameInstance = nullptr;
	GameState = nullptr;
	GameMode = nullptr;
	HUD = nullptr;
	PlayerController = nullptr;

	Widgets.Empty();
}

void UBBWidgetFactoryStub::Initialize(const UIBBGameInstance * NewGameInstance, const AIBBGameState * NewGameState, AIBBGameMode * NewGameMode, AIBBHUD * NewHUD, APlayerController * NewPlayerController)
{
	GameInstance = NewGameInstance;
	GameState = NewGameState;
	GameMode = NewGameMode;
	HUD = NewHUD;
	PlayerController = NewPlayerController;
}

void UBBWidgetFactoryStub::Finalize()
{
	GameInstance = nullptr;
	GameState = nullptr;
	GameMode = nullptr;
	HUD = nullptr;
	PlayerController = nullptr;
}

void UBBWidgetFactoryStub::AddWidget(UIBBWidget * Widget)
{
	Widgets.EmplaceAt(0, Widget);
}

bool UBBWidgetFactoryStub::NewBuildWidget(UIBBBuildWidget * & Widget) const
{
	Widget = Widgets.Num() > 0 ? Cast<UIBBBuildWidget>(Widgets.Pop()) : nullptr;

	return IsValid(Widget);
}

bool UBBWidgetFactoryStub::NewBuildEntryWidget(UIBBBuildEntryWidget *& Widget, const UIBBBuildEntry * Entry) const
{
	Widget = Widgets.Num() > 0 ? Cast<UIBBBuildEntryWidget>(Widgets.Pop()) : nullptr;

	return IsValid(Widget);
}

bool UBBWidgetFactoryStub::NewContextWidget(UIBBContextWidget * & Widget) const
{
	Widget = Widgets.Num() > 0 ? Cast<UIBBContextWidget>(Widgets.Pop()) : nullptr;

	return IsValid(Widget);
}

bool UBBWidgetFactoryStub::NewDateTimeWidget(UIBBDateTimeWidget * & Widget) const
{
	Widget = Widgets.Num() > 0 ? Cast<UIBBDateTimeWidget>(Widgets.Pop()) : nullptr;

	return IsValid(Widget);
}

bool UBBWidgetFactoryStub::NewDossierWidget(UIBBDossierWidget * & Widget, AIBBCharacter * Character) const
{
	Widget = Widgets.Num() > 0 ? Cast<UIBBDossierWidget>(Widgets.Pop()) : nullptr;

	return IsValid(Widget);
}

bool UBBWidgetFactoryStub::NewDossierEntryWidget(UIBBDossierEntryWidget * & Widget, UIBBDossierEntry * Entry) const
{
	Widget = Widgets.Num() > 0 ? Cast<UIBBDossierEntryWidget>(Widgets.Pop()) : nullptr;

	return IsValid(Widget);
}

bool UBBWidgetFactoryStub::NewJobWidget(UIBBJobWidget * & Widget) const
{
	Widget = Widgets.Num() > 0 ? Cast<UIBBJobWidget>(Widgets.Pop()) : nullptr;

	return IsValid(Widget);
}

bool UBBWidgetFactoryStub::NewProgressWidget(UIBBProgressWidget * & Widget, UIBBProgressComponent * Component) const
{
	Widget = Widgets.Num() > 0 ? Cast<UIBBProgressWidget>(Widgets.Pop()) : nullptr;

	return IsValid(Widget);
}

bool UBBWidgetFactoryStub::NewSelectionWidget(UIBBSelectionWidget * & Widget) const
{
	Widget = Widgets.Num() > 0 ? Cast<UIBBSelectionWidget>(Widgets.Pop()) : nullptr;

	return IsValid(Widget);
}

bool UBBWidgetFactoryStub::NewTitleWidget(UIBBTitleWidget * & Widget, UIBBGUIModel * ParentModel) const
{
	Widget = Widgets.Num() > 0 ? Cast<UIBBTitleWidget>(Widgets.Pop()) : nullptr;

	return IsValid(Widget);
}