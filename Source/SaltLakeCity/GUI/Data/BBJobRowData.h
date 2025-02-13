// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "BBJobRowData.generated.h"

/**
 * 
 */

USTRUCT()

struct FBBJobRowData
{
	GENERATED_BODY()

	public:
		FText Name;

		FText Tooltip;

		EBBJob Job;

		FBBJobRowData()
		{
			Name = FText::FromString("");
			Tooltip = FText::FromString("");
			Job = EBBJob::None;
		}
};