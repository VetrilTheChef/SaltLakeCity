// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Includes/BBNeedEnum.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "BBNeedRow.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)

struct FBBNeedRow : public FTableRowBase
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBBNeed Enumerator;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UTexture2D> Icon;
};