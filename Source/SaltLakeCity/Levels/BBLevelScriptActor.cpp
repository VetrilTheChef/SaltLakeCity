// SaltLakeCity 5.7

#include "BBLevelScriptActor.h"
#include "Landscape.h"
#include "Engine/DirectionalLight.h"
#include "Engine/GameInstance.h"
#include "Engine/Level.h"
#include "Engine/LevelBounds.h"
#include "Engine/SkyLight.h"
#include "GameFramework/PlayerController.h"
#include "Lighting/Interfaces/IBBLightingCycle.h"

ABBLevelScriptActor::ABBLevelScriptActor() :
	Super()
{
	bAllowTickBeforeBeginPlay = false;
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	Latitude = 0.0f;
	Longitude = 0.0f;

	LightingCycle = nullptr;

	PreviewLevel = nullptr;

	Landscape = nullptr;
	SunLight = nullptr;
	SkyLight = nullptr;
}

void ABBLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	CreateLightingCycle();

	SetActorTickEnabled(true);
}

void ABBLevelScriptActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	SetActorTickEnabled(false);

	DestroyLightingCycle();

	Super::EndPlay(EndPlayReason);
}

void ABBLevelScriptActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TickLightingCycle();
}

void ABBLevelScriptActor::Initialize(const UIBBGameClock * NewGameClock)
{
	Finalize();

	InitializeLightingCycle(NewGameClock);
	InitializePreviewLevel();
}

void ABBLevelScriptActor::Finalize()
{
	FinalizePreviewLevel();
	FinalizeLightingCycle();
}

const float ABBLevelScriptActor::GetLatitude() const
{
	return Latitude;
}

const float ABBLevelScriptActor::GetLongitude() const
{
	return Longitude;
}

FVector ABBLevelScriptActor::GetLevelBounds() const
{
	FVector LevelOrigin, LevelExtent;

	ULevel * Level = GetLevel();

	verifyf(IsValid(Level), TEXT("Level is invalid."));

	ALevelBounds * LevelBounds = Level->LevelBoundsActor.Get();

	verifyf(IsValid(LevelBounds), TEXT("Level Bounds is invalid."));

	LevelBounds->GetActorBounds(false, LevelOrigin, LevelExtent);

	return LevelExtent;
}

ALandscape * ABBLevelScriptActor::GetLandscape() const
{
	return Landscape.LoadSynchronous();
}

ADirectionalLight * ABBLevelScriptActor::GetSunLight() const
{
	return SunLight.LoadSynchronous();
}

ASkyLight * ABBLevelScriptActor::GetSkyLight() const
{
	return SkyLight.LoadSynchronous();
}

const UIBBLightingCycle * ABBLevelScriptActor::GetLightingCycle() const
{
	return LightingCycle;
}

void ABBLevelScriptActor::SetLightingCycle(UIBBLightingCycle * NewLightingCycle)
{
	verifyf(IsValid(NewLightingCycle), TEXT("New Lighting Cycle is invalid."));

	LightingCycle = NewLightingCycle;
}

ULevel * ABBLevelScriptActor::GetPreviewLevel() const
{
	return PreviewLevel;
}

void ABBLevelScriptActor::SetPreviewLevel(ULevel * NewPreviewLevel)
{
	verifyf(IsValid(NewPreviewLevel), TEXT("New Preview Level is invalid."));

	UGameInstance * GameInstance = GetGameInstance();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	APlayerController * PlayerController = GameInstance->GetFirstLocalPlayerController();

	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));

	if (IsValid(PreviewLevel))
	{
		for (AActor * Actor : PreviewLevel->Actors)
		{
			PlayerController->HiddenActors.Remove(Actor);
		}
	}

	PreviewLevel = NewPreviewLevel;

	PlayerController->HiddenActors.Append(PreviewLevel->Actors);
}



void ABBLevelScriptActor::CreateLightingCycle()
{
	verifyf(!LightingCycleClass.IsNull(), TEXT("Lighting Cycle Class is null."));

	LightingCycle = NewObject<UIBBLightingCycle>(this, LightingCycleClass.LoadSynchronous());
}

void ABBLevelScriptActor::DestroyLightingCycle()
{
	if (IsValid(LightingCycle))
	{
		LightingCycle->MarkAsGarbage();
	}

	LightingCycle = nullptr;
}

void ABBLevelScriptActor::InitializeLightingCycle(const UIBBGameClock * NewGameClock)
{
	verifyf(IsValid(LightingCycle), TEXT("Lighting Cycle is invalid."));

	LightingCycle->Initialize(this, NewGameClock);
}

void ABBLevelScriptActor::InitializePreviewLevel()
{
	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	const TArray<ULevelStreaming *> StreamingLevels = World->GetStreamingLevels();

	for (ULevelStreaming * StreamingLevel : StreamingLevels)
	{
		if (IsValid(StreamingLevel))
		{
			if (StreamingLevel->GetWorldAsset() == PreviewSublevel)
			{
				if (StreamingLevel->HasLoadedLevel())
				{
					SetPreviewLevel(StreamingLevel->GetLoadedLevel());
				}
				else
				{
					FLatentActionInfo LatentActionInfo;
					LatentActionInfo.CallbackTarget = this;
					LatentActionInfo.ExecutionFunction = FName(TEXT("InitializePreviewLevel"));
					LatentActionInfo.UUID = 1;
					LatentActionInfo.Linkage = 0;

					UGameplayStatics::LoadStreamLevel(World, StreamingLevel->PackageNameToLoad, true, true, LatentActionInfo);
				}

				break;
			}
		}
	}
}

void ABBLevelScriptActor::FinalizeLightingCycle()
{
	if (IsValid(LightingCycle))
	{
		LightingCycle->Finalize();
	}
}

void ABBLevelScriptActor::FinalizePreviewLevel()
{
	if (IsValid(PreviewLevel))
	{
	}

	PreviewLevel = nullptr;
}

void ABBLevelScriptActor::TickLightingCycle()
{
	verifyf(IsValid(LightingCycle), TEXT("Lighting Cycle is invalid."));

	LightingCycle->Tick();
}