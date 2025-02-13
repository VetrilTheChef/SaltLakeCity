// SaltLakeCity 4.26

#include "BBLightingCycleStub.h"

UBBLightingCycleStub::UBBLightingCycleStub() :
	Super()
{
	CurrentLevelScriptActor = nullptr;
	GameClock = nullptr;

	Ticks = -1;
}

void UBBLightingCycleStub::Initialize(const AIBBLevelScriptActor * LevelScriptActor, const UIBBGameClock * NewGameClock)
{
	CurrentLevelScriptActor = LevelScriptActor;
	GameClock = NewGameClock;

	Ticks = 0;
}

void UBBLightingCycleStub::Finalize()
{
	CurrentLevelScriptActor = nullptr;
	GameClock = nullptr;

	Ticks = -1;
}

void UBBLightingCycleStub::Tick()
{
	Ticks++;
}

const AIBBLevelScriptActor * UBBLightingCycleStub::GetLevelScriptActor() const
{
	return CurrentLevelScriptActor;
}

const UIBBGameClock * UBBLightingCycleStub::GetGameClock() const
{
	return GameClock;
}

int UBBLightingCycleStub::GetNumTicks() const
{
	return Ticks;
}