// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "IBBGridComponent.generated.h"

/**
*
*/

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBGridComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	public:
		UIBBGridComponent() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize(const int NewColumns, const int NewRows, const float NewTileSize) PURE_VIRTUAL(UIBBGridComponent::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBGridComponent::Finalize, );

		virtual const int GetNumColumns() const PURE_VIRTUAL(UIBBGridComponent::GetNumColumns, return -1; );

		virtual const int GetNumRows() const PURE_VIRTUAL(UIBBGridComponent::GetNumRows, return -1; );

		virtual const float GetTileSize() const PURE_VIRTUAL(UIBBGridComponent::GetTileSize, return -1.0f; );
		
		virtual bool GetTilePosition(const FVector2D InPosition, FIntPoint & OutPosition) const PURE_VIRTUAL(UIBBGridComponent::GetTilePosition, return false; );

		virtual bool IsTileBuildable(const FIntPoint TilePosition) const PURE_VIRTUAL(UIBBGridComponent::IsTileBuildable, return false; );
};