// SaltLakeCity 4.26

#include "BBDetachWidgetCommand.h"
#include "GUI/Interfaces/IBBHUD.h"

UBBDetachWidgetCommand::UBBDetachWidgetCommand() :
	Super()
{
	HUD = nullptr;
	Component = nullptr;
}

void UBBDetachWidgetCommand::SetHUD(AIBBHUD * NewHUD)
{
	HUD = NewHUD;
}

void UBBDetachWidgetCommand::SetWidgetComponent(UIBBWidgetComponent * NewComponent)
{
	Component = NewComponent;
}

void UBBDetachWidgetCommand::Execute()
{
	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	HUD->DetachWidget(Component);
}