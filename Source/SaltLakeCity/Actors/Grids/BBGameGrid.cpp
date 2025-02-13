// SaltLakeCity 4.27

#include "BBGameGrid.h"
#include "Actors/Grids/Layers/Interfaces/IBBGameLayer.h"
#include "Components/BoxComponent.h"
#include "Components/Interfaces/IBBGridComponent.h"

ABBGameGrid::ABBGameGrid() :
	Super()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("GameGridRoot"));

	verifyf(IsValid(RootComponent), TEXT("Game Grid Root is invalid."));

	RootComponent->SetWorldTransform(FTransform::Identity);

	RootLayer = nullptr;
	ActiveLayer = nullptr;

	GameLayers.Empty();
}

void ABBGameGrid::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (AIBBGameLayer * & GameLayer : GameLayers)
	{
		GameLayer->SetVisibility(true);
		GameLayer->Finalize();
		GameLayer->MarkPendingKill();
	}

	GameLayers.Empty();

	ActiveLayer = nullptr;
	RootLayer = nullptr;

	Super::EndPlay(EndPlayReason);
}

void ABBGameGrid::Initialize()
{
	verifyf(!GameLayerClass.IsNull(), TEXT("Game Layer class is null."));

	UWorld * World = GetWorld();

	verifyf(IsValid(World), TEXT("World is invalid."));

	float BaseHeight = GetActorLocation().Z;

	FVector LayerScale = GetActorScale3D();
	LayerScale.Z = 1.0f;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int Layer = 0; Layer < NumLayers; Layer++)
	{
		AIBBGameLayer * GameLayer = World->SpawnActor<AIBBGameLayer>(GameLayerClass.LoadSynchronous(), SpawnParameters);

		verifyf(IsValid(GameLayer), TEXT("Game Layer is invalid."));

		GameLayer->Initialize(this, Layer, TileSize, BaseHeight + (LayerHeight * (Layer - GroundLayer)), LayerScale);

		GameLayer->SetVisibility(false);

		GameLayers.Emplace(GameLayer);
	}

	RootLayer = GameLayers[GroundLayer];

	ActiveLayer = RootLayer;
	ActiveLayer->SetVisibility(true);
}

void ABBGameGrid::Finalize()
{
	for (auto& GameLayer : GameLayers)
	{
		if (IsValid(GameLayer))
		{
			GameLayer->Finalize();
			GameLayer->MarkPendingKill();
		}
	}

	GameLayers.Empty();

	ActiveLayer = nullptr;
	RootLayer = nullptr;
}

const int ABBGameGrid::GetGroundLayer() const
{
	return GroundLayer;
}

const int ABBGameGrid::GetNumLayers() const
{
	return GameLayers.Num();
}

const int ABBGameGrid::GetActiveLayer() const
{
	if (IsValid(ActiveLayer))
	{
		return ActiveLayer->GetIndex();
	}

	return -1;
}

bool ABBGameGrid::SetActiveLayer(const int NewActiveLayerIndex)
{
	if (GameLayers.IsValidIndex(NewActiveLayerIndex))
	{
		verifyf(IsValid(RootLayer), TEXT("Root Layer is invalid."));

		int GroundIndex = RootLayer->GetIndex();

		verifyf(IsValid(ActiveLayer), TEXT("Active Layer is invalid."));

		bool GridVisibility = ActiveLayer->IsGridVisible();

		for (auto& GameLayer : GameLayers)
		{
			verifyf(IsValid(GameLayer), TEXT("Game Layer is invalid."));

			int LayerIndex = GameLayer->GetIndex();

			// Ground level and underground - only the active layer is visible
			// Above ground level - all the layers from the ground up to the active layer are visible
			bool Visibility = (NewActiveLayerIndex <= GroundIndex) ?
								(LayerIndex == NewActiveLayerIndex) :
								((LayerIndex >= GroundIndex) && (LayerIndex <= NewActiveLayerIndex));

			GameLayer->SetVisibility(Visibility);
			GameLayer->SetGridVisibility(false);
		}

		ActiveLayer = GameLayers[NewActiveLayerIndex];

		ActiveLayer->SetGridVisibility(GridVisibility);

		return true;
	}

	return false;
}

void ABBGameGrid::AddToLayer(AActor * Actor, int LayerIndex)
{
	verifyf(GameLayers.IsValidIndex(LayerIndex), TEXT("Layer Index is out of bounds."));

	AIBBGameLayer * GameLayer = GameLayers[LayerIndex];

	verifyf(IsValid(GameLayer), TEXT("Game Layer is invalid."));

	GameLayer->AddActor(Actor);
}

void ABBGameGrid::RemoveFromLayer(AActor * Actor, int LayerIndex)
{
	verifyf(GameLayers.IsValidIndex(LayerIndex), TEXT("Layer Index is out of bounds."));

	AIBBGameLayer * GameLayer = GameLayers[LayerIndex];

	verifyf(IsValid(GameLayer), TEXT("Game Layer is invalid."));

	GameLayer->RemoveActor(Actor);
}

bool ABBGameGrid::IsVisible() const
{
	verifyf(IsValid(ActiveLayer), TEXT("Active Layer is invalid."));

	return ActiveLayer->IsVisible();
}

void ABBGameGrid::SetVisibility(bool Visible)
{
	for (auto& GameLayer : GameLayers)
	{
		GameLayer->SetVisibility(Visible);
	}
}

bool ABBGameGrid::IsGridVisible() const
{
	verifyf(IsValid(ActiveLayer), TEXT("Active Layer is invalid."));

	return ActiveLayer->IsGridVisible();
}

void ABBGameGrid::SetGridVisibility(bool Visible)
{
	verifyf(IsValid(ActiveLayer), TEXT("Active Layer is invalid."));

	ActiveLayer->SetGridVisibility(Visible);
}

bool ABBGameGrid::GetGridPosition(const FVector2D InPosition, FIntPoint & OutPosition) const
{
	verifyf(IsValid(ActiveLayer), TEXT("Active Layer is invalid."));

	return ActiveLayer->GetTilePosition(InPosition, OutPosition);
}

bool ABBGameGrid::GetGridSize(float & OutSize) const
{
	if (IsValid(ActiveLayer))
	{
		OutSize = ActiveLayer->GetSize();

		return true;
	}

	return false;
}

bool ABBGameGrid::GetGridHeight(float & OutHeight) const
{
	if (IsValid(ActiveLayer))
	{
		OutHeight = ActiveLayer->GetHeight();

		return true;
	}

	return false;
}

bool ABBGameGrid::IsGridPositionBuildable(const FIntPoint GridPosition) const
{
	if (IsValid(ActiveLayer))
	{
		return ActiveLayer->IsTileBuildable(GridPosition);
	}

	return false;
}