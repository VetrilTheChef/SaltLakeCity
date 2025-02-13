// SaltLakeCity 4.27

#include "BBGameInstance.h"
#include "Actors/Components/Factories/Interfaces/IBBComponentFactory.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "Levels/BBLevelScriptActor.h"
#include "Specifications/Factories/Interfaces/IBBSpecificationFactory.h"

UBBGameInstance::UBBGameInstance() :
	Super()
{
	GameMode = nullptr;
	GameState = nullptr;
	HUD = nullptr;
	PlayerController = nullptr;

	CommandFactory = nullptr;
	ComponentFactory = nullptr;
	SpecificationFactory = nullptr;
}

void UBBGameInstance::Init()
{
	Super::Init();

	CreateInstances();
}

void UBBGameInstance::Shutdown()
{
	DestroyInstances();

	Super::Shutdown();
}

void UBBGameInstance::Initialize(UWorld * NewWorld, AIBBGameMode * NewGameMode, AIBBGameState * NewGameState, AIBBHUD * NewHUD, AIBBPlayerController * NewPlayerController)
{
	verifyf(IsValid(NewWorld), TEXT("New World is invalid."));
	verifyf(IsValid(NewGameMode), TEXT("New Game Mode is invalid."));
	verifyf(IsValid(NewGameState), TEXT("New Game State is invalid."));
	verifyf(IsValid(NewHUD), TEXT("New HUD is invalid."));
	verifyf(IsValid(NewPlayerController), TEXT("New Player Controller is invalid."));

	GameMode = NewGameMode;
	GameState = NewGameState;
	HUD = NewHUD;
	PlayerController = NewPlayerController;
	
	ULevel * Level = NewWorld->GetCurrentLevel();

	verifyf(IsValid(Level), TEXT("Level is invalid."));
	
	AIBBLevelScriptActor * LevelScriptActor = Cast<AIBBLevelScriptActor>(Level->GetLevelScriptActor());

	GameMode->OnActiveModeUpdate().AddUObject(GameState, &AIBBGameState::UpdateActiveMode);
	GameMode->OnActiveModeUpdate().AddUObject(HUD, &AIBBHUD::UpdateActiveMode);
	GameMode->OnActiveModeUpdate().AddUObject(PlayerController, &AIBBPlayerController::UpdateActiveMode);
	PlayerController->OnFloorChangeRequested().AddUObject(GameState, &AIBBGameState::HandleFloorChangeRequest);

	ComponentFactory->Initialize(HUD);

	GameMode->Initialize();
	GameState->Initialize(LevelScriptActor);
	HUD->Initialize(this, GameMode, GameState, PlayerController);
}

void UBBGameInstance::Finalize(UWorld * OldWorld)
{
	if (IsValid(GameState))
	{
		verifyf(IsValid(OldWorld), TEXT("Old World is invalid."));

		ULevel * Level = OldWorld->GetCurrentLevel();

		verifyf(IsValid(Level), TEXT("Level is invalid."));

		AIBBLevelScriptActor * LevelScriptActor = Cast<AIBBLevelScriptActor>(Level->GetLevelScriptActor());

		GameState->Finalize(LevelScriptActor);
	}

	if (IsValid(GameMode))
	{
		GameMode->OnActiveModeUpdate().RemoveAll(PlayerController);
		GameMode->OnActiveModeUpdate().RemoveAll(HUD);
		GameMode->OnActiveModeUpdate().RemoveAll(GameState);

		GameMode->Finalize();
	}

	if (IsValid(PlayerController))
	{
		PlayerController->OnFloorChangeRequested().RemoveAll(GameState);
	}

	GameState = nullptr;
	GameMode = nullptr;
	PlayerController = nullptr;
}

AIBBGameMode * UBBGameInstance::GetGameMode() const
{
	return GameMode;
}

AIBBGameState * UBBGameInstance::GetGameState() const
{
	return GameState;
}

AIBBHUD * UBBGameInstance::GetHUD() const
{
	return HUD;
}

AIBBPlayerController * UBBGameInstance::GetPlayerController() const
{
	return PlayerController;
}

const UIBBCommandFactory * UBBGameInstance::GetCommandFactory() const
{
	return CommandFactory;
}

const UIBBComponentFactory * UBBGameInstance::GetComponentFactory() const
{
	return ComponentFactory;
}

const UIBBSpecificationFactory * UBBGameInstance::GetSpecificationFactory() const
{
	return SpecificationFactory;
}



void UBBGameInstance::CreateInstances()
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

	ComponentFactory->Initialize(HUD);
}

void UBBGameInstance::CreateSpecificationFactory()
{
	DestroySpecificationFactory();

	if (SpecificationFactoryClass.IsNull()) return;

	SpecificationFactory = NewObject<UIBBSpecificationFactory>(this, SpecificationFactoryClass.LoadSynchronous());

	verifyf(IsValid(SpecificationFactory), TEXT("Specification Factory is invalid."));
}

void UBBGameInstance::DestroyInstances()
{
	DestroySpecificationFactory();
	DestroyComponentFactory();
	DestroyCommandFactory();
}

void UBBGameInstance::DestroyCommandFactory()
{
	if (IsValid(CommandFactory))
	{
		CommandFactory->MarkPendingKill();
	}

	CommandFactory = nullptr;
}

void UBBGameInstance::DestroyComponentFactory()
{
	if (IsValid(ComponentFactory))
	{
		ComponentFactory->MarkPendingKill();
	}

	ComponentFactory = nullptr;
}

void UBBGameInstance::DestroySpecificationFactory()
{
	if (IsValid(SpecificationFactory))
	{
		SpecificationFactory->MarkPendingKill();
	}

	SpecificationFactory = nullptr;
}