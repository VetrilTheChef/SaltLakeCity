// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Components/Interfaces/IBBGridComponent.h"
#include "Components/Includes/BBBuildTileStruct.h"
#include "BBGridComponent.generated.h"

/**
*
*/

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBGridComponent : public UIBBGridComponent
{
	GENERATED_BODY()

	public:
		UBBGridComponent();

		virtual void BeginPlay() override;

		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		virtual void Initialize(const int NewColumns, const int NewRows, const float NewTileSize) override;

		virtual void Finalize();

		virtual const int GetNumColumns() const override;

		virtual const int GetNumRows() const override;
			
		virtual const float GetTileSize() const override;

		virtual bool GetTilePosition(const FVector2D InPosition, FIntPoint & OutPosition) const override;

		virtual bool IsTileBuildable(const FIntPoint TilePosition) const override;

	protected:
		//UPROPERTY(Category = "Grid Settings", EditAnywhere, BlueprintReadWrite)
		//TSoftClassPtr<UIBB2DCellComponent> CellClass;

		UPROPERTY()
		TMap<FIntPoint, FBBBuildTile> Tiles;

		int Columns;

		int Rows;

		float TileSize;
};