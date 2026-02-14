// SaltLakeCity 5.7

#include "BBGameInstanceStub.h"
#include "Actors/Components/Factories/Interfaces/IBBComponentFactory.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Interfaces/IBBWidgetManager.h"
#include "Specifications/Factories/BBSpecificationFactory.h"

UBBGameInstanceStub::UBBGameInstanceStub() :
	Super()
{
	GameMode = nullptr;
	GameState = nullptr;
	HUD = nullptr;
	PlayerController = nullptr;

	CommandFactory = nullptr;
	ComponentFactory = nullptr;
}

void UBBGameInstanceStub::Clone(UGameInstance* Other)
{
	WorldContext = Other->GetWorldContext();
	LocalPlayers = Other->GetLocalPlayers();
	OnlineSession = Other->GetOnlineSession();
	PIEMapName = Other->PIEMapName;
	PIEStartTime = Other->PIEStartTime;
	TimerManager = Other->TimerManager;
	LatentActionManager = Other->LatentActionManager;
}

void UBBGameInstanceStub::Unclone()
{
	WorldContext = nullptr;
	LocalPlayers.Empty();
	OnlineSession = nullptr;
	PIEMapName = TEXT("");
	PIEStartTime = 0;
	TimerManager = nullptr;
	LatentActionManager = nullptr;
}

AIBBGameMode* UBBGameInstanceStub::GetGameMode() const
{
	return GameMode.Get();
}

void UBBGameInstanceStub::SetGameMode(AIBBGameMode* NewGameMode)
{
	GameMode = NewGameMode;
}

AIBBGameState* UBBGameInstanceStub::GetGameState() const
{
	return GameState.Get();
}

void UBBGameInstanceStub::SetGameState(AIBBGameState* NewGameState)
{
	GameState = NewGameState;
}

AIBBHUD* UBBGameInstanceStub::GetHUD() const
{
	return HUD.Get();
}

void UBBGameInstanceStub::SetHUD(AIBBHUD* NewHUD)
{
	HUD = NewHUD;
}

AIBBPlayerController* UBBGameInstanceStub::GetPlayerController() const
{
	return PlayerController.Get();
}

void UBBGameInstanceStub::SetPlayerController(AIBBPlayerController* NewPlayerController)
{
	PlayerController = NewPlayerController;
}

UIBBWidgetManager* UBBGameInstanceStub::GetWidgetManager() const
{
	return WidgetManager.Get();
}

void UBBGameInstanceStub::SetWidgetManager(UIBBWidgetManager* NewWidgetManager)
{
	WidgetManager = NewWidgetManager;
}

const UIBBCommandFactory* UBBGameInstanceStub::GetCommandFactory() const
{
	return CommandFactory.Get();
}

void UBBGameInstanceStub::SetCommandFactory(UIBBCommandFactory* NewCommandFactory)
{
	CommandFactory = NewCommandFactory;
}

const UIBBComponentFactory* UBBGameInstanceStub::GetComponentFactory() const
{
	return ComponentFactory.Get();
}

void UBBGameInstanceStub::SetComponentFactory(UIBBComponentFactory* NewComponentFactory)
{
	ComponentFactory = NewComponentFactory;
}

const UIBBSpecificationFactory* UBBGameInstanceStub::GetSpecificationFactory() const
{
	return SpecificationFactory.Get();
}

void UBBGameInstanceStub::SetSpecificationFactory(UIBBSpecificationFactory* NewSpecificationFactory)
{
	SpecificationFactory = NewSpecificationFactory;
}

void UBBGameInstanceStub::SetWorldContext(FWorldContext* NewWorldContext)
{
	WorldContext = NewWorldContext;
}
