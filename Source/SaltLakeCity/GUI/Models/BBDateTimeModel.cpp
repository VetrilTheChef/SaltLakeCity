// SaltLakeCity 4.26

#include "BBDateTimeModel.h"
#include "GameStates/Components/Interfaces/IBBGameClock.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"
#include "Specifications/GUI/Interfaces/IBBDateTimeWidgetSpecification.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBDateTimeModel::UBBDateTimeModel() :
	Super()
{
	View = nullptr;
	GameClock = nullptr;
}

UIBBWidget * UBBDateTimeModel::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBDateTimeModel::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	UIBBWidgetSpecification * DateTimeWidgetSpecification = nullptr;

	WidgetSpecificationFactory->NewDateTimeWidgetSpecification(DateTimeWidgetSpecification, this);

	return DateTimeWidgetSpecification;
}

void UBBDateTimeModel::Initialize(UIBBDateTimeWidget * NewView, UIBBGameClock * NewGameClock)
{
	InitializeView(NewView);
	InitializeGameClock(NewGameClock);
}

void UBBDateTimeModel::Finalize()
{
	FinalizeGameClock();
	FinalizeView();
}



void UBBDateTimeModel::InitializeView(UIBBDateTimeWidget * NewView)
{
	FinalizeView();

	verifyf(IsValid(NewView), TEXT("New Date Time View is invalid."));

	View = NewView;
}

void UBBDateTimeModel::InitializeGameClock(UIBBGameClock * NewGameClock)
{
	FinalizeGameClock();

	verifyf(IsValid(NewGameClock), TEXT("New Game Clock is invalid."));

	GameClock = NewGameClock;

	GameClock->OnDateUpdate.AddDynamic(this, &UBBDateTimeModel::UpdateDate);
	GameClock->OnTimeUpdate.AddDynamic(this, &UBBDateTimeModel::UpdateTime);
}

void UBBDateTimeModel::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBDateTimeModel::FinalizeGameClock()
{
	if (IsValid(GameClock))
	{
		GameClock->OnDateUpdate.RemoveDynamic(this, &UBBDateTimeModel::UpdateDate);
		GameClock->OnTimeUpdate.RemoveDynamic(this, &UBBDateTimeModel::UpdateTime);
	}

	GameClock = nullptr;
}



void UBBDateTimeModel::UpdateDate(FText Date)
{
	verifyf(IsValid(View), TEXT("Date Time View is invalid."));

	View->SetDate(Date);
}

void UBBDateTimeModel::UpdateTime(FText Time)
{
	verifyf(IsValid(View), TEXT("Date Time View is invalid."));

	View->SetTime(Time);
}