// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "BBNeedEnum.generated.h"

/**
*
*/

UENUM(BlueprintType)

enum class EBBNeed : uint8
{
	Hunger		UMETA(DisplayName = "Hunger"),
	Sleep		UMETA(DisplayName = "Sleep"),
	Thirst		UMETA(DisplayName = "Thirst")
};