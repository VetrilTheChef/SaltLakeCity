// SaltLakeCity 5.7

#include "BBWidgetStub.h"
#include "Blueprint/GameViewportSubsystem.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UBBWidgetStub::UBBWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	InViewport = false;
}

EBBWidget UBBWidgetStub::GetType() const
{
	return EBBWidget::None;
}

void UBBWidgetStub::AddToScreen(int32 ZOrder)
{
	InViewport = true;
}

FVector2D UBBWidgetStub::GetPositionInViewport(bool bRemoveDPIScale)
{
	//UGameViewportSubsystem* Subsystem = UGameViewportSubsystem::Get(GetWorld());

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