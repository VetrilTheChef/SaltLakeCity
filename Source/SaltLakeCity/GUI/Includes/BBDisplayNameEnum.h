// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "BBDisplayNameEnum.generated.h"

/**
*
*/

UENUM(BlueprintType)

enum class EBBDisplayName : uint8
{
	Short		UMETA(DisplayName = "Short Name"),
	Long		UMETA(DisplayName = "Long Name"),
	Code		UMETA(DisplayName = "Code Name"),
	Full		UMETA(DisplayName = "Full Name")
};
