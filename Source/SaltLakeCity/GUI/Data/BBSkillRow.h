// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "BBSkillRow.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)

struct FBBSkillRow : public FTableRowBase
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBBSkill Enumerator;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UTexture2D> Icon;
};