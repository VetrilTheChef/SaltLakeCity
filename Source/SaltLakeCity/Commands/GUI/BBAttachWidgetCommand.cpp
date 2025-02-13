// SaltLakeCity 4.26

#include "BBAttachWidgetCommand.h"
#include "Actors/Components/Interfaces/IBBWidgetComponent.h"
#include "GUI/Interfaces/IBBHUD.h"

UBBAttachWidgetCommand::UBBAttachWidgetCommand() :
	Super()
{
	HUD = nullptr;
	Component = nullptr;
	Specification = nullptr;
}

void UBBAttachWidgetCommand::SetHUD(AIBBHUD * NewHUD)
{
	HUD = NewHUD;
}

void UBBAttachWidgetCommand::SetWidgetComponent(UIBBWidgetComponent * NewComponent)
{
	Component = NewComponent;
}

void UBBAttachWidgetCommand::SetSpecification(UIBBWidgetSpecification * NewSpecification)
{
	Specification = NewSpecification;
}

void UBBAttachWidgetCommand::Execute()
{
	verifyf(IsValid(HUD), TEXT("HUD is invalid."));

	HUD->AttachWidget(Specification, Component);
}