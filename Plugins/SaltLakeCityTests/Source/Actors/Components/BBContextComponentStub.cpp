// SaltLakeCity 4.27

#include "BBContextComponentStub.h"
#include "Actors/Interfaces/IBBContextualizable.h"

UBBContextComponentStub::UBBContextComponentStub() :
	Super()
{
	PrimaryComponentTick.bCanEverTick = false;

	Contextualizable = TScriptInterface<IBBContextualizable>();

	Context.Empty();
}

void UBBContextComponentStub::BeginPlay()
{
	Super::BeginPlay();
}

void UBBContextComponentStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UBBContextComponentStub::Initialize(TScriptInterface<IBBContextualizable> && NewContextualizable)
{
	Contextualizable = NewContextualizable;
}

void UBBContextComponentStub::Finalize()
{
	Contextualizable.SetObject(nullptr);
}

TScriptInterface<IBBContextualizable> UBBContextComponentStub::GetContextualizable() const
{
	return Contextualizable;
}

void UBBContextComponentStub::SetContextualizable(TScriptInterface<IBBContextualizable> && NewContextualizable)
{
	Contextualizable = NewContextualizable;
}

void UBBContextComponentStub::AddOption(EBBContext Option)
{
	Context.Add(Option);
}

void UBBContextComponentStub::RemoveOption(EBBContext Option)
{
	Context.Remove(Option);
}

void UBBContextComponentStub::ClearOptions()
{
	Context.Empty();
}

bool UBBContextComponentStub::IsOption(EBBContext Option) const
{
	return Context.Contains(Option);
}

const TScriptInterface<IBBWidgetTarget> UBBContextComponentStub::GetWidgetTarget() const
{
	return IsValid(Contextualizable.GetObject()) ? Contextualizable->ToWidgetTarget() : TScriptInterface<IBBWidgetTarget>();
}



void UBBContextComponentStub::ShowContext()
{
}

void UBBContextComponentStub::HideContext()
{
}