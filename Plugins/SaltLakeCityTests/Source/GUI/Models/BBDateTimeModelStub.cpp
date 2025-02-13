// SaltLakeCity 4.26

#include "BBDateTimeModelStub.h"
#include "GUI/Widgets/Interfaces/IBBDateTimeWidget.h"

UBBDateTimeModelStub::UBBDateTimeModelStub() :
	Super()
{
	View = nullptr;
	Date = FText::FromString("");
	Time = FText::FromString("");
}

UIBBWidget * UBBDateTimeModelStub::GetWidget() const
{
	return View;
}

void UBBDateTimeModelStub::Initialize(UIBBDateTimeWidget * NewView, UIBBGameClock * NewGameClock)
{
	View = NewView;
}

void UBBDateTimeModelStub::Finalize()
{
	View = nullptr;
}

void UBBDateTimeModelStub::BroadcastDateUpdate(FText NewDate)
{
	UpdateDate(NewDate);
}

void UBBDateTimeModelStub::BroadcastTimeUpdate(FText NewTime)
{
	UpdateTime(NewTime);
}



void UBBDateTimeModelStub::UpdateDate(FText NewDate)
{
	Date = NewDate;

	if (IsValid(View))
	{
		View->SetDate(Date);
	}
}

void UBBDateTimeModelStub::UpdateTime(FText NewTime)
{
	Time = NewTime;

	if (IsValid(View))
	{
		View->SetTime(Time);
	}
}