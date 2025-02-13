// SaltLakeCity 4.24

#include "BBContextWidget.h"
#include "Components/VerticalBox.h"
#include "GUI/Widgets/Interfaces/IBBContextRowWidget.h"

UBBContextWidget::UBBContextWidget(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void UBBContextWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeContextBox();
}

void UBBContextWidget::NativeOnMouseLeave(const FPointerEvent & MouseEvent)
{
	Super::NativeOnMouseLeave(MouseEvent);

	OnMouseLeave().Broadcast(MouseEvent);
}

EBBWidget UBBContextWidget::GetType() const
{
	return EBBWidget::Context;
}

void UBBContextWidget::AddRow(UIBBContextRowWidget * & NewRowWidget)
{
	verifyf(IsValid(NewRowWidget), TEXT("Row Widget is invalid."));

	ContextBox->AddChildToVerticalBox(NewRowWidget);
}

void UBBContextWidget::ClearRows()
{
	verifyf(IsValid(ContextBox), TEXT("Context Box is invalid."));

	ContextBox->ClearChildren();
}

void UBBContextWidget::UpdateVisibility(UObject * NewTarget)
{
}

TSoftClassPtr<UIBBContextRowWidget> UBBContextWidget::GetRowWidgetClass() const
{
	return RowWidgetClass;
}



void UBBContextWidget::InitializeContextBox()
{
	verifyf(IsValid(ContextBox), TEXT("Context Box is invalid."));
	
	ContextBox->ClearChildren();
}