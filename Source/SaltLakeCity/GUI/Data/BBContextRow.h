// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBContextEnum.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Specifications/Actors/BBActorSpecification.h"
#include "BBContextRow.generated.h"

/**
 * 
 */

class UTexture2D;

USTRUCT(BlueprintType)

struct FBBContextRow : public FTableRowBase
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftClassPtr<UBBActorSpecification> Specification;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UTexture2D> Icon;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Tooltip;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBBContext ContextType;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBBWidget WidgetToOpen;
};