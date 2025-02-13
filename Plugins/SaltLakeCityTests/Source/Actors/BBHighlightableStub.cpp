// SaltLakeCity 4.27

#include "BBHighlightableStub.h"

UBBHighlightableStub::UBBHighlightableStub() :
	Super()
{
	DecalComponent = nullptr;
	HighlightableActor = nullptr;
	IsHighlighted = false;
}

void UBBHighlightableStub::UpdateHighlight(bool Highlighted)
{
	IsHighlighted = Highlighted;
}

bool UBBHighlightableStub::GetIsHighlighted() const
{
	return IsHighlighted;
}

UIBBDecalComponent * UBBHighlightableStub::GetDecalComponent() const
{
	return nullptr;
}

void UBBHighlightableStub::SetDecalComponent(UIBBDecalComponent * NewDecalComponent)
{
	DecalComponent = NewDecalComponent;
}

AActor * UBBHighlightableStub::ToActor()
{
	return HighlightableActor;
}

void UBBHighlightableStub::SetActor(AActor * NewHighlightableActor)
{
	HighlightableActor = NewHighlightableActor;
}