// SaltLakeCity 4.27

#include "BBWorkableStub.h"

UBBWorkableStub::UBBWorkableStub() :
	Super()
{
	WorkComponent = nullptr;
	WorkableActor = nullptr;
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();
}

UIBBWorkComponent * UBBWorkableStub::GetWorkComponent() const
{
	return WorkComponent;
}

void UBBWorkableStub::SetSelectionComponent(UIBBWorkComponent * NewWorkComponent)
{
	WorkComponent = NewWorkComponent;
}

AActor * UBBWorkableStub::ToActor()
{
	return WorkableActor;
}

void UBBWorkableStub::SetActor(AActor * NewWorkableActor)
{
	WorkableActor = NewWorkableActor;
}

TScriptInterface<IBBWidgetTarget> UBBWorkableStub::ToWidgetTarget()
{
	return WidgetTarget;
}

void UBBWorkableStub::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}
