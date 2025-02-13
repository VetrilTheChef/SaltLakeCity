// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BBBuildingData.generated.h"

/**
*
*/

class UIBBComponentFactory;
class UIBBProgressComponent;
class UIBBSelectionComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBBuildingData : public UDataAsset
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSoftClassPtr<UIBBProgressComponent> ProgressComponentClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
		TSoftClassPtr<UIBBSelectionComponent> SelectionComponentClass;
};