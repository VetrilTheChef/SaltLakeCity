// SaltLakeCity 5.7

#include "BBContextWidgetStub.h"
#include "GUI/Widgets/Interfaces/IBBContextRowWidget.h"

UBBContextWidgetStub::UBBContextWidgetStub(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	RowWidgetClass = TSoftClassPtr<UIBBContextRowWidget>();
	RowWidgets.Empty();

	InViewport = false;
}

EBBWidget UBBContextWidgetStub::GetType() const
{
	return EBBWidget::Context;
}

void UBBContextWidgetStub::AddToScreen(int32 ZOrder)
{
	InViewport = true;
}

void UBBContextWidgetStub::RemoveFromParent()
{
	InViewport = false;
}

void UBBContextWidgetStub::AddRow(UIBBContextRowWidget*& NewRowWidget)
{
	RowWidgets.Emplace(NewRowWidget);
}

void UBBContextWidgetStub::ClearRows()
{
	RowWidgets.Empty();
}

int UBBContextWidgetStub::GetNumRows()
{
	return RowWidgets.Num();
}

UIBBContextRowWidget * UBBContextWidgetStub::GetRowWidget(int Index)
{
	return RowWidgets.IsValidIndex(Index) ? RowWidgets[Index] : nullptr;
}

void UBBContextWidgetStub::UpdateVisibility(UObject* NewTarget)
{
}

TSoftClassPtr<UIBBContextRowWidget> UBBContextWidgetStub::GetRowWidgetClass() const
{
	return RowWidgetClass;
}

void UBBContextWidgetStub::SetRowWidgetClass(TSoftClassPtr<UIBBContextRowWidget> NewRowWidgetClass)
{
	RowWidgetClass = NewRowWidgetClass;
}

bool UBBContextWidgetStub::IsInViewport()
{
	return InViewport;
}

void UBBContextWidgetStub::SetIsInViewport(bool IsInViewport)
{
	InViewport = IsInViewport;
}

void UBBContextWidgetStub::BroadcastOnMouseLeave(FPointerEvent& MouseEvent)
{
	OnMouseLeave().Broadcast(MouseEvent);
}