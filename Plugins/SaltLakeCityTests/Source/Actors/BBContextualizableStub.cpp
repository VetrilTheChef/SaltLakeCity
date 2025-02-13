// SaltLakeCity 4.27

#include "BBContextualizableStub.h"

UBBContextualizableStub::UBBContextualizableStub() :
	Super()
{
	ContextComponent = nullptr;
	ContextualizableActor = nullptr;
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();
	ContextOptions.Empty();
	IsContextualized = false;
}

void UBBContextualizableStub::UpdateContext(bool Contextualized)
{
	IsContextualized = Contextualized;
}

bool UBBContextualizableStub::GetIsContextualized() const
{
	return IsContextualized;
}

bool UBBContextualizableStub::IsContextOption(EBBContext ContextOption) const
{
	return ContextOptions.Contains(ContextOption);
}

void UBBContextualizableStub::SetContextOptions(TSet<EBBContext> NewValidContextOptions)
{
	ContextOptions = NewValidContextOptions;
}

UIBBContextComponent * UBBContextualizableStub::GetContextComponent() const
{
	return ContextComponent;
}

void UBBContextualizableStub::SetContextComponent(UIBBContextComponent * NewContextComponent)
{
	ContextComponent = NewContextComponent;
}

AActor * UBBContextualizableStub::ToActor()
{
	return ContextualizableActor;
}

void UBBContextualizableStub::SetActor(AActor * NewContextualizableActor)
{
	ContextualizableActor = NewContextualizableActor;
}

TScriptInterface<IBBWidgetTarget> UBBContextualizableStub::ToWidgetTarget()
{
	return WidgetTarget;
}

void UBBContextualizableStub::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}
