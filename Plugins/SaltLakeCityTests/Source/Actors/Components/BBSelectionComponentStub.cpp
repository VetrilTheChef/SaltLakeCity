// SaltLakeCity 4.27

#include "BBSelectionComponentStub.h"
#include "InputCoreTypes.h"
#include "Actors/Interfaces/IBBSelectable.h"
#include "Commands/Factories/Interfaces/IBBCommandFactory.h"
#include "Commands/GameStates/Interfaces/IBBSelectCommand.h"

UBBSelectionComponentStub::UBBSelectionComponentStub() :
	Super()
{
	PrimaryComponentTick.bCanEverTick = false;

	Selectable = TScriptInterface<IBBSelectable>();
	Command = nullptr;
}

void UBBSelectionComponentStub::Initialize(TScriptInterface<IBBSelectable> && NewSelectable)
{
	Selectable = NewSelectable;

	if (IsValid(Selectable.GetObject()))
	{
		Selectable->ToActor()->OnClicked.AddDynamic(this, & UBBSelectionComponentStub::Click);
		Selectable->OnSelectionUpdate().AddUObject(this, & UBBSelectionComponentStub::ToggleWidget);
	}
}

void UBBSelectionComponentStub::Finalize()
{
	if (IsValid(Selectable.GetObject()))
	{
		Selectable->ToActor()->OnClicked.RemoveAll(this);
		Selectable->OnSelectionUpdate().RemoveAll(this);
	}

	Selectable = TScriptInterface<IBBSelectable>();
}

TScriptInterface<IBBSelectable> UBBSelectionComponentStub::GetSelectable() const
{
	return Selectable;
}

void UBBSelectionComponentStub::SetSelectable(TScriptInterface<IBBSelectable> && NewSelectable)
{
	Selectable = NewSelectable;
}

const TScriptInterface<IBBWidgetTarget> UBBSelectionComponentStub::GetWidgetTarget() const
{
	return IsValid(Selectable.GetObject()) ? Selectable->ToWidgetTarget() : TScriptInterface<IBBWidgetTarget>();
}




void UBBSelectionComponentStub::Click(AActor * Actor, FKey ButtonPressed)
{
}

void UBBSelectionComponentStub::ToggleWidget(bool Attached)
{
}