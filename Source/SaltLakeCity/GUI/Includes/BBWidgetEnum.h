// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "BBWidgetEnum.generated.h"

/**
*
*/

UENUM(BlueprintType)

enum class EBBWidget : uint8
{
	None				UMETA(DisplayName = "None"),
	SkillEntry			UMETA(DisplayName = "SkillEntry"),
	TraitEntry			UMETA(DisplayName = "TraitEntry"),
	EquipmentEntry		UMETA(DisplayName = "EquipmentEntry"),
	Build				UMETA(DisplayName = "Build"),
	BuildEntry			UMETA(DisplayName = "Build Entry"),
	Context				UMETA(DisplayName = "Context"),
	DateTime			UMETA(DisplayName = "Date Time"),
	Dossier				UMETA(DisplayName = "Dossier"),
	DossierEntry		UMETA(DisplayName = "Dossier Entry"),
	Job					UMETA(DisplayName = "Job"),
	Modes				UMETA(DisplayName = "Modes"),
	Progress			UMETA(DisplayName = "Progress"),
	Selection			UMETA(DisplayName = "Selection"),
	Title				UMETA(DisplayName = "Title")
};
