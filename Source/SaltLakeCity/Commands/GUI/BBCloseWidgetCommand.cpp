// SaltLakeCity 4.25

#include "BBCloseWidgetCommand.h"
#include "GUI/Interfaces/IBBHUD.h"

UBBCloseWidgetCommand::UBBCloseWidgetCommand() :
	Super()
{
	HUD = nullptr;
	Specification = nullptr;
}

void UBBCloseWidgetCommand::SetHUD(AIBBHUD * NewHUD)
{
	HUD = NewHUD;
}

void UBBCloseWidgetCommand::SetSpecification(UIBBWidgetSpecification * NewSpecification)
{
	Specification = NewSpecification;
}

void UBBCloseWidgetCommand::Execute()
{
	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	HUD->CloseWidget(Specification);
}