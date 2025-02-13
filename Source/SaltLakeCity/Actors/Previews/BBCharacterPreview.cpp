// SaltLakeCity 4.27

#include "BBCharacterPreview.h"
#include "Actors/Characters/Interfaces/IBBCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABBCharacterPreview::ABBCharacterPreview() :
	Super()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	SetActorEnableCollision(false);
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ClearColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
	AutoGenerateMips = false;
	Width = 256;
	Height = 256;

	PreviewSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PreviewSpringArm"));

	verifyf(IsValid(PreviewSpringArm), TEXT("Preview Spring Arm is invalid."));

	PreviewSpringArm->bEditableWhenInherited = true;
	PreviewSpringArm->TargetArmLength = 500.0f;
	PreviewSpringArm->SetupAttachment(RootComponent);

	PreviewSceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("PreviewSceneCapture"));

	verifyf(IsValid(PreviewSceneCapture), TEXT("Preview Scene Capture is invalid."));

	PreviewSceneCapture->bEditableWhenInherited = true;
	PreviewSceneCapture->bCaptureEveryFrame = true;
	PreviewSceneCapture->SetupAttachment(PreviewSpringArm);
	PreviewSceneCapture->SetWorldLocationAndRotationNoPhysics(PreviewSceneCapture->GetComponentLocation(),
		UKismetMathLibrary::FindLookAtRotation(PreviewSceneCapture->GetComponentLocation(), this->GetActorLocation()));
	PreviewSceneCapture->ShowOnlyActors.Emplace(this);
}

void ABBCharacterPreview::BeginPlay()
{
	Super::BeginPlay();

	PreviewRenderTarget = NewObject<UTextureRenderTarget2D>(this, UTextureRenderTarget2D::StaticClass());

	verifyf(IsValid(PreviewRenderTarget), TEXT("Preview Render Target is invalid."));

	PreviewRenderTarget->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8_SRGB;
	PreviewRenderTarget->ClearColor = ClearColor;
	PreviewRenderTarget->bAutoGenerateMips = AutoGenerateMips;
	PreviewRenderTarget->InitAutoFormat(Width, Height);
	PreviewRenderTarget->UpdateResourceImmediate(true);

	verifyf(IsValid(PreviewSceneCapture), TEXT("Preview Scene Capture is invalid."));

	PreviewSceneCapture->TextureTarget = PreviewRenderTarget;

	UGameInstance * GameInstance = GetGameInstance();

	verifyf(IsValid(GameInstance), TEXT("Game Instance is invalid."));

	APlayerController * PlayerController = GameInstance->GetFirstLocalPlayerController();

	verifyf(IsValid(PlayerController), TEXT("Player Controller is invalid."));

	PlayerController->HiddenActors.Emplace(this);
}

void ABBCharacterPreview::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABBCharacterPreview::CreatePreview(const AIBBCharacter * TemplateCharacter)
{
	verifyf(IsValid(TemplateCharacter), TEXT("Template Character is invalid."));

	USkeletalMeshComponent * TemplateMesh = TemplateCharacter->GetMesh();

	verifyf(IsValid(TemplateMesh), TEXT("Template Mesh is invalid."));

	USkeletalMeshComponent * Mesh = GetSkeletalMeshComponent();

	verifyf(IsValid(Mesh), TEXT("Mesh is invalid."));

	Mesh->SetSkeletalMesh(TemplateMesh->SkeletalMesh, true);

	SetActorScale3D(TemplateCharacter->GetActorScale3D());
}

void ABBCharacterPreview::ShowActors(TArray<AActor *> Actors)
{
	PreviewSceneCapture->ShowOnlyActors.Append(Actors);
}

UTexture * ABBCharacterPreview::GetPreview()
{	
	return PreviewRenderTarget;
}