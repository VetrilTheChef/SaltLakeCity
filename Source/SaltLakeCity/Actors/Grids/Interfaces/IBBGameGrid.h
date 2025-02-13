// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "IBBGameGrid.generated.h"

/**
*
*/

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBGameGrid : public AActor
{
	GENERATED_BODY()

	public:
		AIBBGameGrid() : Super() { };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize() PURE_VIRTUAL(AIBBGameGrid::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(AIBBGameGrid::Finalize, );

		virtual const int GetGroundLayer() const PURE_VIRTUAL(AIBBGameGrid::GetGroundLayer, return 0; );

		virtual const int GetNumLayers() const PURE_VIRTUAL(AIBBGameGrid::GetActiveLayer, return 0; );

		virtual const int GetActiveLayer() const PURE_VIRTUAL(AIBBGameGrid::GetActiveLayer, return 0; );

		virtual bool SetActiveLayer(const int NewActiveLayerIndex) PURE_VIRTUAL(AIBBGameGrid::SetActiveLayer, return false; );

		virtual void AddToLayer(AActor * Actor, int LayerIndex) PURE_VIRTUAL(AIBBGameGrid::AddActor, );

		virtual void RemoveFromLayer(AActor * Actor, int LayerIndex) PURE_VIRTUAL(AIBBGameGrid::RemoveActor, );

		virtual bool IsVisible() const PURE_VIRTUAL(AIBBGameGrid::IsVisible, return false; );

		virtual void SetVisibility(bool Visible) PURE_VIRTUAL(AIBBGameGrid::SetVisibility, );

		virtual bool IsGridVisible() const PURE_VIRTUAL(AIBBGameGrid::IsGridVisible, return false; );

		virtual void SetGridVisibility(bool Visible) PURE_VIRTUAL(AIBBGameGrid::SetGridVisibility, );

		virtual bool GetGridPosition(const FVector2D InPosition, FIntPoint & OutPosition) const PURE_VIRTUAL(AIBBGameGrid::GetGridPosition, return false; );

		virtual bool GetGridSize(float & OutSize) const PURE_VIRTUAL(AIBBGameGrid::GetGridSize, return false; );
		
		virtual bool GetGridHeight(float & OutHeight) const PURE_VIRTUAL(AIBBGameGrid::GetGridHeight, return false; );

		virtual bool IsGridPositionBuildable(const FIntPoint GridPosition) const PURE_VIRTUAL(AIBBGameGrid::IsGridPositionBuildable, return false; );
};