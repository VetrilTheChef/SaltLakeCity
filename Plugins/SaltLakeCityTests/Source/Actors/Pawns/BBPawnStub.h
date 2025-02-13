// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pawns/Interfaces/IBBPawn.h"
#include "BBPawnStub.generated.h"

/**
*
*/

UCLASS(NotBlueprintable)

class ABBPawnStub : public AIBBPawn
{
	GENERATED_BODY()

	public:
		ABBPawnStub();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Tick(float DeltaSeconds) override;

		virtual const float GetMinCameraDistance() const override;

		void SetMinCameraDistance(const float NewMinCameraDistance);

		virtual const float GetMaxCameraDistance() const override;

		void SetMaxCameraDistance(const float NewMaxCameraDistance);

		virtual const float GetCameraDistance() const override;

		virtual void SetCameraDistance(const float NewCameraDistance) override;

		virtual const FVector GetForwardVector() const override;

		void SetForwardVector(const FVector NewForwardVector);

		virtual const FVector GetRightVector() const override;

		void SetRightVector(const FVector NewRightVector);

		virtual const FVector GetUpVector() const override;

		void SetUpVector(const FVector NewUpVector);

		virtual void Move(const FVector Direction, const float Scale) override;

		virtual void Turn(const float Direction) override;

		virtual void Lerp(const FVector TargetLocation, const float LerpTime) override;

		const FVector GetLerpTarget();

		virtual void Zoom(const float Scale) override;

	protected:
		float CameraDistance;

		float MinCameraDistance;

		float MaxCameraDistance;

		float ZoomSpeed;

		float PanSpeed;

		float MinMovementSpeed;

		float MaxMovementSpeed;

		float AccelerationTime;

		FVector ForwardVector;

		FVector RightVector;

		FVector UpVector;

		FVector MoveDirection;

		float MoveScale;

		float TurnDirection;

		FVector LerpTarget;

		float LerpTotalTime;

		float ZoomScale;
};