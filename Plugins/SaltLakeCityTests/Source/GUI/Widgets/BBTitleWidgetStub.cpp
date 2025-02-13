// SaltLakeCity 4.24

#include "BBTitleWidgetStub.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "GUI/Components/Interfaces/IBBButton.h"

UBBTitleWidgetStub::UBBTitleWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	Icon = nullptr;
	Text = FText::FromString("");
	CloseCommand = nullptr;

	Position = FVector2D::ZeroVector;
}

void UBBTitleWidgetStub::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

EBBWidget UBBTitleWidgetStub::GetType() const
{
	return EBBWidget::Title;
}

void UBBTitleWidgetStub::SetCloseCommand(UIBBCommand * NewCommand)
{
	CloseCommand = NewCommand;
}

void UBBTitleWidgetStub::Drag(FVector2D NewPosition)
{
	Position = NewPosition;

	OnDragged.Broadcast(Position);
}

FVector2D UBBTitleWidgetStub::GetPosition() const
{
	return Position;
}