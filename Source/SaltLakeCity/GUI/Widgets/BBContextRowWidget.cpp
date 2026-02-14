// SaltLakeCity 5.7

#include "BBContextRowWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "GUI/Components/BBButton.h"
#include "GUI/Widgets/BBContextWidget.h"

UBBContextRowWidget::UBBContextRowWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UBBContextRowWidget::NativeOnInitialized()
{
	verifyf(IsValid(RowButton), TEXT("Row Button is invalid."));

	RowButton->OnClicked.AddDynamic(this, &UBBContextRowWidget::Click);
}

void UBBContextRowWidget::NativeDestruct()
{
	verifyf(IsValid(RowButton), TEXT("Row Button is invalid."));

	RowButton->OnClicked.RemoveDynamic(this, &UBBContextRowWidget::Click);
}

EBBWidget UBBContextRowWidget::GetType() const
{
	return EBBWidget::None;
}

void UBBContextRowWidget::AddToScreen(int32 ZOrder)
{
	AddToViewport(ZOrder);
}

void UBBContextRowWidget::SetRowName(FText NewName)
{
	verifyf(IsValid(RowText), TEXT("Row Text is invalid."));

	RowText->SetText(NewName);
}
void UBBContextRowWidget::SetRowIcon(UTexture2D* NewIcon)
{
	verifyf(IsValid(RowIcon), TEXT("Row Icon is invalid."));

	RowIcon->SetBrushFromTexture(NewIcon, false);
}

void UBBContextRowWidget::SetRowTooltip(FText NewTooltip)
{
	verifyf(IsValid(RowButton), TEXT("Row Button is invalid."));

	RowButton->SetToolTipText(NewTooltip);
}

void UBBContextRowWidget::SetCommand(UIBBCommand* Command)
{
	verifyf(IsValid(RowButton), TEXT("Row Button is invalid."));
	
	RowButton->SetCommand(Command);
}



void UBBContextRowWidget::Click()
{
	OnClicked().Broadcast();
}