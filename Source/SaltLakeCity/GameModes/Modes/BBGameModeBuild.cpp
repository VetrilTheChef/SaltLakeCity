// SaltLakeCity 4.25

#include "BBGameModeBuild.h"
#include "Controllers/Interfaces/IBBPlayerController.h"
#include "Engine/World.h"
#include "GameStates/Interfaces/IBBGameState.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"

UBBGameModeBuild::UBBGameModeBuild() :
	Super()
{
	Controller = nullptr;
	GameState = nullptr;
	HUD = nullptr;
	InputComponent = nullptr;
	BuildWidgetSpecification = nullptr;
}

void UBBGameModeBuild::Initialize(AIBBPlayerController * NewController, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, AIBBGameState * NewGameState)
{
	verifyf(IsValid(NewController), TEXT("New Controller is invalid."));

	Controller = NewController;

	verifyf(IsValid(NewGameState), TEXT("New Game State is invalid."));

	GameState = NewGameState;

	HUD = Controller->GetHUD<AIBBHUD>();

	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	CreateInputComponent(Controller);
	CreateWidgetSpecification(WidgetSpecificationFactory);
}

void UBBGameModeBuild::Finalize()
{
	DestroyWidgetSpecification();
	DestroyInputComponent();
}

void UBBGameModeBuild::Activate()
{
	PushInputComponent();
	OpenBuildWidget();
	ToggleGrid(true);
}

void UBBGameModeBuild::Deactivate()
{
	PopInputComponent();
	CloseBuildWidget();
	ToggleGrid(false);
}



void UBBGameModeBuild::CreateInputComponent(AIBBPlayerController * PlayerController)
{
}

void UBBGameModeBuild::DestroyInputComponent()
{
	if (IsValid(InputComponent))
	{
		InputComponent->ClearActionBindings();
		InputComponent->UnregisterComponent();
		InputComponent->MarkPendingKill();
	}

	InputComponent = nullptr;
}

void UBBGameModeBuild::CreateWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	WidgetSpecificationFactory->NewBuildWidgetSpecification(BuildWidgetSpecification, this);
}

void UBBGameModeBuild::DestroyWidgetSpecification()
{
	if (IsValid(BuildWidgetSpecification))
	{
		BuildWidgetSpecification->MarkPendingKill();
	}

	BuildWidgetSpecification = nullptr;
}

void UBBGameModeBuild::PushInputComponent()
{
	verifyf(IsValid(Controller), TEXT("Player Controller is invalid."));

	Controller->PushInputComponent(InputComponent);
}

void UBBGameModeBuild::PopInputComponent()
{
	verifyf(IsValid(Controller), TEXT("Player Controller is invalid."));

	Controller->PopInputComponent(InputComponent);
}

void UBBGameModeBuild::OpenBuildWidget()
{
	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	HUD->OpenWidget(BuildWidgetSpecification, false);
}

void UBBGameModeBuild::CloseBuildWidget()
{
	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	HUD->CloseWidget(BuildWidgetSpecification);
}

void UBBGameModeBuild::ToggleGrid(bool Enabled)
{
	verifyf(IsValid(GameState), TEXT("Game State is invalid."));

	GameState->SetGridVisibility(Enabled);
}