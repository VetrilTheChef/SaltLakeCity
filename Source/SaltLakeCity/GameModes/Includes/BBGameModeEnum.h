// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "BBGameModeEnum.generated.h"

/**
*
*/

UENUM(BlueprintType)

enum class EBBGameMode : uint8
{
	None		UMETA(DisplayName = "None"),
	Build		UMETA(DisplayName = "Build"),
	Play		UMETA(DisplayName = "Play")
};