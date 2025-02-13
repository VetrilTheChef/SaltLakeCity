// SaltLakeCity 4.27

#include "BBProgressComponentStub.h"

UBBProgressComponentStub::UBBProgressComponentStub() :
	Super()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	Progressable = TScriptInterface<IBBProgressable>();
	Progress = -1.0f;
}

void UBBProgressComponentStub::BeginPlay()
{
	Super::BeginPlay();
}

void UBBProgressComponentStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UBBProgressComponentStub::Initialize(TScriptInterface<IBBProgressable> && NewProgressable)
{
	Progressable = NewProgressable;
}

void UBBProgressComponentStub::Finalize()
{
}

TScriptInterface<IBBProgressable> UBBProgressComponentStub::GetProgressable() const
{
	return Progressable;
}

void UBBProgressComponentStub::SetProgressable(TScriptInterface<IBBProgressable>&& NewProgressable)
{
	Progressable = NewProgressable;
}

float UBBProgressComponentStub::GetProgress()
{
	return Progress;
}

void UBBProgressComponentStub::SetProgress(float NewProgress)
{
	Progress = NewProgress;

	OnProgressUpdate().Broadcast(Progress);
}

const TScriptInterface<IBBWidgetTarget> UBBProgressComponentStub::GetWidgetTarget() const
{
	return IsValid(Progressable.GetObject()) ? Progressable->ToWidgetTarget() : TScriptInterface<IBBWidgetTarget>();
}