// SaltLakeCity 4.27

#include "BBLevelScriptActorStub.h"
#include "Landscape.h"
#include "Engine/DirectionalLight.h"
#include "Engine/LevelBounds.h"
#include "Engine/Level.h"
#include "Engine/SkyLight.h"
#include "Engine/World.h"
#include "IOC/BBIOC.h"

ABBLevelScriptActorStub::ABBLevelScriptActorStub() :
	Super()
{
	Latitude = 0.0f;
	Longitude = 0.0f;

	Landscape = nullptr;
	SunLight = nullptr;
	SkyLight = nullptr;

	LightingCycle = nullptr;
	GameClock = nullptr;
}

void ABBLevelScriptActorStub::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	Landscape = TSoftObjectPtr<ALandscape>(World->SpawnActor<ALandscape>(ALandscape::StaticClass(), SpawnParameters));
	SunLight = TSoftObjectPtr<ADirectionalLight>(World->SpawnActor<ADirectionalLight>(ADirectionalLight::StaticClass(), SpawnParameters));
	SkyLight = TSoftObjectPtr<ASkyLight>(World->SpawnActor<ASkyLight>(ASkyLight::StaticClass(), SpawnParameters));
}

void ABBLevelScriptActorStub::BeginPlay()
{
	Super::BeginPlay();
}

void ABBLevelScriptActorStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UWorld * World = GetWorld();

	if (IsValid(World))
	{
		if (IsValid(Landscape.LoadSynchronous()))
		{
			World->DestroyActor(Landscape.LoadSynchronous());
		}

		if (IsValid(SunLight.LoadSynchronous()))
		{
			World->DestroyActor(SunLight.LoadSynchronous());
		}

		if (IsValid(SkyLight.LoadSynchronous()))
		{
			World->DestroyActor(SkyLight.LoadSynchronous());
		}
	}

	Super::EndPlay(EndPlayReason);
}

void ABBLevelScriptActorStub::Initialize(const UIBBGameClock * NewGameClock)
{
	GameClock = NewGameClock;
}

void ABBLevelScriptActorStub::Finalize()
{
	GameClock = nullptr;
}

const float ABBLevelScriptActorStub::GetLatitude() const
{
	return Latitude;
}

void ABBLevelScriptActorStub::SetLatitude(float NewLatitude)
{
	Latitude = NewLatitude;
}

const float ABBLevelScriptActorStub::GetLongitude() const
{
	return Longitude;
}

void ABBLevelScriptActorStub::SetLongitude(float NewLongitude)
{
	Longitude = NewLongitude;
}

FVector ABBLevelScriptActorStub::GetLevelBounds() const
{

	return LevelBounds;
}

void ABBLevelScriptActorStub::SetLevelBounds(FVector NewLevelBounds)
{
	LevelBounds = NewLevelBounds;
}

ALandscape * ABBLevelScriptActorStub::GetLandscape() const
{
	return Landscape.LoadSynchronous();
}

void ABBLevelScriptActorStub::SetLandscape(ALandscape * NewLandscape)
{
	Landscape = TSoftObjectPtr<ALandscape>(NewLandscape);
}


ADirectionalLight * ABBLevelScriptActorStub::GetSunLight() const
{
	return SunLight.LoadSynchronous();
}

void ABBLevelScriptActorStub::SetSunLight(ADirectionalLight * NewSunLight)
{
	SunLight = TSoftObjectPtr<ADirectionalLight>(NewSunLight);
}

ASkyLight * ABBLevelScriptActorStub::GetSkyLight() const
{
	return SkyLight.LoadSynchronous();
}

void ABBLevelScriptActorStub::SetSkyLight(ASkyLight * NewSkyLight)
{
	SkyLight = TSoftObjectPtr<ASkyLight>(NewSkyLight);
}

const UIBBLightingCycle * ABBLevelScriptActorStub::GetLightingCycle() const
{
	return LightingCycle;
}

void ABBLevelScriptActorStub::SetLightingCycle(UIBBLightingCycle * NewLightingCycle)
{
	LightingCycle = NewLightingCycle;
}
