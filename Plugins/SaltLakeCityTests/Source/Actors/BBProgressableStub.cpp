// SaltLakeCity 4.27

#include "BBProgressableStub.h"

UBBProgressableStub::UBBProgressableStub() :
	Super()
{
	ProgressComponent = nullptr;
	ProgressableActor = nullptr;
	WidgetTarget = TScriptInterface<IBBWidgetTarget>();
	Progress = -1.0f;
}

float UBBProgressableStub::GetProgress() const
{
	return Progress;
}

void UBBProgressableStub::SetProgress(float NewProgress)
{
	Progress = NewProgress;
}

UIBBProgressComponent * UBBProgressableStub::GetProgressComponent() const
{
	return ProgressComponent;
}

void UBBProgressableStub::SetProgressComponent(UIBBProgressComponent * NewProgressComponent)
{
	ProgressComponent = NewProgressComponent;
}

AActor * UBBProgressableStub::ToActor()
{
	return ProgressableActor;
}

void UBBProgressableStub::SetActor(AActor * NewProgressableActor)
{
	ProgressableActor = NewProgressableActor;
}

TScriptInterface<IBBWidgetTarget> UBBProgressableStub::ToWidgetTarget()
{
	return WidgetTarget;
}

void UBBProgressableStub::SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget)
{
	WidgetTarget = NewWidgetTarget;
}

void UBBProgressableStub::BroadcastProgressInitiation()
{
	OnProgressInitiation().Broadcast();
}

void UBBProgressableStub::BroadcastProgressUpdate()
{
	OnProgressUpdate().Broadcast(Progress);
}

void UBBProgressableStub::BroadcastProgressCompletion()
{
	OnProgressCompletion().Broadcast();
}
