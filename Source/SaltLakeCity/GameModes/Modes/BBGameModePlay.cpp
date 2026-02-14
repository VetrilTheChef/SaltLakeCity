// SaltLakeCity 5.7

#include "BBGameModePlay.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "GameStates/Interfaces/IBBGameState.h"

UBBGameModePlay::UBBGameModePlay() :
	Super()
{
	Controller = nullptr;
	GameState = nullptr;
	InputComponent = nullptr;
}

void UBBGameModePlay::Initialize(AIBBPlayerController * NewController, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, AIBBGameState * NewGameState)
{
	verifyf(IsValid(NewController), TEXT("New Controller is invalid."));

	Controller = NewController;

	verifyf(IsValid(NewGameState), TEXT("New Game State is invalid."));

	GameState = NewGameState;

	DestroyInputComponent();

	CreateInputComponent(Controller);
}

void UBBGameModePlay::Finalize()
{
	DestroyInputComponent();
}

void UBBGameModePlay::Activate()
{
}

void UBBGameModePlay::Deactivate()
{
}



void UBBGameModePlay::CreateInputComponent(AIBBPlayerController * PlayerController)
{
	InputComponent = NewObject<UInputComponent>(PlayerController, UInputComponent::StaticClass(), "PlayInputComponent");
	InputComponent->RegisterComponent();
	InputComponent->bBlockInput = true;
}

void UBBGameModePlay::DestroyInputComponent()
{
	if (IsValid(InputComponent))
	{
		InputComponent->ClearActionBindings();
		InputComponent->UnregisterComponent();
		InputComponent->MarkAsGarbage();
	}

	InputComponent = nullptr;
}

void UBBGameModePlay::PushInputComponent()
{
	verifyf(IsValid(Controller), TEXT("Player Controller is invalid."));

	Controller->PushInputComponent(InputComponent);
}

void UBBGameModePlay::PopInputComponent()
{
	verifyf(IsValid(Controller), TEXT("Player Controller is invalid."));

	Controller->PopInputComponent(InputComponent);
}