// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "IBBTileComponent.generated.h"

/**
*
*/

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBTileComponent : public UActorComponent
{
	GENERATED_BODY()

	public:
		UIBBTileComponent() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual const float GetSize() const PURE_VIRTUAL(UIBBTileComponent::GetSize, return -1.0f; );

		virtual void SetSize(const float NewSize)  PURE_VIRTUAL(UIBBTileComponent::SetSize, );
};