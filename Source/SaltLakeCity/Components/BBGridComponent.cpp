// SaltLakeCity 4.25

#include "BBGridComponent.h"

UBBGridComponent::UBBGridComponent() :
	Super()
{
	Rows = 1;
	Columns = 1;
	TileSize = 100.0;

	bEditableWhenInherited = true;
	SetComponentTickEnabled(false);
	SetCastInsetShadow(false);
	SetCastShadow(false);
	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UpdateCollisionProfile();

	SetVisibility(false);
}

void UBBGridComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBBGridComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UBBGridComponent::Initialize(const int NewColumns, const int NewRows, const float NewTileSize)
{
	Columns = FMath::Max(1, NewColumns);
	Rows = FMath::Max(1, NewRows);
	TileSize = FMath::Max(NewTileSize, 100.0f);
}

void UBBGridComponent::Finalize()
{

}

const int UBBGridComponent::GetNumColumns() const
{
	return Columns;
}

const int UBBGridComponent::GetNumRows() const
{
	return Rows;
}

const float UBBGridComponent::GetTileSize() const
{
	return TileSize;
}

bool UBBGridComponent::GetTilePosition(const FVector2D InPosition, FIntPoint & OutPosition) const
{
	if (FMath::Abs(InPosition.X) < (Columns / 2 * TileSize) &&
		FMath::Abs(InPosition.Y) < (Rows / 2 * TileSize))
	{
		OutPosition = FIntPoint( (int)(InPosition.X / TileSize), (int)(InPosition.Y / TileSize) );

		return true;
	}

	return false;
}

bool UBBGridComponent::IsTileBuildable(const FIntPoint TilePosition) const
{
	return Tiles.Contains(TilePosition) ? (Tiles.FindRef(TilePosition).Buildables.Num() == 0) : true;
}