// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "BBJobRow.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)

struct FBBJobRow : public FTableRowBase
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Tooltip;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBBJob Job;

		FBBJobRow()
		{
			Name = FText::FromString("");
			Tooltip = FText::FromString("");
			Job = EBBJob::None;
		}

		FBBJobRow(FText NewName, FText NewTooltip, EBBJob NewJob)
		{
			Name = NewName;
			Tooltip = NewTooltip;
			Job = NewJob;
		}

		~FBBJobRow()
		{
			Name = FText::FromString("");
			Tooltip = FText::FromString("");
			Job = EBBJob::None;
		}
};