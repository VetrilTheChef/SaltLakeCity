// SaltLakeCity 4.26

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

FText UBBSelectionWidgetStub::GetDisplayName()
{
	return DisplayName;
}

void UBBSelectionWidgetStub::SetDisplayName(FText NewDisplayName)
{
	DisplayName = NewDisplayName;
}
