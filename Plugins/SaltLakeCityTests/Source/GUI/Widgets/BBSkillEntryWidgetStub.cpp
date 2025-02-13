// SaltLakeCity 4.27

#include "BBSkillEntryWidgetStub.h"

UBBSkillEntryWidgetStub::UBBSkillEntryWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	Name = FText::FromString("");
	Icon = nullptr;
	Value = -1.0f;
	MaxValue = -1.0f;
}

EBBWidget UBBSkillEntryWidgetStub::GetType() const
{
	return EBBWidget::SkillEntry;
}

FText UBBSkillEntryWidgetStub::GetEntryName() const
{
	return Name;
}

void UBBSkillEntryWidgetStub::SetEntryName(FText NewName)
{
	Name = NewName;
}

UTexture2D * UBBSkillEntryWidgetStub::GetIcon() const
{
	return Icon;
}

void UBBSkillEntryWidgetStub::SetIcon(UTexture2D * NewIcon)
{
	Icon = NewIcon;
}

float UBBSkillEntryWidgetStub::GetValue() const
{
	return Value;
}

void UBBSkillEntryWidgetStub::SetValue(float NewValue)
{
	Value = NewValue;
}

float UBBSkillEntryWidgetStub::GetMaxValue() const
{
	return MaxValue;
}

void UBBSkillEntryWidgetStub::SetMaxValue(float NewMaxValue)
{
	MaxValue = NewMaxValue;
}



void UBBSkillEntryWidgetStub::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
}
