// SaltLakeCity 4.26

#include "BBPawnStub.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveVector.h"
#include "GameFramework/Controller.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

ABBPawnStub::ABBPawnStub() :
	Super()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CameraDistance = 10.0f;
	MinCameraDistance = 10.0f;
	MaxCameraDistance = 100.0f;
	ZoomSpeed = 10.0f;
	PanSpeed = 10.0f;
	MinMovementSpeed = 10.0f;
	MaxMovementSpeed = 100.0f;
	AccelerationTime = 1.0f;
	ForwardVector = FVector(1.0f, 0.0f, 0.0f);
	RightVector = FVector(0.0f, 1.0f, 0.0f);
	UpVector = FVector(0.0f, 0.0f, 1.0f);
	MoveDirection = FVector(0.0f, 0.0f, 0.0f);
	MoveScale = 0.0f;
	TurnDirection = 0.0f;
	LerpTarget = FVector(0.0f, 0.0f, 0.0f);
	LerpTotalTime = 0.0f;
	ZoomScale = 0.0f;
}

void ABBPawnStub::BeginPlay()
{
	Super::BeginPlay();
}

void ABBPawnStub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABBPawnStub::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

const float ABBPawnStub::GetMinCameraDistance() const
{
	return MinCameraDistance;
}

void ABBPawnStub::SetMinCameraDistance(const float NewMinCameraDistance)
{
	MinCameraDistance = NewMinCameraDistance;
}

const float ABBPawnStub::GetMaxCameraDistance() const
{
	return MaxCameraDistance;
}

void ABBPawnStub::SetMaxCameraDistance(const float NewMaxCameraDistance)
{
	MaxCameraDistance = NewMaxCameraDistance;
}

const float ABBPawnStub::GetCameraDistance() const
{
	return CameraDistance;
}

void ABBPawnStub::SetCameraDistance(const float NewCameraDistance)
{
	CameraDistance = FMath::Clamp(NewCameraDistance, MinCameraDistance, MaxCameraDistance);
}

const FVector ABBPawnStub::GetForwardVector() const
{
	return ForwardVector;
}

void ABBPawnStub::SetForwardVector(const FVector NewForwardVector)
{
	ForwardVector = NewForwardVector;
}

const FVector ABBPawnStub::GetRightVector() const
{
	return RightVector;
}

void ABBPawnStub::SetRightVector(const FVector NewRightVector)
{
	RightVector = NewRightVector;
}

const FVector ABBPawnStub::GetUpVector() const
{
	return UpVector;
}

void ABBPawnStub::SetUpVector(const FVector NewUpVector)
{
	UpVector = NewUpVector;
}

void ABBPawnStub::Move(const FVector Direction, const float Scale)
{
	MoveDirection = Direction;
	MoveScale = Scale;
}

void ABBPawnStub::Turn(const float Direction)
{
	TurnDirection = Direction;
}

void ABBPawnStub::Lerp(const FVector TargetLocation, const float LerpTime)
{
	LerpTarget = TargetLocation;
	LerpTotalTime = LerpTime;
}

const FVector ABBPawnStub::GetLerpTarget()
{
	return LerpTarget;
}

void ABBPawnStub::Zoom(const float Scale)
{
	ZoomScale = Scale;
}