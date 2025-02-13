// SaltLakeCity 4.26

#include "BBGameModeStub.h"

ABBGameModeStub::ABBGameModeStub() :
	Super()
{
	GameMode = EBBGameMode::None;
}

void ABBGameModeStub::BeginPlay()
{
	Super::BeginPlay();

	GameMode = EBBGameMode::Play;
}

void ABBGameModeStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABBGameModeStub::Initialize()
{
}

void ABBGameModeStub::Finalize()
{
}

EBBGameMode ABBGameModeStub::GetMode()
{
	return GameMode;
}

void ABBGameModeStub::SetMode(EBBGameMode NewGameMode)
{
	GameMode = NewGameMode;
}

void ABBGameModeStub::BroadcastActiveModeUpdate()
{
	OnActiveModeUpdate().Broadcast(GameMode);
}