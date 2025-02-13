// SaltLakeCity 4.26

#include "BBGameInstanceStub.h"

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

void UBBGameInstanceStub::Clone(UGameInstance * Other)
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

AIBBGameMode * UBBGameInstanceStub::GetGameMode() const
{
	return GameMode;
}

void UBBGameInstanceStub::SetGameMode(AIBBGameMode * NewGameMode)
{
	GameMode = NewGameMode;
}

AIBBGameState * UBBGameInstanceStub::GetGameState() const
{
	return GameState;
}

void UBBGameInstanceStub::SetGameState(AIBBGameState * NewGameState)
{
	GameState = NewGameState;
}

AIBBHUD * UBBGameInstanceStub::GetHUD() const
{
	return HUD;
}

void UBBGameInstanceStub::SetHUD(AIBBHUD * NewHUD)
{
	HUD = NewHUD;
}

AIBBPlayerController * UBBGameInstanceStub::GetPlayerController() const
{
	return PlayerController;
}

void UBBGameInstanceStub::SetPlayerController(AIBBPlayerController * NewPlayerController)
{
	PlayerController = NewPlayerController;
}

const UIBBCommandFactory * UBBGameInstanceStub::GetCommandFactory() const
{
	return CommandFactory;
}

void UBBGameInstanceStub::SetCommandFactory(UIBBCommandFactory * NewCommandFactory)
{
	CommandFactory = NewCommandFactory;
}

const UIBBComponentFactory * UBBGameInstanceStub::GetComponentFactory() const
{
	return ComponentFactory;
}

void UBBGameInstanceStub::SetComponentFactory(UIBBComponentFactory * NewComponentFactory)
{
	ComponentFactory = NewComponentFactory;
}

const UIBBSpecificationFactory * UBBGameInstanceStub::GetSpecificationFactory() const
{
	return SpecificationFactory;
}

void UBBGameInstanceStub::SetSpecificationFactory(UIBBSpecificationFactory * NewSpecificationFactory)
{
	SpecificationFactory = NewSpecificationFactory;
}

void UBBGameInstanceStub::SetWorldContext(FWorldContext * NewWorldContext)
{
	WorldContext = NewWorldContext;
}
