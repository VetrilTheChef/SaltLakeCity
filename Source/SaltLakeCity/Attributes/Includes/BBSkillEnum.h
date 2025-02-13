// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "BBSkillEnum.generated.h"

/**
*
*/

UENUM(BlueprintType)

enum class EBBSkill : uint8
{
	Build		UMETA(DisplayName = "Build"),
	Fuck		UMETA(DisplayName = "Fuck"),
	Guard		UMETA(DisplayName = "Guard"),
	Lead		UMETA(DisplayName = "Lead"),
	Research	UMETA(DisplayName = "Research"),
};