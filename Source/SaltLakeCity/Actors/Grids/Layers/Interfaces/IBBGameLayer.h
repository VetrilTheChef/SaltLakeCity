// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "IBBGameLayer.generated.h"

/**
*
*/

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBGameLayer : public AActor
{
	GENERATED_BODY()

	public:
		AIBBGameLayer() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Initialize(AActor * ParentActor, const int NewIndex, const float NewSize, const float NewHeight, const FVector NewScale) PURE_VIRTUAL(AIBBGameLayer::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(AIBBGameLayer::Finalize, );

		virtual const int GetIndex() const PURE_VIRTUAL(AIBBGameLayer::GetIndex, return -1; );

		virtual const float GetSize() const PURE_VIRTUAL(AIBBGameLayer::GetIndex, return 0.0f; );

		virtual const float GetHeight() const PURE_VIRTUAL(AIBBGameLayer::GetHeight, return 0.0f; );

		virtual const FVector GetScale() const PURE_VIRTUAL(AIBBGameLayer::GetScale, return FVector::ZeroVector; );

		virtual void AddActor(AActor * Actor) PURE_VIRTUAL(AIBBGameLayer::AddActor, );

		virtual void RemoveActor(AActor * Actor) PURE_VIRTUAL(AIBBGameLayer::RemoveActor, );

		virtual bool IsVisible() const PURE_VIRTUAL(AIBBGameLayer::IsVisible, return false; );

		virtual void SetVisibility(bool Visible) PURE_VIRTUAL(AIBBGameLayer::SetVisibility, );

		virtual bool IsGridVisible() const PURE_VIRTUAL(AIBBGameLayer::IsGridVisible, return false; );

		virtual void SetGridVisibility(bool Visible) PURE_VIRTUAL(AIBBGameLayer::SetGridVisibility, );

		virtual bool GetTilePosition(const FVector2D InPosition, FIntPoint & OutPosition) const PURE_VIRTUAL(AIBBGameLayer::GetTilePosition, return false; );

		virtual bool IsTileBuildable(const FIntPoint TilePosition) const PURE_VIRTUAL(AIBBGameLayer::IsTileBuildable, return false; );
};