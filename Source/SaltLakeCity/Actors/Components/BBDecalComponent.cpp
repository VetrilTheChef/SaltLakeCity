// SaltLakeCity 4.26

#include "BBDecalComponent.h"
#include "Actors/Interfaces/IBBHighlightable.h"

UBBDecalComponent::UBBDecalComponent() :
	Super()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	Highlightable = TScriptInterface<IBBHighlightable>();
}

void UBBDecalComponent::BeginPlay()
{
	Super::BeginPlay();

	SetVisibility(false);
}

void UBBDecalComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UBBDecalComponent::Initialize(TScriptInterface<IBBHighlightable> && NewHighlightable)
{
	SetDecalMaterial(HighlightMaterial.LoadSynchronous());

	Subscribe(Forward<TScriptInterface<IBBHighlightable>>(NewHighlightable));
}

void UBBDecalComponent::Finalize()
{
	Unsubscribe(Highlightable);

	SetDecalMaterial(nullptr);
}

void UBBDecalComponent::Subscribe(TScriptInterface<IBBHighlightable> && NewHighlightable)
{
	Unsubscribe(Highlightable);

	verifyf(IsValid(NewHighlightable.GetObject()), TEXT("New Highlightable is invalid."));

	Highlightable = NewHighlightable;

	Highlightable->OnHighlightUpdate().AddUObject(this, & UBBDecalComponent::ToggleDecal);
}

void UBBDecalComponent::Unsubscribe(TScriptInterface<IBBHighlightable> & OldHighlightable)
{
	if (IsValid(OldHighlightable.GetObject()))
	{
		OldHighlightable->OnHighlightUpdate().RemoveAll(this);
	}

	OldHighlightable.SetObject(nullptr);
}
void UBBDecalComponent::ToggleDecal(bool Highlighted)
{
	SetVisibility(Highlighted);
}