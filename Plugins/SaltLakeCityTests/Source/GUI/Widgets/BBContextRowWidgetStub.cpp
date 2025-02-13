// SaltLakeCity 4.24

#include "BBContextRowWidgetStub.h"
#include "Commands/Interfaces/IBBCommand.h"

UBBContextRowWidgetStub::UBBContextRowWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	Name = FText::FromString("");
	Icon = nullptr;
	Tooltip = FText::FromString("");
	Command = nullptr;
	TestVisibility = ESlateVisibility::Hidden;
}

EBBWidget UBBContextRowWidgetStub::GetType() const
{
	return EBBWidget::None;
}

FText UBBContextRowWidgetStub::GetRowName() const
{
	return Name;
}

void UBBContextRowWidgetStub::SetRowName(FText NewName)
{
	Name = NewName;
}

UTexture2D * UBBContextRowWidgetStub::GetRowIcon() const
{
	return Icon;
}

void UBBContextRowWidgetStub::SetRowIcon(UTexture2D * NewIcon)
{
	Icon = NewIcon;
}

FText UBBContextRowWidgetStub::GetRowTooltip() const
{
	return Tooltip;
}

void UBBContextRowWidgetStub::SetRowTooltip(FText NewTooltip)
{
	Tooltip = NewTooltip;
}

UIBBCommand * UBBContextRowWidgetStub::GetCommand()
{
	return Command;
}

void UBBContextRowWidgetStub::SetCommand(UIBBCommand * NewCommand)
{
	Command = NewCommand;
}

void UBBContextRowWidgetStub::ClickRowButton()
{
	if (IsValid(Command))
	{
		Command->Execute();
	}

	OnClicked().Broadcast();
}



ESlateVisibility UBBContextRowWidgetStub::GetTestVisibility()
{
	return TestVisibility;
}

void UBBContextRowWidgetStub::SetVisibility(ESlateVisibility InVisibility)
{
	TestVisibility = InVisibility;

	Super::SetVisibility(InVisibility);
}