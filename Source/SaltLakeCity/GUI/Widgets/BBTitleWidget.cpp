// SaltLakeCity 4.24

#include "BBTitleWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "GUI/Interfaces/IBBHUD.h"
#include "GUI/Components/BBButton.h"

UBBTitleWidget::UBBTitleWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	DragOffset = FVector2D::ZeroVector;
}

void UBBTitleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeTitle();
}

EBBWidget UBBTitleWidget::GetType() const
{
	return EBBWidget::None;
}

void UBBTitleWidget::SetCloseCommand(UIBBCommand * NewCommand)
{
	verifyf(IsValid(CloseButton), TEXT("Close Button is invalid."));

	CloseButton->SetCommand(NewCommand);
}



void UBBTitleWidget::NativeOnDragCancelled(const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
	FVector2D Position = InDragDropEvent.GetScreenSpacePosition() - DragOffset;

	OnDragged.Broadcast(Position);

	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

void UBBTitleWidget::NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent, UDragDropOperation * & OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UIBBWidget * Widget = nullptr;
	OnDragDetected.Broadcast(Widget);

	DragOffset = InMouseEvent.GetScreenSpacePosition() - InGeometry.GetAbsolutePositionAtCoordinates(FVector2D::ZeroVector);

	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());

	OutOperation->DefaultDragVisual = Widget;
	OutOperation->Offset = FVector2D::ZeroVector;
	OutOperation->Payload = Widget;
	OutOperation->Pivot = EDragPivot::MouseDown;

	FVector2D Position = FVector2D::ZeroVector;

	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	UGameViewportClient * Viewport = GetWorld()->GetGameViewport();

	verifyf(IsValid(Viewport), TEXT("Game Viewport Client is invalid."));
	
	Viewport->GetViewportSize(Position);
	Position += InGeometry.GetAbsolutePositionAtCoordinates(FVector2D::ZeroVector) + FVector2D(1.0, 1.0);

	OnDragged.Broadcast(Position);
}

FReply UBBTitleWidget::NativeOnMouseButtonUp(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	FEventReply EventReply = UWidgetBlueprintLibrary::Handled();
	EventReply.NativeReply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		EventReply = UWidgetBlueprintLibrary::ReleaseMouseCapture(EventReply);
	}

	return EventReply.NativeReply;
}

FReply UBBTitleWidget::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	FEventReply EventReply = UWidgetBlueprintLibrary::Handled();
	EventReply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		EventReply = UWidgetBlueprintLibrary::CaptureMouse(EventReply, this);
	}

	return EventReply.NativeReply;
}

void UBBTitleWidget::InitializeTitle()
{
	InitializeIcon();
	InitializeText();
}

void UBBTitleWidget::InitializeIcon()
{
	verifyf(IsValid(TitleIcon), TEXT("Title Icon is invalid."));

	TitleIcon->SetBrushFromTexture(Icon, false);
}

void UBBTitleWidget::InitializeText()
{
	verifyf(IsValid(TitleText), TEXT("Title Text is invalid."));

	TitleText->SetText(Text);
}

bool UBBTitleWidget::ClampPosition(FVector2D & Position, FVector2D Min, FVector2D Max)
{
	Position.X = FMath::Clamp(Position.X, Min.X, Max.X);
	Position.Y = FMath::Clamp(Position.Y, Min.Y, Max.Y);

	return false;
}