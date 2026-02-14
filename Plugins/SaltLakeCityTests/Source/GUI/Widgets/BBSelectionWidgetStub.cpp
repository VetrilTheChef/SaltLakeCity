// SaltLakeCity 5.7

#include "BBSelectionWidgetStub.h"

UBBSelectionWidgetStub::UBBSelectionWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	DisplayName = FText();
}

EBBWidget UBBSelectionWidgetStub::GetType() const
{
	return EBBWidget::Selection;
}

void UBBSelectionWidgetStub::AddToScreen(int32 ZOrder)
{
}

FText UBBSelectionWidgetStub::GetDisplayName()
{
	return DisplayName;
}

void UBBSelectionWidgetStub::SetDisplayName(FText NewDisplayName)
{
	DisplayName = NewDisplayName;
}
