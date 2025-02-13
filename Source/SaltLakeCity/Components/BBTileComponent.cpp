// SaltLakeCity 4.25

#include "BBTileComponent.h"

UBBTileComponent::UBBTileComponent() :
	Super()
{
	Size = -1.0f;
}

void UBBTileComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBBTileComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}



const float UBBTileComponent::GetSize() const
{
	return Size;
}

void UBBTileComponent::SetSize(const float NewSize)
{
	Size = FMath::Max(0.0f, NewSize);
}