// SaltLakeCity 4.26

#include "BBOpenWidgetCommand.h"
#include "GUI/Interfaces/IBBHUD.h"

UBBOpenWidgetCommand::UBBOpenWidgetCommand() :
	Super()
{
	HUD = nullptr;
	Specification = nullptr;
	PopUp = false;
}

void UBBOpenWidgetCommand::SetHUD(AIBBHUD * NewHUD)
{
	HUD = NewHUD;
}

void UBBOpenWidgetCommand::SetSpecification(UIBBWidgetSpecification * NewSpecification)
{
	Specification = NewSpecification;
}

bool UBBOpenWidgetCommand::GetPopUp()
{
	return PopUp;
}

void UBBOpenWidgetCommand::SetPopUp(bool NewPopUp)
{
	PopUp = NewPopUp;
}

void UBBOpenWidgetCommand::Execute()
{
	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	HUD->OpenWidget(Specification, PopUp);
}