// SaltLakeCity 4.27

#include "BBSelectableStub.h"

UBBSelectableStub::UBBSelectableStub() :
	Super()
{
	SelectionComponent = nullptr;
	SelectableActor = nullptr;
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();
	IsSelected = false;
}

void UBBSelectableStub::UpdateSelection(bool Selected)
{
	IsSelected = Selected;
}

bool UBBSelectableStub::GetIsSelected() const
{
	return IsSelected;
}

UIBBSelectionComponent * UBBSelectableStub::GetSelectionComponent() const
{
	return SelectionComponent;
}

void UBBSelectableStub::SetSelectionComponent(UIBBSelectionComponent * NewSelectionComponent)
{
	SelectionComponent = NewSelectionComponent;
}

AActor * UBBSelectableStub::ToActor()
{
	return SelectableActor;
}

void UBBSelectableStub::SetActor(AActor * NewSelectableActor)
{
	SelectableActor = NewSelectableActor;
}

TScriptInterface<IBBWidgetTarget> UBBSelectableStub::ToWidgetTarget()
{
	return WidgetTarget;
}

void UBBSelectableStub::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}