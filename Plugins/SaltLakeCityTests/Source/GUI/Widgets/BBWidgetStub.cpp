// SaltLakeCity 4.24

#include "BBWidgetStub.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UBBWidgetStub::UBBWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	InViewport = false;
}

void UBBWidgetStub::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	InViewport = true;
}

EBBWidget UBBWidgetStub::GetType() const
{
	return EBBWidget::None;
}

FVector2D UBBWidgetStub::GetPositionInViewport(bool bRemoveDPIScale)
{
	FVector2D Position = GetFullScreenOffset().GetTopLeft();;

	float Scale = bRemoveDPIScale ? UWidgetLayoutLibrary::GetViewportScale(this) : 1.0f;

	Position.X *= Scale;
	Position.Y *= Scale;

	return Position;
}

bool UBBWidgetStub::IsInViewport()
{
	return InViewport;
}

void UBBWidgetStub::SetIsInViewport(bool IsInViewport)
{
	InViewport = IsInViewport;
}