// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Actors/Grids/Layers/Interfaces/IBBGameLayer.h"
#include "BBGameLayer.generated.h"

/**
*
*/

class UBoxComponent;
class UIBBGridComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API ABBGameLayer : public AIBBGameLayer
{
	GENERATED_BODY()

	public:
		ABBGameLayer();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(AActor * ParentActor, const int NewIndex, const float NewSize, const float NewHeight, const FVector NewScale) override;

		virtual void Finalize() override;

		virtual const int GetIndex() const override;

		virtual const float GetSize() const override;

		virtual const float GetHeight() const override;

		virtual const FVector GetScale() const override;

		virtual void AddActor(AActor * Actor) override;

		virtual void RemoveActor(AActor * Actor) override;

		virtual bool IsVisible() const override;

		virtual void SetVisibility(bool Visible) override;

		virtual bool IsGridVisible() const override;

		virtual void SetGridVisibility(bool Visible) override;

		virtual bool GetTilePosition(const FVector2D InPosition, FIntPoint & OutPosition) const override;

		virtual bool IsTileBuildable(const FIntPoint TilePosition) const override;

	protected:
		UPROPERTY(Category = "World Layer Settings", EditAnywhere, BlueprintReadWrite)
		TSoftClassPtr<UIBBGridComponent> LayerGridClass;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent * LayerCollision;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent * LayerFloor;

		UPROPERTY()
		UIBBGridComponent * LayerGrid;

		UPROPERTY()
		TSet<AActor *> LayerActors;

		int Index;

		float Height;

		FVector Scale;
};