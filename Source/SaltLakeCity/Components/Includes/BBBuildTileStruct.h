// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "BBBuildTileStruct.generated.h"

/**
*
*/

USTRUCT(BlueprintType)

struct FBBBuildTile
{
	GENERATED_BODY()

	public:
		UPROPERTY()
		TArray<TScriptInterface<IBBBuildable>> Buildables;

		FBBBuildTile()
		{
			Buildables.Empty();
		}

		~FBBBuildTile()
		{
			Buildables.Empty();
		}
};