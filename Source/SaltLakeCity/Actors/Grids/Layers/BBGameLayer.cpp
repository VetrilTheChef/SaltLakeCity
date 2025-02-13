// SaltLakeCity 4.25

#include "BBGameLayer.h"
#include "Components/BoxComponent.h"
#include "Components/Interfaces/IBBGridComponent.h"

ABBGameLayer::ABBGameLayer() :
	Super()
{
	Index = -1;
	Height = 1.0f;
	Scale = FVector::OneVector;

	LayerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LayerCollision"));

	verifyf(IsValid(LayerCollision), TEXT("Layer Collision is invalid."));

	RootComponent = LayerCollision;

	LayerCollision->bEditableWhenInherited = true;
	LayerCollision->bHiddenInGame = false;
	LayerCollision->SetWorldTransform(FTransform::Identity);
	LayerCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	LayerCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	LayerCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	LayerCollision->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	LayerCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	LayerCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
	LayerCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Block);
	LayerCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	LayerCollision->CanCharacterStepUpOn = TEnumAsByte<ECanBeCharacterBase>(ECanBeCharacterBase::ECB_No);
	LayerCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LayerCollision->UpdateCollisionProfile();

	LayerFloor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LayerFloor"));

	verifyf(IsValid(LayerFloor), TEXT("Layer Floor is invalid."));

	LayerFloor->bEditableWhenInherited = true;
	LayerFloor->SetCollisionResponseToAllChannels(ECR_Ignore);
	LayerFloor->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	LayerFloor->SetCollisionObjectType(ECC_GameTraceChannel1);
	LayerFloor->CanCharacterStepUpOn = TEnumAsByte<ECanBeCharacterBase>(ECanBeCharacterBase::ECB_No);
	LayerFloor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LayerFloor->UpdateCollisionProfile();

	LayerFloor->SetupAttachment(RootComponent);

	LayerActors.Empty();
}

void ABBGameLayer::BeginPlay()
{
	Super::BeginPlay();
}

void ABBGameLayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (auto& LayerActor : LayerActors)
	{
		LayerActor->SetActorHiddenInGame(false);
	}

	LayerActors.Empty();

	Super::EndPlay(EndPlayReason);
}

void ABBGameLayer::Initialize(AActor * ParentActor, const int NewIndex, const float NewSize, const float NewHeight, const FVector NewScale)
{
	verifyf(!LayerGridClass.IsNull(), TEXT("Layer Grid class is null."));

	Index = NewIndex;
	Height = NewHeight;
	Scale = NewScale;
	int Columns = Scale.Y / NewSize;
	int Rows = Scale.X / NewSize;

	LayerGrid = NewObject<UIBBGridComponent>(this, LayerGridClass.LoadSynchronous(), TEXT("LayerGrid"));

	verifyf(IsValid(LayerGrid), TEXT("Layer Grid is invalid."));

	LayerGrid->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	LayerGrid->SetCollisionResponseToAllChannels(ECR_Ignore);
	LayerGrid->SetCollisionObjectType(ECC_GameTraceChannel1);
	LayerGrid->CanCharacterStepUpOn = TEnumAsByte<ECanBeCharacterBase>(ECanBeCharacterBase::ECB_No);
	LayerGrid->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LayerGrid->UpdateCollisionProfile();

	LayerGrid->Initialize(Columns, Rows, NewSize);

	LayerGrid->SetupAttachment(RootComponent);
	LayerGrid->RegisterComponent();

	AttachToActor(ParentActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SetActorRelativeLocation(FVector(0.0f, 0.0f, Height));
	SetActorRelativeScale3D(Scale);
}

void ABBGameLayer::Finalize()
{
}

const int ABBGameLayer::GetIndex() const
{
	return Index;
}

const float ABBGameLayer::GetSize() const
{
	verifyf(IsValid(LayerGrid), TEXT("Layer Grid is invalid."));

	return LayerGrid->GetTileSize();
}

const float ABBGameLayer::GetHeight() const
{
	return Height;
}

const FVector ABBGameLayer::GetScale() const
{
	return Scale;
}

void ABBGameLayer::AddActor(AActor * Actor)
{
	verifyf(IsValid(Actor), TEXT("Actor is invalid."));

	Actor->SetActorHiddenInGame(!IsVisible());

	LayerActors.Emplace(Actor);
}

void ABBGameLayer::RemoveActor(AActor * Actor)
{
	if (LayerActors.Remove(Actor))
	{
		Actor->SetActorHiddenInGame(false);
	}
}

bool ABBGameLayer::IsVisible() const
{
	verifyf(IsValid(RootComponent), TEXT("Root Component is invalid."));

	return RootComponent->IsVisible();
}

void ABBGameLayer::SetVisibility(bool Visible)
{
	verifyf(IsValid(RootComponent), TEXT("Root Component is invalid."));

	bool GridVisibility = IsGridVisible();

	RootComponent->SetVisibility(Visible, true);

	verifyf(IsValid(LayerCollision), TEXT("Layer Collision is invalid."));

	LayerCollision->SetCollisionEnabled(Visible ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);

	verifyf(IsValid(LayerGrid), TEXT("Layer Grid is invalid."));

	LayerGrid->SetVisibility(GridVisibility);

	for (auto& LayerActor : LayerActors)
	{
		LayerActor->SetActorHiddenInGame(!Visible);
	}
}

bool ABBGameLayer::IsGridVisible() const
{
	verifyf(IsValid(LayerGrid), TEXT("Layer Grid is invalid."));

	return LayerGrid->IsVisible();
}

void ABBGameLayer::SetGridVisibility(bool Visible)
{
	verifyf(IsValid(LayerGrid), TEXT("Layer Grid is invalid."));

	LayerGrid->SetVisibility(Visible);
}

bool ABBGameLayer::GetTilePosition(const FVector2D InPosition, FIntPoint & OutPosition) const
{
	verifyf(IsValid(LayerGrid), TEXT("Layer Grid is invalid."));

	return LayerGrid->GetTilePosition(InPosition, OutPosition);
}

bool ABBGameLayer::IsTileBuildable(const FIntPoint TilePosition) const
{
	verifyf(IsValid(LayerGrid), TEXT("Layer Grid is invalid."));

	return LayerGrid->IsTileBuildable(TilePosition);
}