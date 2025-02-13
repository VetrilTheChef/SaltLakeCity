// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "BBBuildCategoryEnum.generated.h"

/**
 * 
 */

UENUM(BlueprintType)

enum class EBBBuildCategory : uint8
{
	None			UMETA(DisplayName = "None"),
	Foundation		UMETA(DisplayName = "Foundation"),
	Outdoors		UMETA(DisplayName = "Structural"),
	Indoors			UMETA(DisplayName = "Objects"),
	Customization	UMETA(DisplayName = "Customization")
};