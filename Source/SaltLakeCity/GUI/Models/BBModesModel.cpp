// SaltLakeCity 4.26

#include "BBModesModel.h"
#include "GameModes/Interfaces/IBBGameMode.h"
#include "GUI/Widgets/Interfaces/IBBModesWidget.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBModesModel::UBBModesModel() :
	Super()
{
	View = nullptr;
	GameMode = nullptr;
}

UIBBWidget * UBBModesModel::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBModesModel::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	UIBBWidgetSpecification * ModesWidgetSpecification = nullptr;

	WidgetSpecificationFactory->NewModesWidgetSpecification(ModesWidgetSpecification, this);

	return ModesWidgetSpecification;
}

void UBBModesModel::Initialize(UIBBModesWidget * NewView, AIBBGameMode * NewGameMode)
{
	InitializeView(NewView);
	InitializeGameMode(NewGameMode);
}

void UBBModesModel::Finalize()
{
	FinalizeGameMode();
	FinalizeView();
}



void UBBModesModel::InitializeView(UIBBModesWidget * NewView)
{
	FinalizeView();

	verifyf(IsValid(NewView), TEXT("New Modes View is invalid."));

	View = NewView;
}

void UBBModesModel::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBModesModel::InitializeGameMode(AIBBGameMode * NewGameMode)
{
	FinalizeGameMode();

	verifyf(IsValid(NewGameMode), TEXT("New Game Mode is invalid."));

	GameMode = NewGameMode;

	GameMode->OnActiveModeUpdate().AddUObject(this, &UBBModesModel::UpdateMode);
}

void UBBModesModel::FinalizeGameMode()
{
	if (IsValid(GameMode))
	{
		GameMode->OnActiveModeUpdate().RemoveAll(this);
	}

	GameMode = nullptr;
}



void UBBModesModel::UpdateMode(EBBGameMode NewGameMode)
{
	OnModeUpdate.Broadcast(NewGameMode);
}