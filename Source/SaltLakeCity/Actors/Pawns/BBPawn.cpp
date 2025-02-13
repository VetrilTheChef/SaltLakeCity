// SaltLakeCity 4.25

#include "BBPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveVector.h"
#include "GameFramework/Controller.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

ABBPawn::ABBPawn() :
	Super()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	MinCameraDistance = 200.0f;
	MaxCameraDistance = 5000.0f;
	ZoomSpeed = 100.0f;
	MinMovementSpeed = 1000.0f;
	MaxMovementSpeed = 10000.0f;

	// PawnCollision is assigned directly to RootComponent as that component
	// is the only one considered for collision during movement

	PawnCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;

	verifyf(IsValid(PawnCollision), TEXT("Pawn Collision is invalid."));

	PawnCollision->bEditableWhenInherited = true;
	PawnCollision->SetWorldTransform(FTransform::Identity);
	PawnCollision->InitSphereRadius(32.0f);
	PawnCollision->SetCollisionProfileName(TEXT("Pawn"));
	PawnCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	PawnCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	//PawnCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Block);
	//PawnCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECR_Block);
	//PawnCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECR_Block);
	PawnCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECR_Block);
	PawnCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PawnCollision->SetUseCCD(true);
	PawnCollision->UpdateCollisionProfile();

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));

	verifyf(IsValid(PawnMovement), TEXT("Pawn Movement is invalid."));

	PawnMovement->bEditableWhenInherited = true;
	PawnMovement->MaxSpeed = 2000.0f;
	PawnMovement->SetPlaneConstraintOrigin(GetActorLocation());
	PawnMovement->SetPlaneConstraintNormal(FVector::UpVector);
	PawnMovement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
	PawnMovement->SetPlaneConstraintEnabled(true);

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));

	verifyf(IsValid(PawnMesh), TEXT("Pawn Mesh is invalid."));

	PawnMesh->bEditableWhenInherited = true;
	PawnMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	PawnMesh->SetupAttachment(RootComponent);

	PawnSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PawnSpringArm"));

	verifyf(IsValid(PawnSpringArm), TEXT("Pawn Spring Arm is invalid."));

	PawnSpringArm->bEditableWhenInherited = true;
	PawnSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 200.0f), FRotator(-45.0f, 0.0f, 0.0f));
	PawnSpringArm->TargetArmLength = 1000.0f;
	PawnSpringArm->SetupAttachment(RootComponent);

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));

	verifyf(IsValid(PawnCamera), TEXT("Pawn Camera is invalid."));

	PawnCamera->bEditableWhenInherited = true;
	PawnCamera->SetupAttachment(PawnSpringArm);

	PawnTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("PawnTimeline"));

	verifyf(IsValid(PawnTimeline), TEXT("Pawn Timeline is invalid."));

	PawnTimeline->bEditableWhenInherited = true;
	PawnTimeline->PrimaryComponentTick.bCanEverTick = true;
	PawnTimeline->SetIgnoreTimeDilation(true);
	PawnTimeline->SetLooping(false);
	PawnTimeline->SetTickableWhenPaused(true);
	PawnTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);

	LocationLerpCurve = CreateDefaultSubobject<UCurveVector>(TEXT("LocationLerpCurve"));

	verifyf(IsValid(LocationLerpCurve), TEXT("Location Lerp Curve is invalid."));

	FOnTimelineVector PawnTimelineLocationLerp;
	PawnTimelineLocationLerp.BindUFunction(this, "LocationLerp");
	PawnTimeline->AddInterpVector(LocationLerpCurve, PawnTimelineLocationLerp, TEXT("LocationLerpCurve"), TEXT("LocationLerpTrack"));

	FOnTimelineEvent PawnTimelineFinishLerp;
	PawnTimelineFinishLerp.BindUFunction(this, "FinishLerp");
	PawnTimeline->SetTimelineFinishedFunc(PawnTimelineFinishLerp);
}

void ABBPawn::BeginPlay()
{
	Super::BeginPlay();

	SetCameraDistance(GetCameraDistance());
}

void ABBPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABBPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

const float ABBPawn::GetCameraDistance() const
{
	verifyf(IsValid(PawnSpringArm), TEXT("Pawn Spring Arm is invalid."));

	return PawnSpringArm->TargetArmLength;
}

const float ABBPawn::GetMinCameraDistance() const
{
	return MinCameraDistance;
}

const float ABBPawn::GetMaxCameraDistance() const
{
	return MaxCameraDistance;
}

void ABBPawn::SetCameraDistance(const float NewCameraDistance)
{
	verifyf(IsValid(PawnSpringArm), TEXT("Pawn Spring Arm is invalid."));

	PawnSpringArm->TargetArmLength = FMath::Clamp(NewCameraDistance, MinCameraDistance, MaxCameraDistance);

	float ZoomRatio = (PawnSpringArm->TargetArmLength - MinCameraDistance) / (MaxCameraDistance - MinCameraDistance);

	PawnMovement->MaxSpeed = FMath::LerpStable(MinMovementSpeed, MaxMovementSpeed, ZoomRatio);
}

const FVector ABBPawn::GetForwardVector() const
{
	verifyf(IsValid(PawnCamera), TEXT("Pawn Camera is invalid."));

	return PawnCamera->GetForwardVector();
}

const FVector ABBPawn::GetRightVector() const
{
	verifyf(IsValid(PawnCamera), TEXT("Pawn Camera is invalid."));

	return PawnCamera->GetRightVector();
}

const FVector ABBPawn::GetUpVector() const
{
	verifyf(IsValid(PawnCamera), TEXT("Pawn Camera is invalid."));

	return PawnCamera->GetUpVector();
}

void ABBPawn::Move(const FVector Direction, const float Scale)
{
	verifyf(IsValid(PawnMovement), TEXT("Pawn Movement is invalid."));

	AddMovementInput(Direction, Scale);
}

void ABBPawn::Turn(const float Direction)
{
	verifyf(IsValid(PawnMovement), TEXT("Pawn Movement is invalid."));

	AddActorLocalRotation(FRotator(0.0f, Direction * PanSpeed, 0.0f));
}

void ABBPawn::Lerp(const FVector TargetLocation, const float LerpTime)
{
	verifyf(IsValid(LocationLerpCurve), TEXT("Pawn Timeline Location Lerp Curve is invalid."));
	verifyf(IsValid(PawnTimeline), TEXT("Pawn Timeline is invalid."));

	float FinalTime = FMath::Max(LerpTime, 1.0f);

	StartLerp();

	FVector CurrentLocation = GetActorLocation();

	PawnTimeline->SetTimelineLength(FinalTime);

	PawnTimeline->SetVectorCurve(LocationLerpCurve, TEXT("LocationLerpTrack"));

	LocationLerpCurve->FloatCurves[0].Reset();

	LocationLerpCurve->FloatCurves[0].AddKey(0.0f, CurrentLocation.X);
	LocationLerpCurve->FloatCurves[0].AddKey(FinalTime, TargetLocation.X);

	for (auto Iterator(LocationLerpCurve->FloatCurves[0].GetKeyHandleIterator()); Iterator; ++Iterator)
	{
		LocationLerpCurve->FloatCurves[0].AutoSetTangents();
		LocationLerpCurve->FloatCurves[0].SetKeyInterpMode(* Iterator, ERichCurveInterpMode::RCIM_Cubic, true);
	}

	LocationLerpCurve->FloatCurves[1].Reset();

	LocationLerpCurve->FloatCurves[1].AddKey(0.0f, CurrentLocation.Y);
	LocationLerpCurve->FloatCurves[1].AddKey(FinalTime, TargetLocation.Y);

	for (auto Iterator(LocationLerpCurve->FloatCurves[1].GetKeyHandleIterator()); Iterator; ++Iterator)
	{
		LocationLerpCurve->FloatCurves[1].AutoSetTangents();
		LocationLerpCurve->FloatCurves[1].SetKeyInterpMode(* Iterator, ERichCurveInterpMode::RCIM_Cubic, true);
	}

	LocationLerpCurve->FloatCurves[2].Reset();

	LocationLerpCurve->FloatCurves[2].AddKey(0.0f, CurrentLocation.Z);
	LocationLerpCurve->FloatCurves[2].AddKey(FinalTime, TargetLocation.Z);

	for (auto Iterator(LocationLerpCurve->FloatCurves[2].GetKeyHandleIterator()); Iterator; ++Iterator)
	{
		LocationLerpCurve->FloatCurves[2].AutoSetTangents();
		LocationLerpCurve->FloatCurves[2].SetKeyInterpMode(* Iterator, ERichCurveInterpMode::RCIM_Cubic, true);
	}

	PawnTimeline->PlayFromStart();
}

void ABBPawn::Zoom(const float Scale)
{
	SetCameraDistance(GetCameraDistance() + (Scale * ZoomSpeed));
}



void ABBPawn::StartLerp()
{
	verifyf(IsValid(PawnMovement), TEXT("Pawn Movement is invalid."));

	PawnMovement->Deactivate();

	PawnMovement->SetPlaneConstraintEnabled(false);
}

void ABBPawn::LocationLerp(FVector Output)
{
	SetActorLocation(Output);
}

void ABBPawn::FinishLerp()
{
	verifyf(IsValid(PawnMovement), TEXT("Pawn Movement is invalid."));

	PawnMovement->SetPlaneConstraintOrigin(GetActorLocation());
	PawnMovement->SetPlaneConstraintEnabled(false);

	PawnMovement->Activate();

	OnLerpCompleted().Broadcast();
}