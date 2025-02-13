// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "BBAttributeEnum.generated.h"

/**
*
*/

UENUM(BlueprintType)

enum class EBBAttribute : uint8
{
	Health		UMETA(DisplayName = "Health"),
	Stamina		UMETA(DisplayName = "Stamina")
};