// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "BBContextEnum.generated.h"

/**
*
*/

UENUM(BlueprintType)

enum class EBBContext : uint8
{
	None		UMETA(DisplayName = "None"),
	Build		UMETA(DisplayName = "Build"),
	Dossier		UMETA(DisplayName = "Dossier"),
	Job		UMETA(DisplayName = "Job")
};
