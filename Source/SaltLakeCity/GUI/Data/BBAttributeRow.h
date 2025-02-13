// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Includes/BBAttributeEnum.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "BBAttributeRow.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)

struct FBBAttributeRow : public FTableRowBase
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBBAttribute Enumerator;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UTexture2D> Icon;
};