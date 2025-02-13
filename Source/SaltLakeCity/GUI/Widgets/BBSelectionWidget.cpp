// SaltLakeCity 4.26

#include "BBSelectionWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

UBBSelectionWidget::UBBSelectionWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
}

EBBWidget UBBSelectionWidget::GetType() const
{
	return EBBWidget::Selection;
}

void UBBSelectionWidget::SetDisplayName(FText NewDisplayName)
{
	verifyf(IsValid(DisplayNameText), TEXT("Display Name Text is invalid."));

	DisplayNameText->SetText(NewDisplayName);
}
