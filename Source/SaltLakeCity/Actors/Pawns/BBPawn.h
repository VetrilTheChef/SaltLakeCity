// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pawns/Interfaces/IBBPawn.h"
#include "Components/TimelineComponent.h"
#include "BBPawn.generated.h"

/**
*
*/

class UCameraComponent;
class UFloatingPawnMovement;
class USphereComponent;
class USpringArmComponent;
class UStaticMeshComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API ABBPawn : public AIBBPawn
{
	GENERATED_BODY()

	public:
		ABBPawn();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Tick(float DeltaSeconds) override;

		virtual const float GetCameraDistance() const override;

		virtual const float GetMinCameraDistance() const override;

		virtual const float GetMaxCameraDistance() const override;

		virtual void SetCameraDistance(const float NewCameraDistance) override;

		virtual const FVector GetForwardVector() const override;

		virtual const FVector GetRightVector() const override;

		virtual const FVector GetUpVector() const override;

		virtual void Move(const FVector Direction, const float Scale) override;

		virtual void Turn(const float Direction) override;

		virtual void Lerp(const FVector TargetLocation, const float LerpTime) override;

		virtual void Zoom(const float Scale) override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Camera", meta=(ClampMin = "200.0", ClampMax = "1000.0"))
		float MinCameraDistance;

		UPROPERTY(EditDefaultsOnly, Category = "Camera", meta=(ClampMin = "1000.0", ClampMax = "5000.0"))
		float MaxCameraDistance;

		UPROPERTY(EditDefaultsOnly, Category = "Camera", meta = (ClampMin = "50.0", ClampMax = "500.0"))
		float ZoomSpeed;

		UPROPERTY(EditDefaultsOnly, Category = "Camera", meta = (ClampMin = "50.0", ClampMax = "500.0"))
		float PanSpeed;

		UPROPERTY(EditDefaultsOnly, Category = "Movement", meta=(ClampMin = "1000.0", ClampMax = "20000.0"))
		float MinMovementSpeed;

		UPROPERTY(EditDefaultsOnly, Category = "Movement", meta=(ClampMin = "20000.0", ClampMax = "40000.0"))
		float MaxMovementSpeed;

		UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (ClampMin = "0.0", ClampMax = "5.0"))
		float AccelerationTime;

		UPROPERTY()
		USphereComponent * PawnCollision;

		UPROPERTY()
		UFloatingPawnMovement * PawnMovement;

		UPROPERTY()
		UStaticMeshComponent * PawnMesh;

		UPROPERTY()
		USpringArmComponent * PawnSpringArm;

		UPROPERTY()
		UCameraComponent * PawnCamera;

		UPROPERTY()
		UTimelineComponent * PawnTimeline;

		UPROPERTY()
		UCurveVector * LocationLerpCurve;

		UFUNCTION()
		void StartLerp();

		UFUNCTION()
		void LocationLerp(FVector Output);

		UFUNCTION()
		void FinishLerp();
};