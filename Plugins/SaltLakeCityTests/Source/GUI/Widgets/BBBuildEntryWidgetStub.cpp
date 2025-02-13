// SaltLakeCity 4.24

#include "BBBuildEntryWidgetStub.h"
#include "Commands/Interfaces/IBBCommand.h"

UBBBuildEntryWidgetStub::UBBBuildEntryWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	Name = FText::FromString("");
	Icon = nullptr;
	Price = 0.0f;
	Time = 0.0f;
	Command = nullptr;
}

EBBWidget UBBBuildEntryWidgetStub::GetType() const
{
	return EBBWidget::BuildEntry;
}

FText UBBBuildEntryWidgetStub::GetEntryName()
{
	return Name;
}

void UBBBuildEntryWidgetStub::SetEntryName(FText NewName)
{
	Name = NewName;
}

UTexture2D * UBBBuildEntryWidgetStub::GetIcon()
{
	return Icon;
}

void UBBBuildEntryWidgetStub::SetIcon(UTexture2D * NewIcon)
{
	Icon = NewIcon;
}

float UBBBuildEntryWidgetStub::GetPrice()
{
	return Price;
}

void UBBBuildEntryWidgetStub::SetPrice(float NewPrice)
{
	Price = NewPrice;
}

float UBBBuildEntryWidgetStub::GetTime()
{
	return Time;
}

void UBBBuildEntryWidgetStub::SetTime(float NewTime)
{
	Time = NewTime;
}

UIBBCommand * UBBBuildEntryWidgetStub::GetCommand()
{
	return Command;
}

void UBBBuildEntryWidgetStub::SetCommand(UIBBCommand * NewCommand)
{
	Command = NewCommand;
}

void UBBBuildEntryWidgetStub::ClickEntryButton()
{
	if (IsValid(Command))
	{
		Command->Execute();
	}
}



void UBBBuildEntryWidgetStub::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
}
