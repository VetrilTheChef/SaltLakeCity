// SaltLakeCity 4.27

#include "BBDecalComponentStub.h"
#include "Actors/Interfaces/IBBHighlightable.h"

UBBDecalComponentStub::UBBDecalComponentStub() :
	Super()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBBDecalComponentStub::BeginPlay()
{
	Super::BeginPlay();
}

void UBBDecalComponentStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UBBDecalComponentStub::Initialize(TScriptInterface<IBBHighlightable> && NewHighlightable)
{
	Highlightable = NewHighlightable;

	if (IsValid(Highlightable.GetObject()))
	{
		Highlightable->OnHighlightUpdate().AddUObject(this, & UBBDecalComponentStub::ToggleDecal);
	}
}

void UBBDecalComponentStub::Finalize()
{
	if (IsValid(Highlightable.GetObject()))
	{
		Highlightable->OnHighlightUpdate().RemoveAll(this);
	}

	Highlightable = TScriptInterface<IBBHighlightable>();
}



void UBBDecalComponentStub::ToggleDecal(bool Highlighted)
{
	SetVisibility(Highlighted);
}