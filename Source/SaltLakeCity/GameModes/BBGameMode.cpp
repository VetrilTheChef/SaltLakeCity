// SaltLakeCity 4.26

#include "BBGameMode.h"

ABBGameMode::ABBGameMode() :
	Super()
{
}

void ABBGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ABBGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABBGameMode::Initialize()
{
}

void ABBGameMode::Finalize()
{
}

void ABBGameMode::SetMode(EBBGameMode NewGameMode)
{
	OnActiveModeUpdate().Broadcast(NewGameMode);
}