// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Actors/Grids/Interfaces/IBBGameGrid.h"
#include "BBGameGrid.generated.h"

/**
*
*/

class AIBBGameLayer;
class UBoxComponent;
class UIBBGridComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API ABBGameGrid : public AIBBGameGrid
{
	GENERATED_BODY()

	public:
		ABBGameGrid();

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize() override;

		virtual void Finalize() override;

		virtual const int GetGroundLayer() const override;

		virtual const int GetNumLayers() const override;

		virtual const int GetActiveLayer() const override;

		virtual bool SetActiveLayer(const int NewActiveLayerIndex) override;

		virtual void AddToLayer(AActor * Actor, int LayerIndex) override;

		virtual void RemoveFromLayer(AActor * Actor, int LayerIndex) override;

		virtual bool IsVisible() const override;

		virtual void SetVisibility(bool Visible) override;

		virtual bool IsGridVisible() const override;

		virtual void SetGridVisibility(bool Visible) override;

		virtual bool GetGridPosition(const FVector2D InPosition, FIntPoint & OutPosition) const override;

		virtual bool GetGridSize(float & OutSize) const override;

		virtual bool GetGridHeight(float & OutHeight) const override;

		virtual bool IsGridPositionBuildable(const FIntPoint GridPosition) const override;

	protected:
		UPROPERTY(Category = "Game Layers Settings", EditAnywhere, BlueprintReadWrite)
		TSoftClassPtr<AIBBGameLayer> GameLayerClass;

		UPROPERTY(EditAnywhere, Category = "Game Layers Settings", meta = (ClampMin = "1"))
		int NumLayers;

		UPROPERTY(EditAnywhere, Category = "Game Layers Settings", meta = (ClampMin = "0"))
		int GroundLayer;

		UPROPERTY(EditAnywhere, Category = "Game Layers Settings", meta = (ClampMin = "100.0"))
		float TileSize;

		UPROPERTY(EditAnywhere, Category = "Game Layers Settings", meta = (ClampMin = "200.0"))
		float LayerHeight;

		UPROPERTY()
		AIBBGameLayer * RootLayer;

		UPROPERTY()
		AIBBGameLayer * ActiveLayer;

		UPROPERTY()
		TArray<AIBBGameLayer *> GameLayers;
};