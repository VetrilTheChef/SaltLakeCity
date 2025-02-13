// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IBBPawn.generated.h"

/**
*
*/

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API AIBBPawn : public APawn
{
	GENERATED_BODY()

	public:
		AIBBPawn() : Super() { };

		virtual void BeginPlay() override { Super::BeginPlay(); };

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override { Super::EndPlay(EndPlayReason); };

		virtual void Tick(float DeltaSeconds) override { Super::Tick(DeltaSeconds); };

		virtual const float GetCameraDistance() const PURE_VIRTUAL(AIBBPawn::GetCameraDistance, return -1.0f; );

		virtual const float GetMinCameraDistance() const PURE_VIRTUAL(AIBBPawn::GetMinCameraDistance, return -1.0f; );

		virtual const float GetMaxCameraDistance() const PURE_VIRTUAL(AIBBPawn::GetMaxCameraDistance, return -1.0f; );

		virtual void SetCameraDistance(const float NewCameraDistance) PURE_VIRTUAL(AIBBPawn::SetCameraDistance, );

		virtual const FVector GetForwardVector() const PURE_VIRTUAL(AIBBPawn::GetForwardVector, return FVector(); );

		virtual const FVector GetRightVector() const PURE_VIRTUAL(AIBBPawn::GetRightVector, return FVector(); );

		virtual const FVector GetUpVector() const PURE_VIRTUAL(AIBBPawn::GetUpVector, return FVector(); );

		virtual void Move(const FVector Direction, const float Scale) PURE_VIRTUAL(AIBBPawn::Move, );

		virtual void Turn(const float Direction) PURE_VIRTUAL(AIBBPawn::Turn, );

		virtual void Lerp(const FVector TargetLocation, const float LerpTime) PURE_VIRTUAL(AIBBPawn::Move, );

		virtual void Zoom(const float Scale) PURE_VIRTUAL(AIBBPawn::Zoom, );

		DECLARE_EVENT(AIBBPawn, FBBCompleteLerp);

		virtual FBBCompleteLerp & OnLerpCompleted() { return CompleteLerp; };

	protected:
		FBBCompleteLerp CompleteLerp;
};