// SaltLakeCity 4.27

#include "BBWorldSettings.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "GameInstances/Interfaces/IBBGameInstance.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "Levels/BBLevelScriptActor.h"

ABBWorldSettings::ABBWorldSettings() :
	Super()
{
}

void ABBWorldSettings::BeginPlay()
{
	Super::BeginPlay();
}

void ABBWorldSettings::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABBWorldSettings::NotifyBeginPlay()
{
	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	APlayerController * PlayerController = nullptr;
	AHUD * HUD = nullptr;
	AIBBGameMode * GameMode = nullptr;
	AIBBGameState * GameState = nullptr;
	AIBBLevelScriptActor * LevelScriptActor = nullptr;
	UIBBGameInstance * GameInstance = nullptr;

	if (!World->bBegunPlay)
	{
		const bool bFromLevelLoad = true;

		PlayerController = World->GetFirstPlayerController();

		verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));

		PlayerController->DispatchBeginPlay(bFromLevelLoad);

		HUD = PlayerController->GetHUD();

		verifyf(IsValid(HUD), TEXT("HUD is invalid."));

		HUD->DispatchBeginPlay(bFromLevelLoad);

		GameMode = World->GetAuthGameMode<AIBBGameMode>();

		verifyf(IsValid(GameMode), TEXT("Game Mode is invalid."));

		GameMode->DispatchBeginPlay(bFromLevelLoad);

		GameState = World->GetGameState<AIBBGameState>();

		verifyf(IsValid(GameState), TEXT("Game State is invalid."));

		GameState->DispatchBeginPlay(bFromLevelLoad);

		ULevel * CurrentLevel = World->GetCurrentLevel();

		verifyf(IsValid(CurrentLevel), TEXT("Current Level is invalid."));

		LevelScriptActor = Cast<AIBBLevelScriptActor>(CurrentLevel->LevelScriptActor);

		verifyf(IsValid(LevelScriptActor), TEXT("Level Script Actor is invalid."));

		LevelScriptActor->DispatchBeginPlay();

		GameInstance = World->GetGameInstance<UIBBGameInstance>();

		verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

		// Resolve actor dependencies

		GameInstance->Initialize(World, GameMode, GameState, Cast<AIBBHUD>(HUD), Cast<AIBBPlayerController>(PlayerController));
	}

	Super::NotifyBeginPlay();
}

void ABBWorldSettings::NotifyEndPlay()
{
	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	UIBBGameInstance * GameInstance = World->GetGameInstance<UIBBGameInstance>();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	GameInstance->Finalize(World);
}