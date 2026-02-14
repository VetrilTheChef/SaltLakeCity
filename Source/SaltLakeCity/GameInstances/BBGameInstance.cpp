// SaltLakeCity 5.7

#include "BBGameInstance.h"
#include "Actors/Components/Factories/Interfaces/IBBComponentFactory.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "GameInstances/Subsystems/Interfaces/IBBUINotificationSubsystem.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Interfaces/IBBWidgetManager.h"
#include "Levels/BBLevelScriptActor.h"
#include "Specifications/Factories/Interfaces/IBBSpecificationFactory.h"

UBBGameInstance::UBBGameInstance() :
	Super()
{
	GameMode = nullptr;
	GameState = nullptr;
	HUD = nullptr;
	WidgetManager = nullptr;
	PlayerController = nullptr;

	CommandFactory = nullptr;
	ComponentFactory = nullptr;
	SpecificationFactory = nullptr;
}

void UBBGameInstance::Init()
{
	CreateFactories();

	Super::Init();
}

void UBBGameInstance::Shutdown()
{
	Super::Shutdown();

	DestroyFactories();
}

void UBBGameInstance::Initialize(
	UWorld * NewWorld,
	AIBBGameMode* NewGameMode,
	AIBBGameState* NewGameState,
	AIBBHUD* NewHUD,
	AIBBPlayerController* NewPlayerController
)
{
	SetGameModeChecked(NewGameMode);
	SetGameStateChecked(NewGameState);
	SetHUDChecked(NewHUD);
	SetPlayerControllerChecked(NewPlayerController);

	CreateWidgetManager(this, NewGameState, NewGameMode, NewHUD, NewPlayerController);

	verifyf(IsValid(NewWorld), TEXT("New World is invalid."));
	
	ULevel * Level = NewWorld->GetCurrentLevel();

	verifyf(IsValid(Level), TEXT("Level is invalid."));
	
	AIBBLevelScriptActor * LevelScriptActor = Cast<AIBBLevelScriptActor>(Level->GetLevelScriptActor());

	GameMode->OnActiveModeUpdate().AddUObject(NewGameState, &AIBBGameState::UpdateActiveMode);
	GameMode->OnActiveModeUpdate().AddUObject(NewHUD, &AIBBHUD::UpdateActiveMode);
	GameMode->OnActiveModeUpdate().AddUObject(NewPlayerController, &AIBBPlayerController::UpdateActiveMode);

	PlayerController->OnFloorChangeRequested().AddUObject(NewGameState, &AIBBGameState::HandleFloorChangeRequest);

	ComponentFactory->Initialize(NewHUD);

	GameMode->Initialize();
	GameState->Initialize(LevelScriptActor);
	HUD->Initialize(GetSubsystem<UIBBPresentationSubsystem>(), WidgetManager);
	WidgetManager->Initialize(this, NewGameState, NewGameMode, NewHUD, NewPlayerController);
}

void UBBGameInstance::Finalize(UWorld* OldWorld)
{
	if (HUD.IsValid())
	{
		HUD->Finalize();
	}

	if (GameState.IsValid())
	{
		verifyf(IsValid(OldWorld), TEXT("Old World is invalid."));

		ULevel * Level = OldWorld->GetCurrentLevel();

		verifyf(IsValid(Level), TEXT("Level is invalid."));

		AIBBLevelScriptActor * LevelScriptActor = Cast<AIBBLevelScriptActor>(Level->GetLevelScriptActor());

		GameState->Finalize(LevelScriptActor);
	}

	if (GameMode.IsValid())
	{
		GameMode->OnActiveModeUpdate().RemoveAll(PlayerController.Get());
		GameMode->OnActiveModeUpdate().RemoveAll(HUD.Get());
		GameMode->OnActiveModeUpdate().RemoveAll(GameState.Get());

		GameMode->Finalize();
	}

	if (PlayerController.IsValid())
	{
		PlayerController->OnFloorChangeRequested().RemoveAll(GameState.Get());
	}

	DestroyWidgetManager();

	GameState = nullptr;
	GameMode = nullptr;
	HUD = nullptr;
	WidgetManager = nullptr;
	PlayerController = nullptr;
}

AIBBGameMode * UBBGameInstance::GetGameMode() const
{
	return GameMode.Get();
}

AIBBGameState * UBBGameInstance::GetGameState() const
{
	return GameState.Get();
}

AIBBHUD* UBBGameInstance::GetHUD() const
{
	return HUD.Get();
}

AIBBPlayerController* UBBGameInstance::GetPlayerController() const
{
	return PlayerController.Get();
}

UIBBWidgetManager* UBBGameInstance::GetWidgetManager() const
{
	return WidgetManager;
}

const UIBBCommandFactory* UBBGameInstance::GetCommandFactory() const
{
	return CommandFactory;
}

const UIBBComponentFactory* UBBGameInstance::GetComponentFactory() const
{
	return ComponentFactory;
}

const UIBBSpecificationFactory* UBBGameInstance::GetSpecificationFactory() const
{
	return SpecificationFactory;
}



AIBBGameMode* UBBGameInstance::GetGameModeChecked() const
{
	verifyf(GameMode.IsValid(), TEXT("Game Mode is invalid."));

	return GameMode.Get();
}

void UBBGameInstance::SetGameModeChecked(AIBBGameMode* NewGameMode)
{
	verifyf(IsValid(NewGameMode), TEXT("New Game Mode is invalid."));

	GameMode = NewGameMode;
}

AIBBGameState* UBBGameInstance::GetGameStateChecked() const
{
	verifyf(GameState.IsValid(), TEXT("Game State is invalid."));

	return GameState.Get();
}

void UBBGameInstance::SetGameStateChecked(AIBBGameState* NewGameState)
{
	verifyf(IsValid(NewGameState), TEXT("New Game State is invalid."));

	GameState = NewGameState;
}

AIBBHUD* UBBGameInstance::GetHUDChecked() const
{
	verifyf(HUD.IsValid(), TEXT("HUD is invalid."));

	return HUD.Get();
}

void UBBGameInstance::SetHUDChecked(AIBBHUD* NewHUD)
{
	verifyf(IsValid(NewHUD), TEXT("New HUD is invalid."));

	HUD = NewHUD;
}

AIBBPlayerController* UBBGameInstance::GetPlayerControllerChecked() const
{
	verifyf(PlayerController.IsValid(), TEXT("Player Controller is invalid."));

	return PlayerController.Get();
}

void UBBGameInstance::SetPlayerControllerChecked(AIBBPlayerController* NewPlayerController)
{
	verifyf(IsValid(NewPlayerController), TEXT("New Player Controller is invalid."));

	PlayerController = NewPlayerController;
}

void UBBGameInstance::CreateFactories()
{
	CreateCommandFactory();
	CreateComponentFactory();
	CreateSpecificationFactory();
}

void UBBGameInstance::CreateCommandFactory()
{
	DestroyCommandFactory();

	if (CommandFactoryClass.IsNull()) return;

	CommandFactory = NewObject<UIBBCommandFactory>(this, CommandFactoryClass.LoadSynchronous());

	verifyf(IsValid(CommandFactory), TEXT("Command Factory is invalid."));

	CommandFactory->Initialize(this);
}

void UBBGameInstance::CreateComponentFactory()
{
	DestroyComponentFactory();

	if (ComponentFactoryClass.IsNull()) return;

	ComponentFactory = NewObject<UIBBComponentFactory>(this, ComponentFactoryClass.LoadSynchronous());

	verifyf(IsValid(ComponentFactory), TEXT("Component Factory is invalid."));

	ComponentFactory->Initialize(HUD.Get());
}

void UBBGameInstance::CreateSpecificationFactory()
{
	DestroySpecificationFactory();

	if (SpecificationFactoryClass.IsNull()) return;

	SpecificationFactory = NewObject<UIBBSpecificationFactory>(this, SpecificationFactoryClass.LoadSynchronous());

	verifyf(IsValid(SpecificationFactory), TEXT("Specification Factory is invalid."));
}

void UBBGameInstance::DestroyFactories()
{
	DestroySpecificationFactory();
	DestroyComponentFactory();
	DestroyCommandFactory();
}

void UBBGameInstance::DestroyCommandFactory()
{
	if (IsValid(CommandFactory))
	{
		CommandFactory->MarkAsGarbage();
	}

	CommandFactory = nullptr;
}

void UBBGameInstance::DestroyComponentFactory()
{
	if (IsValid(ComponentFactory))
	{
		ComponentFactory->MarkAsGarbage();
	}

	ComponentFactory = nullptr;
}

void UBBGameInstance::DestroySpecificationFactory()
{
	if (IsValid(SpecificationFactory))
	{
		SpecificationFactory->MarkAsGarbage();
	}

	SpecificationFactory = nullptr;
}

void UBBGameInstance::CreateWidgetManager(
	const UIBBGameInstance* NewGameInstance,
	const AIBBGameState* NewGameState,
	AIBBGameMode* NewGameMode,
	AIBBHUD* NewHUD,
	APlayerController* NewPlayerController
)
{
	DestroyWidgetManager();

	verifyf(!WidgetManagerClass.IsNull(), TEXT("Widget Manager class is null."));

	WidgetManager = NewObject<UIBBWidgetManager>(this, WidgetManagerClass.LoadSynchronous());

	verifyf(IsValid(WidgetManager), TEXT("Widget Manager is invalid."));

	WidgetManager->Initialize(NewGameInstance, NewGameState, NewGameMode, NewHUD, NewPlayerController);
}

void UBBGameInstance::DestroyWidgetManager()
{
	if (IsValid(WidgetManager))
	{
		WidgetManager->Finalize();
		WidgetManager->MarkAsGarbage();
	}

	WidgetManager = nullptr;
}