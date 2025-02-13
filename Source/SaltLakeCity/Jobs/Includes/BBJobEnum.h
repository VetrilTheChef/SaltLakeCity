// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "BBJobEnum.generated.h"

/**
*
*/

UENUM(BlueprintType)

enum class EBBJob : uint8
{
	None		UMETA(DisplayName = "None"),
	Idle		UMETA(DisplayName = "Unemployed"),
	Builder		UMETA(DisplayName = "Builder")
};