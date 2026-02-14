// SaltLakeCity 5.7

#include "BBWidget.h"

UBBWidget::UBBWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UBBWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBBWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBBWidget::BeginDestroy()
{
	Super::BeginDestroy();
}

EBBWidget UBBWidget::GetType() const
{
	return EBBWidget::None;
}

void UBBWidget::AddToScreen(int32 ZOrder)
{
	AddToViewport(ZOrder);
}



FReply UBBWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return FReply::Handled();
}