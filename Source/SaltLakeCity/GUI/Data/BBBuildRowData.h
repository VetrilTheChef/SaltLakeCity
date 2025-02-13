// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "BBBuildRowData.generated.h"

/**
 * 
 */

class IBBBuildable;
class UTexture2D;

USTRUCT()

struct FBBBuildRowData
{
	GENERATED_BODY()

	public:
		FText Name;

		FText Tooltip;

		float Price;

		float Time;

		UPROPERTY()
		TSoftObjectPtr<UTexture2D> Image;

		UPROPERTY()
		TArray<TSoftClassPtr<IBBBuildable>> Buildables;

		FBBBuildRowData() :
			Name(FText::FromString("")),
			Tooltip(FText::FromString("")),
			Price(-1.0f),
			Time(-1.0f),
			Image(nullptr),
			Buildables(TArray<TSoftClassPtr<IBBBuildable>>())
		{
		}
};